#ifndef    ENGINE_HH
# define   ENGINE_HH

# include "Window.hh"
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Engine {
        public:

          virtual Window::UUID
          createWindow(const utils::Sizei& size,
                       const std::string& title = std::string("Default SDL window")) = 0;

          virtual Texture::UUID
          createTexture(const utils::Sizei& size) = 0;

          virtual void
          setActiveWindow(const Window::UUID& uuid) = 0;

      };

    }
  }
}

#endif    /* ENGINE_HH */
