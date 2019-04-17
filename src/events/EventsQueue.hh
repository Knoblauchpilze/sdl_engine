#ifndef    EVENTS_QUEUE_HH
# define   EVENTS_QUEUE_HH

# include <memory>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EngineObject;

      class EventsQueue {
        public:

          virtual void
          postEvent(EventShPtr event) = 0;

          virtual void
          removeListener(EngineObject* listener) = 0;

      };

    }
  }
}

#endif    /* EVENTS_QUEUE_HH */
