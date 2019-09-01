
# include "EngineObject.hh"
# include "EventsUtils.hxx"

namespace sdl {
  namespace core {
    namespace engine {

      EngineObject::EngineObject(const std::string& name,
                                 const bool allowLog):
        utils::CoreObject(name, allowLog),
        m_filters(),
        m_queue(nullptr),

        m_eventsLocker(),
        m_events(),

        m_handledTypes()
      {
        setService(std::string("object"));
      }

      bool
      EngineObject::event(EventShPtr e) {
        // Apply all the filters registered for this listener.

        // Assume the event is not filtered.
        bool filtered = false;
        Filter filter = m_filters.cbegin();

        while (filter != m_filters.cend() && !filtered) {
          filtered = (*filter)->filterEvent(this, e);
          ++filter;
        }

        // Check whether this event has been filtered before calling
        // the internal handler.
        if (filtered) {
          // The event has been recognized since it was filtered.
          return true;
        }

        // Proceed with the internal handler: this will determine whether the event
        // has been regognized.
        return handleEvent(e);
      }

      void
      EngineObject::postEvent(EventShPtr e,
                              bool autosetReceiver,
                              bool autosetEmitter) noexcept
      {
        // Check event coherence.
        if (e == nullptr) {
          log(
            std::string("Cannot post empty event in queue"),
            utils::Level::Warning
          );
          return;
        }

        // Assign the receiver to `this` if asked and if no receiver
        // is provided in the input event.
        if (autosetReceiver && !e->isDirected()) {
          e->setReceiver(this);
        }

        // Assign this object as emitter of this event.
        if (autosetEmitter && e->isSpontaneous()) {
          e->setEmitter(this);
        }

        // Check whether a queue is provided: if this is not the case
        // we might still be ok if the event is set to be directed for
        // this object.
        if (m_queue == nullptr) {
          // Check whether the event is directed towards this object.
          if (isReceiver(*e)) {
            // Post directly onto the local queue. The event will not
            // be processed until a queue is assigned anyway but at
            // least we will not lose information.
            postLocalEvent(e);

            // Return to avoid posting the event using the null queue
            // anyway.
            return;
          }
          else {
            // We cannot direct the event to the suited object as no
            // queue is provided.
            log(
              std::string("Cannot post event ") + Event::getNameFromEvent(e) + ", no queue provided",
              utils::Level::Warning
            );
            return;
          }
        }

        // The event is now completely built. We need to either insert it into the
        // general events queue or inside the internal list of events for this object
        // if `this` is this object anyway.
        // No matter the case we rely on the events queue to call `postLocalEvent`
        // appropriately if needed.
        m_queue->postEvent(e);
      }

      void
      EngineObject::postLocalEvent(EventShPtr e) {
        // Check whether this event is valid.
        if (e == nullptr) {
          return;
        }

        // Now that we know that we have a valid event, we might ask the question
        // of how we will insert it into the internal array of events.
        // Indeed it might be useful to keep only one event of some type: for example
        // there's no need to keep two events indicating that the mouse left the
        // object, or that we need to resize to two different sizes. It is enough to
        // keep only the last one.
        // So we have to determine which kind of events already exist in the internal
        // array before inserting the new one.

        std::lock_guard<std::mutex> guard(m_eventsLocker);

        // Traverse the existing events and try to find a duplicate, i.e. an event
        // which has same type as the input one.
        bool unique = true;
        Events::iterator event = m_events.begin();

        while (unique && event != m_events.end()) {
          // An event is unique as long as it has either a) a different type or b) a
          // different emitter.
          unique = ((*event)->getType() != e->getType() || (*event)->getEmitter() != e->getEmitter());
          if (unique) {
            ++event;
          }
        }

        // Check whether we could find an event identical to the input one.
        // If this is the case we need to keep only one of the events based
        // on their timestamp (so that we can keep the most recent one). If
        // no identical events were found, we can safely proceed to insert
        // the new input event to the internal array.
        if (unique) {
          // Proceed to the insertion of the input event into the internal
          // array.
          // log("Queuing " + Event::getNameFromEvent(e), utils::Level::Notice);
          m_events.push_back(e);
        }
        else {
          // This event is not unique: use the dedicated merge function to
          // merge both events into a single one.
          // log("Merging " + Event::getNameFromEvent(e) + " with more recent event", utils::Level::Notice);

          (*event)->merge(*e);

          // The only remaining operation here is a sort so that events are
          // only ordered with the most basic first: as we did not modify
          // the order of the internal `m_events` array we can return right
          // away.
          return;
        }

        // Sort these events so that we process the most basic ones first:
        // this allows not to waste some processing time to handle a cycle
        // like so:
        // repaint -> geometry -> repaint (generated).
        // The order in the input `events` array is only chronological with
        // no consideration about the real meaning of events.
        // This object is able to make sense of such events and thus speed up
        // the processing by sorting them in importance order.
        sortLocalEvents();
      }

      void
      EngineObject::clearEvents() {
        // Clear internal events array.
        std::lock_guard<std::mutex> guard(m_eventsLocker);
        m_events.clear();
      }

      void
      EngineObject::processEvents(const EventProcessingPass& pass) {
        // We need to handle each and every event registered in this
        // object (and more specifically into the internal `m_events`
        // queue).
        // As this process may generated new events (for example when
        // processing a `Resize` event we usually trigger a `Repaint`
        // event), we need to keep processing until we perform a full
        // run with no new events generated.
        // This is a bit longer than only processing the currently
        // registered events and stopping there but it is better for
        // several reasons:
        // 1. It allows to build complex flows using events (`Resize`
        //    flow for instance).
        // 2. Most events are quick to process so it helps unqueuing
        //    events as fast as possible.
        // 3. It provides better support for os events which are
        //    usually numerous.
        // The dispatch system also facilitates this optimization
        // process by providing a `pass` argument: several events
        // processing passes are defined, each one focusing on the
        // processing of a specific kind of events. Each increment
        // add support for more events which usually generate less
        // new events.
        // We thus temper a bit what we said before in order to stop
        // also in case no more events corresponding to the input
        // `pass` exist in the internal queue.
        EventShPtr toProcess = nullptr;

        // Start processing.
        do {
          // Retrieve the first event of the queue so that we can
          // safely process the event without worrying that new
          // events might be generated. Indeed if we kept an iterator
          // on the queue it would be invalidated as soon as a new
          // event was posted.
          // Additionally we process the first event which belongs
          // to the input events processing pass.
          {
            std::lock_guard<std::mutex> guard(m_eventsLocker);

            // Check if at least one event can be retrieved.
            if (m_events.empty()) {
              toProcess = nullptr;
            }
            else {
              Events::reverse_iterator it = m_events.rbegin();
              while (it != m_events.rend() && !engine::belongsToPass((*it)->getType(), pass)) {
                ++it;
              }

              // Check whether we could find a valid event to process.
              if (it == m_events.rend()) {
                toProcess = nullptr;
              }
              else {
                toProcess = *it;
                m_events.erase(std::next(it).base());
              }
            }
          }

          // Discard invalid events.
          if (toProcess == nullptr || toProcess->getType() == Event::Type::None) {
            continue;
          }

          // Check whether this event is actually directed towards us.
          if (toProcess->isDirected() && !isReceiver(*toProcess)) {
            // Requeue this event.
            log(
              std::string("Could not process event \"") + Event::getNameFromEvent(*toProcess) +
              "\" (invalid receiver \"" + toProcess->getReceiver()->getName() + "\"",
              utils::Level::Warning
            );

            postEvent(toProcess);
          }

          // Process this event.
          event(toProcess);

        } while (toProcess != nullptr);
      }

      void
      EngineObject::installEventFilter(EngineObject* filter) {
        // Check filter validity.
        if (filter == nullptr) {
          log(
            std::string("Cannot install event filter, invalid null filter"),
            utils::Level::Warning
          );

          return;
        }

        // Only add this filter if it does not exist yet.
        // The `removeFilter` does handle properly the case where
        // the provided filter does not exist so use it as a cheap
        // solution to remove the `filter` in all cases.
        removeFilter(findFilter(filter));

        // Insert this filter at the end of the internal vector.
        // Based on the mechanism provided by `filterEvent`, if
        // we insert the filter at the end of the vector it will
        // be applied first which is what we want.
        m_filters.push_back(filter);
      }

      void
      EngineObject::removeEvents(const Event::Type& type) noexcept {
        // Traverse the internal events list and remove the ones with
        // the specified input type.
        std::lock_guard<std::mutex> guard(m_eventsLocker);

        Events::iterator event = m_events.begin();

        while (event != m_events.cend()) {
          // Check the current event's type and remove it if needed.
          // We also try to erase null events just in case we find
          // some, but this should never happen.
          if ((*event) == nullptr || (*event)->getType() == type) {
            event = m_events.erase(event);
          }
          else {
            ++event;
          }
        }
      }

      bool
      EngineObject::handleEvent(EventShPtr e) {
        // Check for degenerate event.
        if (e == nullptr) {
          log(std::string("Dropping invalid null event"), utils::Level::Warning);
          // The event was not recognized.
          return false;
        }

        // Handle the event if this element is active or if it is a show event.
        if (isActive(e->getType())) {
          if (e->getType() != Event::Type::MouseMove) {
            log("Handling " + Event::getNameFromEvent(e), utils::Level::Info);
          }

          // Check the event type and dispatch to the corresponding handler.
          switch (e->getType()) {
            case Event::Type::Enter:
              return enterEvent(*std::dynamic_pointer_cast<EnterEvent>(e));
            case Event::Type::FocusIn:
              return focusInEvent(*std::dynamic_pointer_cast<FocusEvent>(e));
            case Event::Type::FocusOut:
              return focusOutEvent(*std::dynamic_pointer_cast<FocusEvent>(e));
            case Event::Type::GainFocus:
              return gainFocusEvent(*std::dynamic_pointer_cast<FocusEvent>(e));
            case Event::Type::GeometryUpdate:
              return geometryUpdateEvent(*e);
            case Event::Type::Hide:
              return hideEvent(*e);
            case Event::Type::KeyPress:
              return keyPressEvent(*std::dynamic_pointer_cast<KeyEvent>(e));
            case Event::Type::KeyRelease:
              return keyReleaseEvent(*std::dynamic_pointer_cast<KeyEvent>(e));
            case Event::Type::Leave:
              return leaveEvent(*e);
            case Event::Type::LostFocus:
              return lostFocusEvent(*std::dynamic_pointer_cast<FocusEvent>(e));
            case Event::Type::MouseButtonPress:
              return mouseButtonPressEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
            case Event::Type::MouseButtonRelease:
              return mouseButtonReleaseEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
            case Event::Type::MouseMove:
              return mouseMoveEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
            case Event::Type::MouseWheel:
              return mouseWheelEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
            case Event::Type::Repaint:
              return repaintEvent(*std::dynamic_pointer_cast<PaintEvent>(e));
            case Event::Type::Show:
              return showEvent(*e);
            case Event::Type::Resize:
              return resizeEvent(*std::dynamic_pointer_cast<ResizeEvent>(e));
            case Event::Type::WindowEnter:
              return windowEnterEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
            case Event::Type::WindowLeave:
              return windowLeaveEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
            case Event::Type::WindowResize:
              return windowResizeEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
            case Event::Type::Quit:
              return quitEvent(*std::dynamic_pointer_cast<QuitEvent>(e));
            case Event::Type::ZOrderChanged:
              return zOrderChanged(*e);
            default:
              // Event type is not handled, continue the process.
              break;
          }
        }

        // Handle accepted status for this event: if we are the unique receiver we
        // assume we can safely accept it.
        if (isReceiver(*e)) {
          e->accept();
        }

        // Not recognized event.
        return false;
      }

      void
      EngineObject::sortLocalEvents() {
        // Perform a sorting of the internal array so that we can process
        // events more efficiently. We rely on the id provided by the dedicated
        // method to assign a priority to each event type.
        std::sort(
          m_events.begin(),
          m_events.end(),
          [](const EventShPtr& lhs, const EventShPtr& rhs) {
            return getEventID(lhs) > getEventID(rhs);
          }
        );
      }

    }
  }
}
