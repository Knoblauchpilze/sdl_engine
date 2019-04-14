#ifndef    EVENT_LISTENER_HXX
# define   EVENT_LISTENER_HXX

# include <algorithm>
# include "EventListener.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EventListener::~EventListener() {}

      inline
      void
      EventListener::removeEventFilter(EventListenerShPtr filter) {
        // Use the dedicated handler.
        removeFilter(findFilter(filter));
      }

      inline
      bool
      EventListener::filterEvent(EventListener* /*watched*/,
                                 EventShPtr /*e*/)
      {
        // No filtering provided here, return false.
        return false;
      }

      inline
      bool
      EventListener::handleEvent(EventShPtr /*e*/) {
        // No handling provided, assume the event has been recognized.
        return true;
      }

      inline
      EventListener::Filter
      EventListener::findFilter(EventListenerShPtr filter) const {
        // Traverse the registered filter and try to find the input `filter`.
        Filter internalFilter = m_filters.cbegin();

        while (validFilter(internalFilter) && *internalFilter != filter) {
          ++internalFilter;
        }

        return internalFilter;
      }

      inline
      bool
      EventListener::validFilter(const Filter& filter) const noexcept {
        return filter != m_filters.cend();
      }

      inline
      void
      EventListener::removeFilter(const Filter& filter) {
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
