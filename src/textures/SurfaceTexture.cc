
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      SurfaceTexture::create() {
        if (m_surface == nullptr) {
          // Check whether we should create the texture from its raw data.
          if (m_rawData == nullptr) {
            error(
              std::string("Could not create texture from surface"),
              std::string("Invalid null surface")
            );
          }

          // TODO: Create from raw data.

          if (m_surface == nullptr) {
            error(
              std::string("Could not create texture from surface"),
              SDL_GetError()
            );
          }
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
