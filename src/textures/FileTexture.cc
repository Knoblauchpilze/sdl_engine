
# include "FileTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      FileTexture::create() {
        // Transform the surface into a valid texture.
        SDL_Texture* tex = SDL_CreateTextureFromSurface(getRenderer(), m_img->getSurface());

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from file \"") + m_img->getFileName() + "\"",
            SDL_GetError()
          );
        }

        // Return the created texture.
        return tex;
      }

    }
  }
}
