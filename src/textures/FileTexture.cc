
# include "FileTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      FileTexture::create() {
        // First, load the image as a surface using regular SDL function.
        SDL_Surface* imageAsSurface = SDL_LoadBMP(m_file.c_str());
        if (imageAsSurface == nullptr) {
          error(
            std::string("Unable to create texture from file \"") + m_file + "\"",
            SDL_GetError()
          );
        }

        // Transform the surface into a valid texture.
        SDL_Texture* tex  = SDL_CreateTextureFromSurface(getRenderer(), imageAsSurface);

        // Release the resources used by the surface.
        SDL_FreeSurface(imageAsSurface);

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from file \"") + m_file + "\"",
            SDL_GetError()
          );
        }

        // Return the created texture.
        return tex;
      }

    }
  }
}
