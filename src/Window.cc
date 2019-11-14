
# include "Window.hh"
# include "TextureUtils.hxx"
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

      utils::Sizef
      Window::getSize() const {
        if (m_window == nullptr) {
          error(
            std::string("Cannot retrieve dimensions of window"),
            std::string("Invalid internal SDL window")
          );
        }

        // Query the underlying API to get the window's size.
        int w = 0;
        int h = 0;
        SDL_GetWindowSize(m_window, &w, &h);

        // Return the built-in value.
        return utils::Sizef(w, h);
      }

      void
      Window::setIcon(const std::string& icon) {
        // Load this icon.
        SDL_Surface* iconAsSurface = SDL_LoadBMP(icon.c_str());
        if (iconAsSurface == nullptr) {
          error(
            std::string("Could not load icon \"") + icon + "\"",
            SDL_GetError()
          );
        }

        // Set the icon to the window.
        SDL_SetWindowIcon(m_window, iconAsSurface);

        // Release resources used to create the icon.
        SDL_FreeSurface(iconAsSurface);
      }

      void
      Window::updateViewport(const utils::Boxf& area) {
        // Check whether the current rendering target is `null`.
        SDL_Texture* renderTarget = SDL_GetRenderTarget(m_renderer);

        if (renderTarget != nullptr) {
          Uint32 fmt;
          int access, w, h;
          SDL_QueryTexture(renderTarget, &fmt, &access, &w, &h);

          error(
            std::string("Could not update viewport to ") + area.toString(),
            std::string("Rendering target is not null ") +
            "(format: " + std::to_string(fmt) + ", access: " + std::to_string(access) +
            ", dims: " + std::to_string(w) + "x" + std::to_string(h) + ")"
          );
        }

        // Convert and assign the viewport of the renderer associated to this
        // window. This will force the utilization no matter its current size.
        // Note that this function is mostly here to prevent some issues when
        // dealing with window resize. It could happen that the viewport did
        // not get resized for some reasons.
        SDL_Rect viewport = toSDLRect(area);
        int ret = SDL_RenderSetViewport(m_renderer, &viewport);

        if (ret != 0) {
          error(
            std::string("Could not set viewport to ") + area.toString(),
            SDL_GetError()
          );
        }
      }

      void
      Window::drawTexture(const utils::Uuid& tex,
                          const utils::Boxf* from,
                          const utils::Uuid* on,
                          const utils::Boxf* where)
      {
        // We want to draw the input `tex` on the target `on` at
        // position `where`.
        // `on` may be nil, in which case we should assign the default
        // rendering target to the internal `m_renderer` and perform
        // the blit.
        // If `where` is set to null, it only affects how the SDL
        // will process the blit operation internally but does not
        // really change anything at this level.

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

        // Retrieve the texture to draw.
        TextureShPtr layer = getTextureOrThrow(tex);

        // Draw the layer on the base.
        layer->draw(from, where, target);
      }

      void
      Window::create(const utils::Sizei& size,
                     const bool resizable)
      {
        // Compute the flags from the input properties.
        std::uint32_t flags = SDL_WINDOW_SHOWN;
        if (resizable) {
          flags |= SDL_WINDOW_RESIZABLE;
        }

        // Attempt to create the underlying SDL window.
        m_window = SDL_CreateWindow(
          getName().c_str(),
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          size.w(),
          size.h(),
          flags
        );

        // Check whether the window could successfully be created.
        if (m_window == nullptr) {
          error(
            std::string("Could not create SDL window"),
            SDL_GetError()
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
            SDL_GetError()
          );
        }
      }

    }
  }
}