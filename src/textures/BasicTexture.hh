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

          /**
           * @brief - Creates a texture using the specified renderer. The texture is created
           *          with the specified role and size. The size is expressed using floating
           *          point values so that we get more flexibility.
           *          The underlying SDL texture has integer coordinates though.
           * @param renderer - the renderer to use to create and render the texture.
           * @param role - the role to assign to the texture. Used to retrieve a color when
           *               drawing the texture.
           * @param size - the dimensions of the texture to create.
           */
          BasicTexture(SDL_Renderer* renderer,
                       const Palette::ColorRole& role,
                       const utils::Sizef& size);

          ~BasicTexture();

          /**
           * @brief - Reimplementation of the base `Texture` method. This class can specializes
           *          the query by directly returning the input size used to create the texture
           *          instead of relying on the underlying engine.
           *          This allows to keep track of half pixels more easily and yields for more
           *          accurate results in general.
           * @return - the size of the texture.
           */
          utils::Sizef
          query() override;

        protected:

          SDL_Texture*
          create() override;

        private:

          utils::Sizef m_size;
      };

      using BasicTextureShPtr = std::shared_ptr<BasicTexture>;
    }
  }
}

# include "BasicTexture.hxx"

#endif    /* BASIC_TEXTURE_HH */
