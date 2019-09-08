#ifndef    EVENT_LISTENER_HXX
# define   EVENT_LISTENER_HXX

# include <algorithm>
# include "EngineObject.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EngineObject::~EngineObject() {
        // Unregister from the event queue if any has been provided.
        if (m_queue != nullptr) {
          m_queue->removeListener(this);
        }
      }

      inline
      void
      EngineObject::removeEventFilter(EngineObject* filter) {
        // Use the dedicated handler.
        removeFilter(findFilter(filter));
      }

      inline
      bool
      EngineObject::filterEvent(EngineObject* /*watched*/,
                                 EventShPtr /*e*/)
      {
        // No filtering provided here, return false.
        return false;
      }

      inline
      void
      EngineObject::setEventsQueue(EventsQueue* queue) noexcept {
        // Register the queue in the internal attribute.
        m_queue = queue;

        // Add this object as listener of the queue.
        if (m_queue != nullptr) {
          m_queue->addListener(this);
        }
      }

      inline
      bool
      EngineObject::hasEvents(const EventProcessingPass& pass) {
        // Lock the mutex to access events.
        std::lock_guard<std::mutex> guard(m_eventsLocker);

        // Traverse the internal list of events and search for one belonging
        // to the input pass.
        Events::const_iterator e = m_events.cbegin();

        while (e != m_events.cend()) {
          if (belongsToPass((*e)->getType(), pass)) {
            return true;
          }

          ++e;
        }

        // No events corresponding to the input pass.
        return false;
      }

      inline
      void
      EngineObject::disableEventsProcessing() noexcept {
        // Loop on all valid event types and deactivate them if needed.
        Event::Types all = Event::getAllEvents();
        for (Event::Types::const_iterator it = all.cbegin() ;
             it != all.cend() ;
             ++it)
        {
          setActive(*it, staysActiveWhileDisabled(*it));
        }
      }

      inline
      bool
      EngineObject::staysActiveWhileDisabled(const Event::Type& type) const noexcept {
        // By default no events stays active when the object is disabled except for `Show`
        // event otherwise we would have a hard time reactivating some elements.
        return type == Event::Type::Show;
      }

      inline
      void
      EngineObject::activateEventsProcessing() noexcept {
        // Loop on all valid event types and activate them if needed.
        Event::Types all = Event::getAllEvents();
        for (Event::Types::const_iterator it = all.cbegin() ;
             it != all.cend() ;
             ++it)
        {
          setActive(*it, !staysInactiveWhileEnabled(*it));
        }
      }

      inline
      bool
      EngineObject::staysInactiveWhileEnabled(const Event::Type& /*type*/) const noexcept {
        // By default no events stays inactive when the object is enabled.
        return false;
      }

      inline
      bool
      EngineObject::isActive(const Event::Type& type) const noexcept {
        return m_handledTypes.find(type) == m_handledTypes.cend();
      }

      inline
      void
      EngineObject::registerToSameQueue(EngineObject* other) {
        // Check that the `other` object is valid.
        if (other == nullptr) {
          error(
            std::string("Cannot register object to same events queue"),
            std::string("Invalid null object")
          );
        }

        // Register the `other` to the queue only if our own events queue is
        // valid (i.e. not null) and if it is not already the queue of the
        // other object.
        if (m_queue != nullptr && m_queue != other->m_queue) {
          other->setEventsQueue(m_queue);
        }
      }

      inline
      bool
      EngineObject::isReceiver(const Event& e) const noexcept {
        return e.isReceivedBy(this);
      }

      inline
      bool
      EngineObject::isEmitter(const Event& e) const noexcept {
        return e.isEmittedBy(this);
      }

      inline
      bool
      EngineObject::enterEvent(const EnterEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::focusInEvent(const FocusEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::focusOutEvent(const FocusEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::gainFocusEvent(const FocusEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::geometryUpdateEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::hideEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyboardGrabbedEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyboardReleasedEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyPressEvent(const KeyEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyReleaseEvent(const KeyEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::leaveEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::lostFocusEvent(const FocusEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseButtonPressEvent(const MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseButtonReleaseEvent(const MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseMoveEvent(const MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseWheelEvent(const MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::repaintEvent(const PaintEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::resizeEvent(ResizeEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::showEvent(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowEnterEvent(const WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowLeaveEvent(const WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowResizeEvent(const WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::quitEvent(const QuitEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::zOrderChanged(const Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      EngineObject::Filter
      EngineObject::findFilter(EngineObject* filter) const {
        // Traverse the registered filter and try to find the input `filter`.
        Filter internalFilter = m_filters.cbegin();

        while (validFilter(internalFilter) && *internalFilter != filter) {
          ++internalFilter;
        }

        return internalFilter;
      }

      inline
      bool
      EngineObject::validFilter(const Filter& filter) const noexcept {
        return filter != m_filters.cend();
      }

      inline
      void
      EngineObject::removeFilter(const Filter& filter) {
        // Check whether this filter is valid.
        if (validFilter(filter)) {
          // Remove it.
          m_filters.erase(filter);
        }
      }

      inline
      void
      EngineObject::setActive(const Event::Type& type,
                              const bool active) noexcept
      {
        // Check whether this type is meant to be activated or deactivated.
        if (active) {
          // We should try to remove the input `type` from the internal
          // filter.
          Event::Types::iterator it = m_handledTypes.find(type);

          if (it == m_handledTypes.end()) {
            return;
          }

          m_handledTypes.erase(it);
        }
        else {
          // Insert the input `type` into the internal filter.
          Event::Types::iterator it = m_handledTypes.find(type);

          if (it != m_handledTypes.end()) {
            return;
          }

          m_handledTypes.insert(type);
        }
      }

    }
  }
}

#endif    /* EVENT_LISTENER_HXX */
