#ifndef    RENDERER_STATE_HXX
# define   RENDERER_STATE_HXX

# include "RendererState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      RendererState::RendererState(SDL_Renderer* renderer):
        m_renderer(renderer),
        m_color(),
        m_texture(SDL_GetRenderTarget(renderer))
      {
        SDL_GetRenderDrawColor(m_renderer, &m_color.r, &m_color.g, &m_color.b, &m_color.a);
        SDL_RenderGetViewport(m_renderer, &m_viewport);
      }

      inline
      RendererState::~RendererState() {
        // Restore old renderer state.
        SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
        SDL_SetRenderTarget(m_renderer, m_texture);
        SDL_RenderSetViewport(m_renderer, &m_viewport);
      }

    }
  }
}

#endif    /* RENDERER_STATE_HXX */
