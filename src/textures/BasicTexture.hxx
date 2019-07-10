#ifndef    BASIC_TEXTURE_HXX
# define   BASIC_TEXTURE_HXX

# include "BasicTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      BasicTexture::BasicTexture(SDL_Renderer* renderer,
                                 const Palette::ColorRole& role,
                                 const utils::Sizef& size):
        Texture(renderer, role, Type::Basic),
        m_size(size)
      {}

      inline
      BasicTexture::~BasicTexture() {}

      inline
      utils::Sizef
      BasicTexture::query() {
        return m_size;
      }

    }
  }
}

#endif    /* BASIC_TEXTURE_HXX */
