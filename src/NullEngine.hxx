#ifndef    NULL_ENGINE_HXX
# define   NULL_ENGINE_HXX

# include "NullEngine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Window::UUID
      NullEngine::createWindow(const utils::Sizei& /*size*/,
                               const std::string& /*title*/)
      {
        // Empty implementation.
        return Window::UUID();
      }

      inline
      Texture::UUID
      NullEngine::createTexture(const utils::Sizei& /*size*/) {
        // Empty implementation.
        return Texture::UUID();
      }

      inline
      void
      NullEngine::setActiveWindow(const Window::UUID& /*uuid*/) {
        // Empty implementation.
      }

    }
  }
}

#endif    /* NULL_ENGINE_HXX */
