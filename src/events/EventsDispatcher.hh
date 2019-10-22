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
          EventsDispatcher(float eventHandlingRate = 60.0f,
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

          /**
           * @brief - Generic method used to post an event to be processed either by all the
           *          listeners registered by this method or by a specific one. This method
           *          does perform some checks to discard invalid events and request a valid
           *          insertion of the event (either in the internal queue or in the queue of
           *          the targeted listener).
           * @param e - the event to be posted.
           */
          void
          postEvent(EventShPtr e) override;

          /**
           * @brief - Performs the insertion of the input object as listeners of this queue.
           *          This allows the `listener` to receive all the events processed by this
           *          queue and to be scheduled regularly for events processing.
           *          Note that an error is raised if the listener is not valid or already
           *          existing in this queue.
           * @param listener - the object which should be added as a listener of this queue.
           */
          void
          addListener(EngineObject* listener) override;

          void
          removeListener(EngineObject* listener) override;

        private:

          using Events = std::vector<EventShPtr>;
          using Listeners = std::vector<EngineObject*>;

          /**
           * @brief - Threadable method which is launched whenever the `run` method is called
           *          on an events dispatcher object. It will periodically triggers a fetching
           *          of the system events and consume them by asking the registered listeners
           *          to process them.
           *          Note that the rate at which events are consumed and processed depends on
           *          the internal `m_framerate` attribute.
           */
          void
          fetchSystemEvents();

          /**
           * @brief - This method queries the underlying events API and post each fetched event
           *          to the queue of each individual listener. Each system event is created as
           *          not directed (i.e. no specific receiver) and no particular emitter (the
           *          system is not a valid destination for events).
           *          In order to guarantee a certain framerate we return the time took by the
           *          method to be executed.
           * @return - returns the duration of this method expressed in milliseconds.
           */
          int
          consumeSystemEvents();

          /**
           * @brief - Used to handle an event dispatch cycle. This method is called by the main
           *          events thread once per tick, right after gathering the system event through
           *          the `consumeSystemEvents` method.
           *          It handles both the dispatch of system events and the directed events to
           *          all the listeners registered in this queue. It also handles the processing
           *          of events created during the processing of existing events. It cycles until
           *          no more listeners are created and no more events are generated. Note that
           *          this method is blocking and might halt the events processing thread if it
           *          takes too long to execute.
           *          Note that we still give some time measurement statistics about the execution
           *          of this method upon returning.
           * @return - returns the duration of this method expressed in milliseconds.
           */
          int
          dispatchEventsFromQueue();

          /**
           * @brief - Convenience method which allows to retrieve the system events registered
           *          in this queue and call a dispatch method on all of them. This method does
           *          call the `dispatchEvents` internally.
           */
          void
          dispatchBroadcastEvents();

          /**
           * @brief - Convenience method which allows to dispatch the events directed to specific
           *          listeners. As these events are stored directly in the private queue of the
           *          listeners, we have to iterate over the registered listeners and call the
           *          dedicated method for each one of them.
           *          Some events might be generated during the process so we continue until we
           *          complete a full round with no new event generated.
           */
          void
          dispatchDirectedEvents();

          /**
           * @brief - Iterates through the input array of events and send each one to all the
           *          listeners registered in this object using the `dispatchEvent` method. It
           *          also provide some error protection by using a safety net before calling
           *          the `dispatchEvent`: this ensure that no matter the errors raised during
           *          the events procesing we will not crash the events processing thread.
           * @param events - the list of events to process.
           */
          void
          dispatchEvents(const Events& events);

          /**
           * @brief - Dispatch the input event to all the listeners registered in this queue.
           *          The type of the event and its validity is checked before actually sending
           *          it to the listeners.
           *          In case the events generates the creation of new listeners this method
           *          loops until one round is executed without creation of new listeners.
           *          Note that unlike the `dispatchDirectedEvents`, this method focuses on
           *          processing a single event. It is usually linked to the processing of
           *          system event which have no particular source or target. Events which are
           *          targeted to a single listener are discarded by this function.
           * @param event - the event to transmit.
           */
          void
          dispatchEventToListeners(const EventShPtr event);

          /**
           * @brief - Used to intercept a key press on the escape key and trigger a quit event
           *          if this dispatcher is configured to do so.
           *          The return value indicates whether the event was successfully intercepted
           *          in which case the parent process can discard further operations.
           *          Note that we assume that the input `event` is valid and thus we don't do
           *          any checks to ensure this fact.
           * @param event - the event which might be a key press on the escape key.
           * @return - `true` if the input event corresponded to an interceptable key press on
           *           the escape key and `false` otherwise.
           */
          bool
          interceptEscapeKey(const EventShPtr event);

          /**
           * @brief - Used to retrieve the current value of the `m_pass` attribute. The mutex
           *          related to it is locked (so we assume it is not already locked beforehand)
           *          and the return value should be used carefully as it might not stay valid
           *          long.
           * @return - the value of the `m_pass` internal attribute upon entering this method.
           */
          const EventProcessingPass&
          getCurrentProcessingPass() const noexcept;

          /**
           * @brief - Assigns a new value for the current events processing pass. Performs a lock
           *          of the associated mutex before setting the value.
           * @param pass - the new events processing pass to assign.
           */
          void
          setCurrentProcessingPass(const EventProcessingPass& pass) noexcept;

        private:

          float m_framerate;
          float m_frameDuration;
          bool m_exitOnEscape;

          EngineShPtr m_engine;

          bool m_eventsRunning;
          std::mutex m_executionLocker;
          std::shared_ptr<std::thread> m_executionThread;

          std::mutex m_eventsLocker;
          Events m_broadcastEvents;

          /**
           * @brief - Indicates which events processing pass should be processed. This variable plays
           *          a double role during the events processing loop.
           *          When the dispatching of events is triggered it serves as a small optimization
           *          to prevent some passes to be executed when not needed. For example if none of
           *          the elements have some visibility related events registered there's no need to
           *          start the processing at this step.
           *          It also serves WHILE processing the events to detect when some events processing
           *          triggers the creation of an event in an anterior pass: we should then go back to
           *          the pass in order to process the highest priority events first.
           */
          EventProcessingPass m_pass;

          /**
           * @brief - This mutex is meant to protect the access to the `m_listeners` array.
           */
          std::mutex m_listenersLocker;

          /**
           * @brief - Holds all the registered listeners of this dispatcher. Note that the fact that
           *          this is implemented using a vector actually allows to provide some sort of
           *          orederings in events.
           *          Let's consider the following situation: a widget and its layout. The widget will
           *          presumably be created before the layout. So when the widget will be assigned an
           *          events queue, it will be registered as a listener of the queue. It will then
           *          proceed to registering its layout, which will thus be stored *after* the widget
           *          in this vector.
           *          This is important because when this dispatcher will process events, it will
           *          traverse the listeners *in order* and process events of each one sequentially.
           *          This way of doing guarantee that the events generated by the widget will be
           *          processed before the events generated by the layout. In this sense order matters.
           *          It is not necessarily a bad thing but it is important to keep that in mind so
           *          because it hides some potentially weird side effects.
           *          As an example if the layout is added before the widget, at some point the layout
           *          will process its geometry event, and do so with an invalid size because the
           *          event responsible for providing a valid size to the widget has not yet been
           *          processed.
           */
          Listeners m_listeners;
      };

      using EventsDispatcherShPtr = std::shared_ptr<EventsDispatcher>;
    }
  }
}

# include "EventsDispatcher.hxx"

#endif    /* EVENTS_DISPATCHER_HH */
