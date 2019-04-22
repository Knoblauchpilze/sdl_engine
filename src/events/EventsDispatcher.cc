
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
        m_directedEvents(),
        m_spontaneousEvents(),

        m_listeners(),
        m_listenersLocker()
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

        // Handle the events registered in the queue.
        // As some events might generate new ones, we need
        // to keep looping until no more events are produced.
        // Note that events that can be produced while
        // we're processing some other events should only be
        // directed events to be processed in the same frame.
        // If this is not the case it will be processed in
        // a subsequent frame.
        // In order not to lock the events queue (and thus
        // preventing elements to emit new events while we are
        // processing the existing ones, we need to copy the
        // queue into a local variable.
        Events events;

        {
          std::lock_guard<std::mutex> guard(m_eventsLocker);
          events.swap(m_spontaneousEvents);
        }

        // First broadcast spontaneous events.
        for (Events::const_iterator event = events.cbegin() ;
             event != events.cend() ;
             ++event)
        {
          // Event with type `None` are discarded right away.
          if ((*event)->getType() != Event::Type::None) {
            dispatchEvent(*event);
          }
        }
        events.clear();

        // Now process directed events. As we may have to handle
        // newly created events we need to keep looping until no
        // more events are produced.
        do {
          // Retrieve the queue into an internal variable so
          // that we can release the lock and allow components
          // to post new events.
          {
            std::lock_guard<std::mutex> guard(m_eventsLocker);
            events.swap(m_directedEvents);
          }

          // Process each event.
          for (unsigned idEvent = 0u ; idEvent < events.size() ; ++idEvent) {
            // Handle this event.
            EventShPtr event = events[idEvent];

            // Event with type `None` are discarded right away.
            if (event->getType() != Event::Type::None) {
              withSafetyNet(
                [&event, this]() {
                  dispatchEvent(event);
                },
                std::string("dispatchEvent")
              );
            }
          }

          // Clear processed events.
          events.clear();

        } while (!m_directedEvents.empty());

        // Return the elapsed time.
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
      }

      void
      EventsDispatcher::dispatchEvent(const EventShPtr event) {
        // This function basically transmits the `event` to all the registered
        // listeners.
        // We only have one special case which is when the `Escape` key is pressed
        // and the internal `m_exitOnEscape` status is ticked: in this case we want
        // to bypass the regular event processing and allow the creation of a quit
        // event and process it as usual.

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
        // log("Dispatching " + Event::getNameFromEvent(event));
        for (std::vector<EngineObject*>::iterator listener = m_listeners.begin() ;
            listener != m_listeners.end() ;
            ++listener)
        {
          (*listener)->event(event);
        }
      }

      void
      EventsDispatcher::trimAndPostSpontaneousEvent(const EventShPtr event) {
        // No particular control is performed for spontaneous event. These events
        // are supposed to be generated by the OS and thus we assume a filtering
        // already takes place to keep only relevant events and drop the rest.
        log("Broadcasting " + Event::getNameFromEvent(event));
        m_spontaneousEvents.push_back(event);
      }

      void
      EventsDispatcher::trimAndPostDirectedEvent(const EventShPtr event) {
        // We need to check whether a similar event already exists with the same
        // receiver and the same data already exists.
        // If this is the case, we can drop this event as it would result in a
        // duplicated processing.

        // Traverse the directed events queue and check for existing elements.
        bool duplicated = false;

        Events::const_iterator existing = m_directedEvents.cbegin();
        while (!duplicated && existing != m_directedEvents.cend()) {
          duplicated = ((**existing) == *event);
          ++existing;
        }

        // Check whether this event is duplicated.
        if (duplicated) {
          // Drop the event.
          log("Dropping " + Event::getNameFromEvent(event) + " for " + event->getReceiver()->getName());
          return;
        }

        // Queue the event.
        log("Queuing " + Event::getNameFromEvent(event) + " for " + event->getReceiver()->getName());
        m_directedEvents.push_back(event);
      }

    }
  }
}
