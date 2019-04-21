#ifndef    SURFACE_TEXTURE_HXX
# define   SURFACE_TEXTURE_HXX

# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      SurfaceTexture::SurfaceTexture(SDL_Renderer* renderer,
                                     const Palette::ColorRole& role,
                                     SDL_Surface* surface):
        Texture(renderer, role, Type::Surface),
        m_surface(surface)
      {}

      inline
      SurfaceTexture::~SurfaceTexture() {
        if (m_surface != nullptr) {
          SDL_FreeSurface(m_surface);
        }
      }

    }
  }
}

#endif    /* SURFACE_TEXTURE_HXX */
