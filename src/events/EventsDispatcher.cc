
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
        m_broadcastEvents(),

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

        // The dispatch of events from queue is divided into two separate parts:
        // 1) Handling broadcast events
        // 2) Handling directed events.
        // Each phase is important but both are not treated almost in the same
        // way. Indeed most of the `broadcast` events are in fact generated by
        // the system while most of the `directed` events are produced by UI
        // elements. It is not uncommon for the processing of a `directed` event
        // to generate more (`directed`) events while it is quite rare for system
        // (i.e. `broadcast` events) to do so. Both types of events might create
        // some new listeners in the process, which need to be forwarded the event
        // which led to their creation.
        // Considering this, we choose to process `directed` events until no more
        // are added (which could take forever) while we only process the system
        // registered at the time of calling this method and none of the potentially
        // newly generated.
        dispatchBroadcastEvents();
        dispatchDirectedEvents();

        // Return the elapsed time.
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
      }

      void
      EventsDispatcher::dispatchBroadcastEvents() {
        // Handle the events registered in the broadcast queue. This function
        // is basically a loop on all the sponatenous registered in the internal
        // queue to send each one of them to the registered listeners.
        // In order not to block the events' queue more than needed, we first
        // copy the internal data of `m_broadcastEvents` into a local variable
        // and then iterate on it.
        // In addition to allowing the system to still produce events while we're
        // processing some (even though we should ideally aim at controlling this
        // fact not to drown in events), it also has the double advantage to
        // allow listeners to react to the events by posting some more events.

        // Copy the events to process into a local variable.
        Events broadcast;

        {
          std::lock_guard<std::mutex> guard(m_eventsLocker);
          broadcast.swap(m_broadcastEvents);
        }

        // Process each event.
        dispatchEvents(broadcast);
      }

      void
      EventsDispatcher::dispatchDirectedEvents() {
        // Now handle the `directed` events: as each listener is able to
        // handle directly the events which are directed towards it, we
        // in fact need to loop through all listeners and trigger the
        // processing of events with the internal method.
        // As listeners may generate new events during this processing,
        // we need to keep looping as long as all events have not been
        // consumed.
        // We can determine whether some listeners still need to process
        // some events with the dedicated `hasEvents` method.
        // In addition to that, events might generate new listeners to
        // register in this dispatcher, which will modify the `m_listeners`
        // lists. We have to copy the listeners in order to allow them to
        // be added.
        // The ordering is the following: when processing an event, we
        // need to pass it to all the listeners created by this event.
        // And when processing an event, we need to continue processing
        // as long as some events have been generated.
        bool allDone = false;

        // Process as long as some events have been added or some listener
        // created.
        do {
          // Loop over the listeners and trigger the processing method
          // for each one of them.
          // In a first approach we assume that we're done. If this is
          // not the case and a listener still has events to process
          // we will change our minds.
          allDone = true;

          int offset = 0;
          bool someListenersAdded = true;

          do {

            // Retrieve existing listeners.
            Listeners existingListeners;
            {
              existingListeners.clear();
              std::lock_guard<std::mutex> guard(m_listenersLocker);
              existingListeners.swap(m_listeners);
            }

            // Process events for the listeners.
            for (int id = offset ; id < static_cast<int>(existingListeners.size()) ; ++id) {
              if (existingListeners[id]->hasEvents()) {
                EngineObject* listener = existingListeners[id];

                withSafetyNet(
                  [&listener]() {
                    listener->processEvents();
                  },
                  std::string("processEvents")
                );
                allDone = false;
              }
            }

            // Check whether some listeners were added.
            {
              std::lock_guard<std::mutex> guard(m_listenersLocker);
              someListenersAdded = !m_listeners.empty();

              // If some listeners were added, merge them with the
              // existing list and then swap it to the internal array
              // so that they can be notified of events.
              if (someListenersAdded) {
                log("Added " + std::to_string(m_listeners.size()) + " listener(s), starting at " + std::to_string(existingListeners.size()) + " for next iteration");
                offset = static_cast<int>(existingListeners.size());
                existingListeners.insert(existingListeners.cend(), m_listeners.cbegin(), m_listeners.cend());
              }

              // Restore internal listeners with existing list to
              // which newly registered have been added.
              m_listeners.swap(existingListeners);
            }

          } while (someListenersAdded);

        } while (!allDone);
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
              dispatchEventToListeners(*event);
            },
            std::string("dispatchEvent")
          );
        }
      }

      void
      EventsDispatcher::dispatchEventToListeners(const EventShPtr event) {
        // Transmit the input `event` and dispatch it to all registered listeners.
        // We only have one special case which is when the `Escape` key is pressed
        // and the internal `m_exitOnEscape` status is ticked: in this case we want
        // to bypass the regular event processing and allow the creation of a quit
        // event and process it as usual.
        // As the event's processing might generate some more listeners (i.e. reveal
        // some previously hidden objects or create entirely new ones), we need to
        // check whether the some have been added. In this case we will loop and
        // transmit the input event to these new listeners.
        // The loop ends when a round is performed without new listeners being
        // created.
        // We also take this opportunity to discard invalid events.

        // Discard `null` events and those with a type set to `None`.
        if (event == nullptr || event->getType() == Event::Type::None) {
          return;
        }

        // Check for key released and try to intercept it to generate a quite event.
        if (interceptEscapeKey(event)) {
          // The event was intercepted, do not process the event itself as it has
          // been converted to a quit event.
          return;
        }

        // Check that the event is actually a broadcast event: otherwise this is a
        // problem as this method is not designed to process such events. Better use
        // the `dispatchEventsForListener` method.
        if (event->isDirected()) {
          // Warn the user and trash the event.
          log("Cannot dispatch event " + Event::getNameFromEvent(event) + " directed towards " + event->getReceiver()->getName(), utils::Level::Warning);
          return;
        }

        // Broadcast the event to all the registered listeners. As we want to allow
        // listeners to be added while processing the listeners array, we cannot
        // just iterate as the iterators will most likely be invalidated if some new
        // listeners are added. Instead we first copy the existing listeners so that
        // each round only transmits the input `event` to the new listeners.
        int offset = 0;
        bool someListenersAdded = true;

        do {
          // Retrieve existing listeners.
          Listeners existingListeners;
          {
            existingListeners.clear();
            std::lock_guard<std::mutex> guard(m_listenersLocker);
            existingListeners.swap(m_listeners);
          }

          // Dispatch the event to the existing listeners. We use the `offset` so that
          // only the listeners which have not yet processed the input `event` receive
          // it in this round.
          for (int id = offset ; id < static_cast<int>(existingListeners.size()) ; ++id) {
            existingListeners[id]->event(event);
          }

          // Check whether some listeners were added.
          {
            std::lock_guard<std::mutex> guard(m_listenersLocker);
            someListenersAdded = !m_listeners.empty();

            // If some listeners were added, merge them with the
            // existing list and then swap it to the internal array
            // so that they can be notified of events.
            if (someListenersAdded) {
              log("Added " + std::to_string(m_listeners.size()) + " listener(s), starting at " + std::to_string(existingListeners.size()) + " for next iteration");
              offset = static_cast<int>(existingListeners.size());
              existingListeners.insert(existingListeners.cend(), m_listeners.cbegin(), m_listeners.cend());
            }

            // Restore internal listeners with existing list to
            // which newly registered have been added.
            m_listeners.swap(existingListeners);
          }

        } while (someListenersAdded);
      }

    }
  }
}
