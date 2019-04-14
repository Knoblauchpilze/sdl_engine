#ifndef    EVENT_LISTENER_HH
# define   EVENT_LISTENER_HH

# include <vector>
# include "Event.hh"
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EventListener: public utils::CoreObject {
        public:

          EventListener(const std::string& name = std::string("EventListener"));

          virtual ~EventListener();

          virtual bool
          handleEvent(Event* e);

          virtual void
          installEventFilter(EventListener* filter);

          virtual void
          removeEventFilter(EventListener* filter);

          virtual bool
          filterEvent(EventListener* watched, Event* e);

        protected:

          using Filters = std::vector<EventListener*>;

          using Filter = Filters::const_iterator;

          Filter
          findFilter(EventListener* filter) const;

          bool
          validFilter(const Filter& filter) const noexcept;

          void
          removeFilter(const Filter& filter);

        private:

          Filters m_filters;

      };

    }
  }
}

# include "EventListener.hxx"

#endif    /* EVENT_LISTENER_HH */
