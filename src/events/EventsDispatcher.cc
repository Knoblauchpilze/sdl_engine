
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

        // The dispatch of events from queue is divided into two
        // separate parts:
        // 1) Handling broadcast events
        // 2) Handling directed events.
        // Each phase is important but both are not treated exactly
        // in the same way.
        // Indeed most of the `broadcast` events are in fact
        // generated by the system while most of the `directed` events
        // are produced by UI elements.
        // It is not uncommon for the processing of a `directed` event
        // to generate more (`directed`) events while it is quite rare
        // for `broadcast` to do so.
        // Considering this, we choose to process `directed` events
        // until no more are added (which could take forever) while
        // we only process the `broadcast` registered at the time of
        // calling this method and none of the potentially newly
        // generated.

        // First handle `broadcast` events.
        dispatchBroadcastEvents();

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

        // Process as long as some events have been added.
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
        // is directed.
        if (event->isDirected()) {
          // Dispatch the event to the receiver.
          log("Dispatching " + Event::getNameFromEvent(event) + " for " + event->getReceiver()->getName());
          event->getReceiver()->event(event);
          return;
        }

        // The event is not directed, transmite it to all listeners. As some new
        // listeners might be added to this dispatcher, we cannot just loop through
        // the internal `m_listeners` array. We have to copy its value into a new
        // elements and then iterate over the copy.
        // We continue looping as long as listeners have been added.
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

      void
      EventsDispatcher::trimAndPostBroadcastEvent(EventShPtr e) {
        // No particular control is performed for broadcast event. These events
        // are supposed to be generated by the OS and thus we assume a filtering
        // already takes place to keep only relevant events and drop the rest.
        if (e->getType() != Event::Type::MouseMove) {
          log("Broadcasting " + Event::getNameFromEvent(e));
        }
        m_broadcastEvents.push_back(e);
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
