#ifndef    FILE_TEXTURE_HXX
# define   FILE_TEXTURE_HXX

# include "FileTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FileTexture::FileTexture(SDL_Renderer* renderer,
                               const Palette::ColorRole& role,
                               const std::string& file):
        Texture(renderer, role, Type::Image),
        m_file(file)
      {}

      inline
      FileTexture::~FileTexture() {}

    }
  }
}

#endif    /* FILE_TEXTURE_HXX */
