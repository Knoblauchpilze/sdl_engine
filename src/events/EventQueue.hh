#ifndef    EVENT_QUEUE_HH
# define   EVENT_QUEUE_HH

# include <memory>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EngineObject;

      class EventQueue {
        public:

          virtual void
          postEvent(EventShPtr event) = 0;

          virtual void
          removeListener(EngineObject* listener) = 0;

      };

    }
  }
}

#endif    /* EVENT_QUEUE_HH */
