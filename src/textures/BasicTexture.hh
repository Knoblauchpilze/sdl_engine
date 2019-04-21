#ifndef    BASIC_TEXTURE_HH
# define   BASIC_TEXTURE_HH

# include <memory>
# include <maths_utils/Size.hh>
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class BasicTexture: public Texture {
        public:

          BasicTexture(SDL_Renderer* renderer,
                       const Palette::ColorRole& role,
                       const utils::Sizei& size);

          ~BasicTexture();

        protected:

          SDL_Texture*
          create() override;

        private:

          utils::Sizei m_size;
      };

      using BasicTextureShPtr = std::shared_ptr<BasicTexture>;
    }
  }
}

# include "BasicTexture.hxx"

#endif    /* BASIC_TEXTURE_HH */
