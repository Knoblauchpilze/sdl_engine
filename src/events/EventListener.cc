
# include "EventListener.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EventListener::EventListener(const std::string& name):
        utils::CoreObject(name),
        m_filters()
      {
        setService(std::string("events"));
      }

      bool
      EventListener::event(EventShPtr e) {
        // Apply all the filters registered for this listener.

        // Assume the event is not filtered.
        bool filtered = false;
        Filter filter = m_filters.cbegin();

        while (filter != m_filters.cend() && !filtered) {
          filtered = (*filter)->filterEvent(this, e);
          ++filter;
        }

        // Check whether this event has been filtered before calling
        // the internal handler.
        if (filtered) {
          // The event has been recognized since it was filtered.
          return true;
        }

        // Proceed with the internal handler: this will determine whether the event
        // has been regognized.
        return handleEvent(e);
      }

      void
      EventListener::installEventFilter(EventListenerShPtr filter) {
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

    }
  }
}
