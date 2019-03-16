
# include "SdlEngine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      SdlEngine::initializeSDLLib() {
        // Initialize the SDL lib.
        if (!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
          error(
            std::string("Caught error while initializing SDL lib"),
            std::string("") + SDL_GetError()
          );
        }
      }

      void
      SdlEngine::releaseSDLLib() {
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
          SDL_Quit();
        }
      }

    }
  }
}
