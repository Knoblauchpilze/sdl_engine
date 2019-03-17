#ifndef    RENDERERSTATE_HH
# define   RENDERERSTATE_HH

# include <memory>
# include <SDL2/SDL.h>
# include "Color.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class RendererState {
        public:

          explicit
          RendererState(SDL_Renderer* renderer);

          ~RendererState();

        private:

          SDL_Renderer* m_renderer;
          SDL_Color m_color;
          SDL_Texture* m_texture;

      };

      using RendererStateShPtr = std::shared_ptr<RendererState>;
    }
  }
}

# include "RendererState.hxx"

#endif    /* RENDERERSTATE_HH */
