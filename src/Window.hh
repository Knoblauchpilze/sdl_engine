#ifndef    WINDOW_HH
# define   WINDOW_HH

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include <maths_utils/Size.hh>
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Window: public utils::CoreObject {
        public:

          Window(const utils::Sizei& size,
                 const std::string& title = std::string("Default SDL window"));

          ~Window();

          SDL_Renderer*
          getRenderer();

          void
          setIcon(const std::string& icon);

          void
          draw(TextureShPtr tex,
               utils::Boxf* where = nullptr);

          void
          clear() noexcept;

          void
          render() noexcept;

        private:

          void
          create(const utils::Sizei& size);

          void
          clean();

        private:

          SDL_Window* m_window;
          SDL_Renderer* m_renderer;
      };

      using WindowShPtr = std::shared_ptr<Window>;
    }
  }
}

# include "Window.hxx"

#endif    /* WINDOW_HH */
