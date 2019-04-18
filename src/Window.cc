
# include "Window.hh"
# include "RendererState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      std::uint32_t
      Window::getSDLID() const {
        if (m_window == nullptr) {
          error(
            std::string("Cannot retrieve SDL window ID for"),
            std::string("Invalid internal SDL window")
          );
        }

        return SDL_GetWindowID(m_window);
      }

      void
      Window::setIcon(const std::string& icon) {
        // Load this icon.
        SDL_Surface* iconAsSurface = SDL_LoadBMP(icon.c_str());
        if (iconAsSurface == nullptr) {
          error(
            std::string("Could not load icon \"") + icon + "\"",
            std::string("") + SDL_GetError()
          );
        }

        // Set the icon to the window.
        SDL_SetWindowIcon(m_window, iconAsSurface);

        // Release resources used to create the icon.
        SDL_FreeSurface(iconAsSurface);
      }

      void
      Window::drawTexture(const utils::Uuid& tex,
                          const utils::Uuid* on,
                          utils::Boxf* where)
      {
        // We want to draw the input `tex` on the target `on` at
        // position `where`.
        // `on` may be nil, in which case we should assign the default
        // rendering target to the internal `m_renderer` and perform
        // the blit.
        // If `where` is set to nul, it only affects how the SDL
        // will process the blit operation internally but does not
        // really change anything at this level.
        // The rendering process is delegated to the texture for the
        // actual blitting part, but this window will perform all
        // the rendering pipeline configuration beforehand.

        // Save the renderer state so that we can restore the
        // initial rendering target and properties (color, etc.).
        RendererState state(m_renderer);

        // So the first thing to do is to assign a valid rendering target.
        // To do so, we should set the target to `on`, except if it is
        // null, in which case we should set the renderer to perform
        // blit on default target.
        SDL_Texture* target = nullptr;
        if (on != nullptr) {
          // Try to retrieve the corresponding texture.
          TextureShPtr base = getTextureOrThrow(*on);

          target = (*base)();
        }

        // Set this texture as rendering target.
        SDL_SetRenderTarget(m_renderer, target);

        // Now that the rendering target is set, perform the drawing.

        // Retrieve the texture to draw.
        TextureShPtr layer = getTextureOrThrow(tex);

        layer->draw(where, m_renderer);
      }

      void
      Window::create(const utils::Sizei& size) {
        // Attempt to create the underlying SDL window.
        m_window = SDL_CreateWindow(
          getName().c_str(),
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          size.w(),
          size.h(),
          SDL_WINDOW_SHOWN
        );

        // Check whether the window could successfully be created.
        if (m_window == nullptr) {
          error(
            std::string("Could not create SDL window"),
            std::string("") + SDL_GetError()
          );
        }

        // Create the SDL renderer associated to the window.
        m_renderer = SDL_CreateRenderer(
          m_window,
          -1,
          SDL_RENDERER_ACCELERATED
        );

        // Check whether the renderer could successfully be created.
        if (m_renderer == nullptr) {
          error(
            std::string("Could not create SDL renderer for window"),
            std::string("") + SDL_GetError()
          );
        }
      }

    }
  }
}