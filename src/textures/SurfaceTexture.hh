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

          /**
           * @brief - Creates a texture from the input surface using the provided
           *          renderer.
           *          Note that the surface is only acquired (in the sense of an
           *          ownership transfer) when the `takeOwnership` boolean is set
           *          to `true`. This will indicate to the texture that the provided
           *          surface should be managed by the textrue itself.
           *          If the value is `false`, the texture will not try to release
           *          the surface when being destroyed.
           * @param renderer - the renderer to use to create the texture.
           * @param surface - the raw data to use to create the texture.
           * @param role - the color role of the texture to create.
           * @param takeOwnership - a boolean indicating wheher the texture should
           *                        take ownership of the surface used to create it.
           */
          SurfaceTexture(SDL_Renderer* renderer,
                         SDL_Surface* surface,
                         const Palette::ColorRole& role,
                         bool takeOwnership);

          ~SurfaceTexture();

        protected:

          SDL_Texture*
          create() override;

        private:

          /**
           * @brief - The raw data to use to create the texture.
           */
          SDL_Surface* m_surface;

          /**
           * @brief - Indicates whether this texture owns the data it is created from
           *          (and thus if it should release it when being destoryed) or if
           *          somebody else is responsible for cleaning it.
           */
          bool m_owner;
      };

      using SurfaceTextureShPtr = std::shared_ptr<SurfaceTexture>;
    }
  }
}

# include "SurfaceTexture.hxx"

#endif    /* SURFACE_TEXTURE_HH */
