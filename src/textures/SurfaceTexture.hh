#ifndef    SURFACE_TEXTURE_HH
# define   SURFACE_TEXTURE_HH

# include <memory>
# include <SDL2/SDL.h>
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class SurfaceTexture: public Texture {
        public:

          SurfaceTexture(SDL_Renderer* renderer,
                         const Palette::ColorRole& role,
                         SDL_Surface* surface);

          ~SurfaceTexture();

        protected:

          SDL_Texture*
          create() override;

        private:

          SDL_Surface* m_surface;
      };

      using SurfaceTextureShPtr = std::shared_ptr<SurfaceTexture>;
    }
  }
}

# include "SurfaceTexture.hxx"

#endif    /* SURFACE_TEXTURE_HH */
