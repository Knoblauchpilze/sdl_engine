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
      bool
      EventListener::handleEvent(Event* /*e*/) {
        // No event handling here, mark this event as "not processed".
        return false;
      }

      inline
      void
      EventListener::installEventFilter(EventListener* filter) {
        // Check filter validity.
        if (filter == nullptr) {
          log(
            std::string("Cannot install event filter, invalid null filter"),
            utils::Level::Warning
          );

          return;
        }

        // Only add this filter if it does not exist yet.
        // The `removeFilter` does handle properly the case where
        // the provided filter does not exist so use it as a cheap
        // solution to remove the `filter` in all cases.
        removeFilter(findFilter(filter));

        // Insert this filter at the end of the internal vector.
        // Based on the mechanism provided by `filterEvent`, if
        // we insert the filter at the end of the vector it will
        // be applied first which is what we want.
        m_filters.push_back(filter);
      }

      inline
      void
      EventListener::removeEventFilter(EventListener* filter) {
        // Use the dedicated handler.
        removeFilter(findFilter(filter));
      }

      inline
      bool
      EventListener::filterEvent(EventListener* /*watched*/, Event* /*e*/) {
        // No filtering provided here, return false.
        return false;
      }

      inline
      EventListener::Filter
      EventListener::findFilter(EventListener* filter) const {
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
