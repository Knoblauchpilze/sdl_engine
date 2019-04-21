#ifndef    BASIC_TEXTURE_HXX
# define   BASIC_TEXTURE_HXX

# include "BasicTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      BasicTexture::BasicTexture(SDL_Renderer* renderer,
                                 const Palette::ColorRole& role,
                                 const utils::Sizei& size):
        Texture(renderer, role, Type::Basic),
        m_size(size)
      {}

      inline
      BasicTexture::~BasicTexture() {}

    }
  }
}

#endif    /* BASIC_TEXTURE_HXX */
