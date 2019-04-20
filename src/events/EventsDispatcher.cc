
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
        m_eventsQueue(),

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
          if (eventsStillInQueue && event != nullptr) {
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

        // Acquire the events lock.
        std::lock_guard<std::mutex> guard(m_eventsLocker);

        // Handle the events registered in the queue.
        while (!m_eventsQueue.empty()) {
          // Handle this event.
          EventShPtr event = m_eventsQueue.back();

          // Event with type `None` are discarded right away.
          if (event->getType() != Event::Type::None) {
            withSafetyNet(
              [&event, this]() {
                dispatchEvent(event);
              },
              std::string("dispatchEvent")
            );
          }

          m_eventsQueue.pop_back();
        }

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

        // Transmit the event to all listeners.
        for (std::vector<EngineObject*>::iterator listener = m_listeners.begin() ;
            listener != m_listeners.end() ;
            ++listener)
        {
          (*listener)->event(event);
        }
      }

    }
  }
}
