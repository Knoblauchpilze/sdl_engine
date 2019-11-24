#ifndef    FILE_TEXTURE_HXX
# define   FILE_TEXTURE_HXX

# include "FileTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FileTexture::FileTexture(SDL_Renderer* renderer,
                               const Palette::ColorRole& role,
                               ImageShPtr img):
        Texture(renderer, role, Type::Image),
        m_img(img)
      {
        // Check whether the provided image is valid.
        if (img == nullptr) {
          error(
            std::string("Could not create texture from image"),
            std::string("Invalid null image")
          );
        }
      }

      inline
      FileTexture::~FileTexture() {}

      inline
      utils::Sizef
      FileTexture::query() {
        return m_img->getSize();
      }

    }
  }
}

#endif    /* FILE_TEXTURE_HXX */
