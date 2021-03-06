
# include "FontFactory.hh"
# include <SDL2/SDL_ttf.h>

namespace sdl {
  namespace core {
    namespace engine {

      void
      FontFactory::initializeTTFLib() {
        // Initialize the TTF lib.
        if (!TTF_WasInit() && TTF_Init() == -1) {
          error(
            std::string("Caught error while initializing TTF lib"),
            std::string("") + TTF_GetError()
          );
        }
      }

      void
      FontFactory::releaseTTFLib() {
        if (TTF_WasInit()) {
          TTF_Quit();
        }
      }

    }
  }
}

