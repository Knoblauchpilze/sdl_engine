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
