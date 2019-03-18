#ifndef    WINDOW_HXX
# define   WINDOW_HXX

# include "Window.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline  
      Window::Window(const UUID& uuid,
                     const utils::Sizei& size,
                     const std::string& title):
        utils::CoreObject(title),
        m_uuid(uuid),
        m_window(nullptr),
        m_renderer(nullptr)
      {
        setService(std::string("window"));

        create(size);
      }

      inline
      Window::~Window() {
        clean();
      }

      inline
      const Window::UUID&
      Window::getUUID() const noexcept {
        return m_uuid;
      }

      inline
      SDL_Renderer*
      Window::getRenderer() {
        return m_renderer;
      }

      inline
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

      inline
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

      inline
      void
      Window::Window::clear() noexcept {
        SDL_RenderClear(m_renderer);
      }

      inline
      void
      Window::render() noexcept {
        SDL_RenderPresent(m_renderer);
      }

      inline
      void
      Window::create(const utils::Sizei& size)
      {
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

      inline
      void
      Window::clean() {
        // Destrroy the renderer for this window.
        if (m_renderer != nullptr) {
          SDL_DestroyRenderer(m_renderer);
        }

        // Destroy the window.
        if (m_window != nullptr) {
          SDL_DestroyWindow(m_window);
        }
      }

    }
  }
}

#endif    /* WINDOW_HXX */
