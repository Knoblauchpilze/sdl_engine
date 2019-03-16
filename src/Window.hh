#ifndef    WINDOW_HH
# define   WINDOW_HH

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Window: public utils::CoreObject {
        public:

          using UUID = uint32_t;

        public:

          Window(const UUID& uuid,
                 const utils::Sizei& size,
                 const std::string& title = std::string("Default SDL window"));

          ~Window();

          const UUID&
          getUUID() const noexcept;

          SDL_Renderer*
          getRenderer();

        private:

          void
          create(const utils::Sizei& size);

          void
          clean();

        private:

          UUID m_uuid;

          SDL_Window* m_window;
          SDL_Renderer* m_renderer;
      };

      using WindowShPtr = std::shared_ptr<Window>;
    }
  }
}

# include "Window.hxx"

#endif    /* WINDOW_HH */
