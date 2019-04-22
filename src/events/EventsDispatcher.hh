#ifndef    EVENTS_DISPATCHER_HH
# define   EVENTS_DISPATCHER_HH

# include <memory>
# include <vector>
# include <thread>
# include <mutex>
# include <core_utils/CoreObject.hh>
# include "Engine.hh"
# include "EngineObject.hh"
# include "EventsQueue.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EventsDispatcher: public utils::CoreObject, public EventsQueue {
        public:

          explicit
          EventsDispatcher(const float& eventHandlingRate = 60.0f,
                          EngineShPtr engine = nullptr,
                          const bool exitOnEscape = true,
                          const std::string& name = std::string("event_dispatcher"));

          ~EventsDispatcher();

          void
          run();

          void
          stop();

          bool
          isRunning();

          // TODO: Add specific kind of listeners ? Like WindowListener for example.
          void
          addListener(EngineObject* listener);

          void
          removeListener(EngineObject* listener) override;

          void
          postEvent(EventShPtr event) override;

        private:

          void
          fetchSystemEvents();

          int
          consumeSystemEvents();

          int
          dispatchEventsFromQueue();

          void
          dispatchEvent(const EventShPtr event);

          void
          trimAndPostSpontaneousEvent(const EventShPtr event);

          void
          trimAndPostDirectedEvent(const EventShPtr event);

        private:

        using Events = std::vector<EventShPtr>;

          float m_framerate;
          float m_frameDuration;
          bool m_exitOnEscape;

          EngineShPtr m_engine;

          bool m_eventsRunning;
          std::mutex m_executionLocker;
          std::shared_ptr<std::thread> m_executionThread;

          std::mutex m_eventsLocker;
          Events m_directedEvents;
          Events m_spontaneousEvents;

          std::vector<EngineObject*> m_listeners;
          std::mutex m_listenersLocker;
      };

      using EventsDispatcherShPtr = std::shared_ptr<EventsDispatcher>;
    }
  }
}

# include "EventsDispatcher.hxx"

#endif    /* EVENTS_DISPATCHER_HH */
