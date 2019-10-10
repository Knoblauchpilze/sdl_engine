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
      EventsDispatcher::postEvent(EventShPtr e) {
        // Check whether this event is valid: we discard null events and
        // events with an invalid type.
        if (e == nullptr || e->getType() == Event::Type::None) {
          // No need to go further.
          return;
        }

        // Update the events processing pass based on the type of the input
        // event to post. There are several cases possible:
        //  1) the event is a visibility event and we're set for the rest
        //  2) the event is not a visibility event and we're set for the rest
        //  3) the event is a visibility event and we're set for the visibility
        //  4) the event is not a visibility event and we're set for the visibility
        // We can see that only the case one will trigger an update of the internal
        // processing pass.
        if (getCurrentProcessingPass() == EventProcessingPass::Rest &&
            belongsToPass(e->getType(), EventProcessingPass::Visibility))
        {
          setCurrentProcessingPass(EventProcessingPass::Visibility);
        }

        // Acquire the events lock.
        std::lock_guard<std::mutex> guard(m_eventsLocker);

        // Post the event in the relevant queue based on whether it is
        // spontaneous or directed to a particular element.
        if (e->isDirected()) {
          // Post the event to the receiver indicated by the event. We
          // are sure that it is valid with the above line.
          e->getReceiver()->postLocalEvent(e);
        }
        else {
          // The event does not have any precise destination: we will
          // broadcast it to all the listeners so add it to the internal
          // queue.
          m_broadcastEvents.push_back(e);
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

      inline
      bool
      EventsDispatcher::interceptEscapeKey(const EventShPtr event) {
        // In order for the event to be intercepted we have to check that
        // the event is a key release and that this object is configured
        // to intercept events in the first place.
        if (m_exitOnEscape && event->getType() == Event::Type::KeyRelease) {
          // This is a key release event and we can intercept events, let's
          // determine which key was released.
          std::shared_ptr<KeyEvent> keyEvent = std::dynamic_pointer_cast<KeyEvent>(event);

          // If the conversion was successful and that it corresponds to the `Escape`
          // key, we need to check the internal status to determine the next action.
          if (keyEvent != nullptr && keyEvent->getRawKey() == Key::Escape && m_exitOnEscape) {
            // Replace the input event with a quit event.
            dispatchEventToListeners(std::make_shared<QuitEvent>());

            // We successfully intercepted the release of the escape key.
            return true;
          }
        }

        // No interception, continue to standard processing.
        return false;
      }

      inline
      const EventProcessingPass&
      EventsDispatcher::getCurrentProcessingPass() const noexcept {
        return m_pass;
      }

      inline
      void
      EventsDispatcher::setCurrentProcessingPass(const EventProcessingPass& pass) noexcept {
        m_pass = pass;
      }

    }
  }
}

#endif    /* EVENT_DISPATCHER_HXX */
