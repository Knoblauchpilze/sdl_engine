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
