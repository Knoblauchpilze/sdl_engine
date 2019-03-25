
# include "EventFactory.hh"
# include "KeyEvent.hh"
# include "MouseEvent.hh"
# include "QuitEvent.hh"

# include <iostream>

namespace sdl {
  namespace core {
    namespace engine {

      EventShPtr
      EventFactory::create(const SDL_Event& event) {
        // Create the suited event from the input type.
        switch (event.type) {
          case SDL_KEYDOWN:
            return std::make_shared<KeyEvent>(event.key);
          case SDL_KEYUP:
            return std::make_shared<KeyEvent>(event.key);
          case SDL_MOUSEMOTION:
            return std::make_shared<MouseEvent>(event.motion);
          case SDL_MOUSEBUTTONDOWN:
            return std::make_shared<MouseEvent>(event.button);
          case SDL_MOUSEBUTTONUP:
            return std::make_shared<MouseEvent>(event.button);
          case SDL_MOUSEWHEEL:
            return std::make_shared<MouseEvent>(event.wheel);
          case SDL_QUIT:
            return std::make_shared<QuitEvent>(event.quit);
          default:
            break;
        }

        // Unhandled type.
        return nullptr;
      }

    }
  }
}
