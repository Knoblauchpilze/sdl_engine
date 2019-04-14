#ifndef    EVENT_LISTENER_HH
# define   EVENT_LISTENER_HH

# include <vector>
# include "Event.hh"
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EventListener;
      using EventListenerShPtr = std::shared_ptr<EventListener>;

      class EventListener: public utils::CoreObject {
        public:

          EventListener(const std::string& name = std::string("EventListener"));

          virtual ~EventListener();

          // Note that this function returns `true` if the event has been recognized,
          // and false if this is not the case.
          // To determine whether the event should be sent to children one should check
          // the `e->isAccepted()` result.
          bool
          event(EventShPtr e);

          void
          installEventFilter(EventListenerShPtr filter);

          void
          removeEventFilter(EventListenerShPtr filter);

          virtual bool
          filterEvent(EventListener* watched,
                      EventShPtr e);

        protected:

          // Note that the return value it is true only if the event `e` has been recognized.
          // To check whether the event has been accepted, use the `e->isAccepted()` method.
          virtual bool
          handleEvent(EventShPtr e);

        private:

          using Filters = std::vector<EventListenerShPtr>;

          using Filter = Filters::const_iterator;

          Filter
          findFilter(EventListenerShPtr filter) const;

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
