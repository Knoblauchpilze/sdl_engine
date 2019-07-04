#ifndef    EVENTS_DISPATCHER_HXX
# define   EVENTS_DISPATCHER_HXX

# include "EventsDispatcher.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      void
      EventsDispatcher::run() {
        std::lock_guard<std::mutex> guard(m_executionLocker);
        if (m_executionThread != nullptr) {
          error(
            std::string("Cannot start event handling"),
            std::string("Process already running")
          );
        }

        m_executionThread = std::make_shared<std::thread>(
          &EventsDispatcher::fetchSystemEvents,
          this
        );
      }

      inline
      void
      EventsDispatcher::stop() {
        m_executionLocker.lock();
        if (m_executionThread == nullptr) {
          // No need to do anything, process not started.
          m_executionLocker.unlock();
          return;
        }

        m_eventsRunning = false;
        m_executionLocker.unlock();
        m_executionThread->join();

        std::lock_guard<std::mutex> guard(m_executionLocker);
        m_executionThread.reset();
      }

      inline
      bool
      EventsDispatcher::isRunning() {
        std::lock_guard<std::mutex> guard(m_executionLocker);
        return m_eventsRunning;
      }

      inline
      void
      EventsDispatcher::postEvent(EventShPtr event) {
        // Check whether this event is valid.
        if (event == nullptr) {
          // No need to go further.
          return;
        }

        // Acquire the events lock.
        std::lock_guard<std::mutex> guard(m_eventsLocker);

        // Post the event in the relevant queue based on whether it is
        // spontaneous or directed to a particular element.
        // In order not to queue several events with similar content
        // we use a dedicated handler.
        if (event->isDirected()) {
          trimAndPostDirectedEvent(event);
        }
        else {
          trimAndPostBroadcastEvent(event);
        }
      }

      inline
      void
      EventsDispatcher::addListener(EngineObject* listener) {
        // Check whether this listener is valid.
        if (listener == nullptr) {
          error(
            std::string("Cannot add event listener"),
            std::string("Invalid null listener")
          );
        }

        std::lock_guard<std::mutex> guard(m_listenersLocker);

        // Loop through existing listeners to detect whether this `listener`
        // is already registered for this queue.
        for (Listeners::const_iterator existing = m_listeners.cbegin() ;
             existing != m_listeners.cend() ;
             ++existing)
        {
          if (*existing == listener) {
            error(
              std::string("Cannot add event listener \"" + listener->getName() + "\""),
              std::string("Listener already registered")
            );
          }
        }

        // Insert it into the internal list of listeners.
        m_listeners.push_back(listener);
      }

      inline
      void
      EventsDispatcher::removeListener(EngineObject* listener) {
        if (listener == nullptr) {
          error(
            std::string("Cannot remove event listener"),
            std::string("Invalid null listener")
          );
        }

        std::lock_guard<std::mutex> guard(m_listenersLocker);
        std::remove_if(m_listeners.begin(), m_listeners.end(),
          [&listener](EngineObject* internalListener) {
            return &*(listener) == &(*internalListener);
          }
        );

        // We also need to remove all the events associated to this
        // listener: it is done by directly calling the appropriate
        // method on the listener to remove.
        listener->clearEvents();
      }

    }
  }
}

#endif    /* EVENT_DISPATCHER_HXX */
