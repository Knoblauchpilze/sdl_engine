
# include "EventsDispatcher.hh"
# include <core_utils/CoreWrapper.hh>
# include "KeyEvent.hh"
# include "QuitEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EventsDispatcher::EventsDispatcher(const float& eventHandlingRate,
                                         EngineShPtr engine,
                                         const bool exitOnEscape,
                                         const std::string& name):
        utils::CoreObject(name),
        EventsQueue(),
        m_framerate(std::max(0.1f, eventHandlingRate)),
        m_frameDuration(1000.0f / m_framerate),
        m_exitOnEscape(exitOnEscape),

        m_engine(engine),

        m_eventsRunning(false),
        m_executionLocker(),
        m_executionThread(nullptr),

        m_eventsLocker(),
        m_spontaneousEvents(),

        m_listenersLocker(),
        m_listeners()
      {
        setService("events");

        if (m_engine == nullptr) {
          error(std::string("Cannot create event handler with null engine"));
        }
      }

      EventsDispatcher::~EventsDispatcher() {
        stop();
      }

      void
      EventsDispatcher::fetchSystemEvents() {
        // Start the event handling.
        m_executionLocker.lock();
        m_eventsRunning = true;
        m_executionLocker.unlock();

        bool stillRunning = true;
        while (stillRunning) {
          stillRunning = isRunning();

          if (!stillRunning) {
            break;
          }

          // Fetch system events.
          int osEventsDuration = consumeSystemEvents();

          // Process events in queue.
          int allEventsDuration = dispatchEventsFromQueue();

          int processingDuration = osEventsDuration + allEventsDuration;

          // Check whether the rendering time is compatible with the desired framerate.
          if (1.0f * processingDuration > m_frameDuration) {
            // Log this problem.
            log(
              std::string("Event handling took ") + std::to_string(processingDuration) + "ms " +
              "which is greater than the " + std::to_string(m_frameDuration) + "ms " +
              " authorized to maintain " + std::to_string(m_framerate) + "fps",
              utils::Level::Warning
            );

            // Move on to the next frame.
            continue;
          }

          // Sleep for the remaining time to complete a frame if there's enough time left.
          const unsigned int remainingDuration = m_frameDuration - processingDuration;
          if (remainingDuration > 3u) {
            std::this_thread::sleep_for(std::chrono::milliseconds(remainingDuration));
          }
        }

        log(std::string("Exiting events thread"), utils::Level::Notice);
      }

      int
      EventsDispatcher::consumeSystemEvents() {
        // Poll events until we deplete the queue.
        bool eventsStillInQueue = true;

        // Start time measurement.
        auto start = std::chrono::steady_clock::now();

        while (eventsStillInQueue) {
          EventShPtr event = m_engine->pollEvent(eventsStillInQueue);

          // Enqueue this event if it is relevant.
          if (eventsStillInQueue && event != nullptr && event->getType() != Event::Type::None) {
            postEvent(event);
          }
        }

        // Return the elapsed time.
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
      }

      int
      EventsDispatcher::dispatchEventsFromQueue() {
        // Start time measurement.
        auto start = std::chrono::steady_clock::now();

        // The dispatch of events from queue is divided into two
        // separate parts:
        // 1) Handling spontaneous events
        // 2) Handling directed events.
        // Each phase is important but both are not treated exactly
        // in the same way.
        // Indeed most of the `spontaneous` events are in fact
        // generated by the system while most of the `directed` events
        // are produced by UI elements.
        // It is not uncommon for the processing of a `directed` event
        // to generate more (`directed`) events while it is quite rare
        // for `spontaneous` to do so.
        // Considering this, we choose to process `directed` events
        // until no more are added (which could take forever) while
        // we only process the `spontaneous` registered at the time of
        // calling this method and none of the potentially newly
        // generated.

        // First handle `spontaneous` events.
        dispatchSpontaneousEvents();

        // Now handle the `directed` events: as each listener is able to
        // handle directly the events which are directed towards it, we
        // in fact need to loop through all listeners and trigger the
        // processing of events with the internal method.
        // As listeners may generate new events during this processing,
        // we need to keep looping as long as all events have not been
        // consumed.
        // We can determine whether some listeners still need to process
        // some events with the dedicated `hasEvents` method.
        bool allDone = false;

        do {
          // Loop over the listeners and trigger the processing method
          // for each one of them.
          std::lock_guard<std::recursive_mutex> guard(m_listenersLocker);

          // In a first approach we assume that we're done. If this is
          // not the case and a listener still has events to process
          // we will change our minds.
          allDone = true;

          for (Listeners::iterator listener = m_listeners.begin() ;
              listener != m_listeners.end() ;
              ++listener)
          {
            if ((*listener)->hasEvents()) {
              withSafetyNet(
                [&listener]() {
                  (*listener)->processEvents();
                },
                std::string("processEvents")
              );
              allDone = false;
            }
          }

          // Loop until no more events are pending in any of the listeners.
        } while (!allDone);

        // Return the elapsed time.
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
      }

      void
      EventsDispatcher::dispatchSpontaneousEvents() {
        // Handle the events registered in the spontaneous queue. This function
        // is basically a loop on all the sponatenous registered in the internal
        // queue to send each one of them to the registered listeners.
        // In order not to block the events' queue more than needed, we first
        // copy the internal data of `m_spontaneousEvents` into a local variable
        // and then iterate on it.
        // In addition to allowing the system to still produce events while we're
        // processing some (even though we should ideally aim at controlling this
        // fact not to drown in events), it also has the double advantage to
        // allow listeners to react to the events by posting some more events.

        // Copy the events to process into a local variable.
        Events spontaneous;

        {
          std::lock_guard<std::mutex> guard(m_eventsLocker);
          spontaneous.swap(m_spontaneousEvents);
        }

        // Process each event.
        dispatchEvents(spontaneous);
      }

      void
      EventsDispatcher::dispatchEvents(const Events& events) {
        // Iterate over the input array of events and dispatch each one of them.
        for (Events::const_iterator event = events.cbegin() ;
             event != events.cend() ;
             ++event)
        {
          withSafetyNet(
            [&event, this]() {
              dispatchEvent(*event);
            },
            std::string("dispatchEvent")
          );
        }
      }

      void
      EventsDispatcher::dispatchEvent(const EventShPtr event) {
        // Transmit the input `event` and dispatch it to all registered listeners.
        // We only have one special case which is when the `Escape` key is pressed
        // and the internal `m_exitOnEscape` status is ticked: in this case we want
        // to bypass the regular event processing and allow the creation of a quit
        // event and process it as usual.

        // Discard events with `None` type.
        if (event->getType() == Event::Type::None) {
          return;
        }

        // Check for key released.
        if (event->getType() == Event::Type::KeyRelease) {
          // Check the key which was pressed.
          std::shared_ptr<KeyEvent> keyEvent = std::dynamic_pointer_cast<KeyEvent>(event);

          // If the conversion was successful and that it corresponds to the `Escape`
          // key, we need to check the internal status to determine the next action.
          if (keyEvent != nullptr && keyEvent->isEscape() && m_exitOnEscape) {
            // Replace the input event with a quit event.
            dispatchEvent(std::make_shared<QuitEvent>());

            // All is well.
            return;
          }

          // Continue to standard processing.
        }

        // Transmit the event to all listeners or to only the receiver if the event
        // is spontaneous.
        if (!event->isSpontaneous()) {
          // Dispatch the event to the receiver.
          log("Dispatching " + Event::getNameFromEvent(event) + " for " + event->getReceiver()->getName());
          event->getReceiver()->event(event);
          return;
        }

        // The event is not spontaneous, transmit it to all listeners.
        std::lock_guard<std::recursive_mutex> guard(m_listenersLocker);
        for (Listeners::iterator listener = m_listeners.begin() ;
            listener != m_listeners.end() ;
            ++listener)
        {
          (*listener)->event(event);
        }
      }

      void
      EventsDispatcher::trimAndPostSpontaneousEvent(EventShPtr e) {
        // No particular control is performed for spontaneous event. These events
        // are supposed to be generated by the OS and thus we assume a filtering
        // already takes place to keep only relevant events and drop the rest.
        log("Broadcasting " + Event::getNameFromEvent(e));
        m_spontaneousEvents.push_back(e);
      }

      void
      EventsDispatcher::trimAndPostDirectedEvent(EventShPtr e) {
        // We know that this event is directed to a specific receiver.
        // We just have to call the dedicated handler on the receiver
        // and we're done.
        // Some high level checks are also performed.

        if (e == nullptr || e->getType() == Event::Type::None) {
          // Do not bother with this event.
          return;
        }

        // Check whether the event actually has a receiver.
        if (e->getReceiver() == nullptr) {
          error(
            std::string("Could not post directed event of type \"") + Event::getNameFromEvent(e) + "\"",
            std::string("Invalid null receiver")
          );
        }

        // Post the event to the correct receiver.
        e->getReceiver()->postLocalEvent(e);
      }

    }
  }
}
