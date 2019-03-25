#ifndef    EVENT_FACTORY_HH
# define   EVENT_FACTORY_HH

# include <SDL2/SDL.h>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EventFactory {
        public:

          EventFactory() = default;

          ~EventFactory() = default;

          static
          EventShPtr
          create(const SDL_Event& event);

      };

    }
  }
}

#endif    /* EVENT_FACTORY_HH */
