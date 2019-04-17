#ifndef    EVENT_LISTENER_HXX
# define   EVENT_LISTENER_HXX

# include <algorithm>
# include "EngineObject.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EngineObject::~EngineObject() {
        // Unregister from the event queue if any has been provided.
        if (m_queue != nullptr) {
          m_queue->removeListener(this);
        }
      }

      inline
      void
      EngineObject::removeEventFilter(EngineObjectShPtr filter) {
        // Use the dedicated handler.
        removeFilter(findFilter(filter));
      }

      inline
      bool
      EngineObject::filterEvent(EngineObject* /*watched*/,
                                 EventShPtr /*e*/)
      {
        // No filtering provided here, return false.
        return false;
      }

      inline
      void
      EngineObject::setEventsQueue(EventsQueue* queue) noexcept {
        m_queue = queue;
      }

      inline
      bool
      EngineObject::handleEvent(EventShPtr /*e*/) {
        // No handling provided, assume the event has been recognized.
        return true;
      }

      inline
      void
      EngineObject::postEvent(EventShPtr e) noexcept {
        // Check event coherence.
        if (e == nullptr) {
          log(
            std::string("Cannot post empty event in queue"),
            utils::Level::Warning
          );
          return;
        }

        // Check whether a queue is provided.
        if (m_queue == nullptr) {
          log(
            std::string("Cannot post event of type ") + std::to_string(static_cast<int>(e->getType())) + ", no queue provided",
            utils::Level::Warning
          );
          return;
        }

        m_queue->postEvent(e);
      }

      inline
      EngineObject::Filter
      EngineObject::findFilter(EngineObjectShPtr filter) const {
        // Traverse the registered filter and try to find the input `filter`.
        Filter internalFilter = m_filters.cbegin();

        while (validFilter(internalFilter) && *internalFilter != filter) {
          ++internalFilter;
        }

        return internalFilter;
      }

      inline
      bool
      EngineObject::validFilter(const Filter& filter) const noexcept {
        return filter != m_filters.cend();
      }

      inline
      void
      EngineObject::removeFilter(const Filter& filter) {
        // Check whether this filter is valid.
        if (validFilter(filter)) {
          // Remove it.
          m_filters.erase(filter);
        }
      }

    }
  }
}

#endif    /* EVENT_LISTENER_HXX */
