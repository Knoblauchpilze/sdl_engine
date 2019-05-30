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

          void
          postEvent(EventShPtr event) override;

          /**
           * @brief - Performs the insertion of the input object as listeners of this queue.
           *          This allows the `listener` to receive all the events processed by this
           *          queue and to be scheduled regularly for events processing.
           *          Note that an error is raised if the listener is not valid or already
           *          existing in this queue.
           *          TODO: Add specific kind of listeners ? Like `WindowListener` for example.
           * @param listener - the object which should be added as a listener of this queue.
           */
          void
          addListener(EngineObject* listener) override;

          void
          removeListener(EngineObject* listener) override;

        private:

          using Events = std::vector<EventShPtr>;
          using Listeners = std::vector<EngineObject*>;

          void
          fetchSystemEvents();

          int
          consumeSystemEvents();

          int
          dispatchEventsFromQueue();

          void
          dispatchSpontaneousEvents();

          void
          dispatchEvents(const Events& events);

          void
          dispatchEvent(const EventShPtr event);

          void
          trimAndPostSpontaneousEvent(EventShPtr e);

          void
          trimAndPostDirectedEvent(EventShPtr e);

        private:

          float m_framerate;
          float m_frameDuration;
          bool m_exitOnEscape;

          EngineShPtr m_engine;

          bool m_eventsRunning;
          std::mutex m_executionLocker;
          std::shared_ptr<std::thread> m_executionThread;

          std::mutex m_eventsLocker;
          Events m_spontaneousEvents;

          std::mutex m_listenersLocker;
          Listeners m_listeners;
      };

      using EventsDispatcherShPtr = std::shared_ptr<EventsDispatcher>;
    }
  }
}

# include "EventsDispatcher.hxx"

#endif    /* EVENTS_DISPATCHER_HH */
