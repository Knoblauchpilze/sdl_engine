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
      void
      NullEngine::setActiveWindow(const Window::UUID& /*uuid*/) {
        // Empty implementation.
      }

      inline
      void
      NullEngine::setWindowIcon(const Window::UUID& /*uuid*/,
                                const std::string& /*icon*/)
      {
        // EMpty implementation.
      }

      inline
      void
      NullEngine::clearWindow(const Window::UUID& /*uuid*/) {
        // Empty implementation.
      }

      inline
      void
      NullEngine::renderWindow(const Window::UUID& /*uuid*/) {
        // Empty implementation.
      }

      inline
      void
      NullEngine::destroyWindow(const Window::UUID& /*uuid*/) {
        // Empty implementation.
      }

      inline
      Texture::UUID
      NullEngine::createTexture(const utils::Sizei& /*size*/) {
        // Empty implementation.
        return Texture::UUID();
      }

      inline
      Texture::UUID
      NullEngine::createTextureFromFile(const std::string& /*file*/) {
        // Empty implementation.
        return Texture::UUID();
      }

      inline
      Texture::UUID
      NullEngine::createTextureFromText(const std::string& /*text*/,
                                        ColoredFontShPtr /*font*/)
      {
        // Empty implementation.
        return Texture::UUID();
      }

      inline
      void
      NullEngine::fillTexture(const Texture::UUID& /*uuid*/,
                              const Palette& /*palette*/)
      {
        // Empty implementation.
      }

      inline
      void
      NullEngine::setTextureAlpha(const Texture::UUID& /*uuid*/,
                                  const Color& /*color*/)
      {
        // Empty implementation.
      }

      inline
      void
      NullEngine::drawTexture(const Texture::UUID& /*tex*/,
                              const Texture::UUID* /*on*/,
                              utils::Boxf* /*where*/)
      {
        // Empty implementation.
      }

      inline
      utils::Sizei
      NullEngine::queryTexture(const Texture::UUID& /*uuid*/) {
        // Empty implementation.
        return utils::Sizei();
      }

      inline
      void
      NullEngine::destroyTexture(const Texture::UUID& /*uuid*/) {
        // Empty implementation.
      }

    }
  }
}

#endif    /* NULL_ENGINE_HXX */
