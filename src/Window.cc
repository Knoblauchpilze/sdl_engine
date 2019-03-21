
# include "Window.hh"
# include "BoxUtils.hh"
# include "RendererState.hh"

namespace sdl {
  namespace core {
    namespace engine {

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
      Window::draw(TextureShPtr tex,
                   utils::Boxf* where)
      {
        // Save the renderer state so that we can restore the
        // initial rendering target and properties (color, etc.).
        RendererState state(m_renderer);

        // Set this texture as rendering target.
        SDL_SetRenderTarget(m_renderer, nullptr);

        // Draw the input texture at the corresponding location.
        if (where == nullptr) {
          SDL_RenderCopy(m_renderer, (*tex)(), nullptr, nullptr);
        } 
        else {
          SDL_Rect dstArea = utils::toSDLRect(*where);
          SDL_RenderCopy(m_renderer, (*tex)(), nullptr, &dstArea);
        }
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