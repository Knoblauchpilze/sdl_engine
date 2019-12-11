
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      SurfaceTexture::create() {
        if (m_surface == nullptr) {
          error(
            std::string("Could not create texture from surface"),
            std::string("Invalid null surface")
          );
        }

        // Convert the surface to a valid texture.
        SDL_Texture* tex = SDL_CreateTextureFromSurface(getRenderer(), m_surface);

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from surface"),
            SDL_GetError()
          );
        }

        // Return the created texture.
        return tex;
      }

    }
  }
}
