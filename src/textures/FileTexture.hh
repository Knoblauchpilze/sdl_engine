#ifndef    FILE_TEXTURE_HH
# define   FILE_TEXTURE_HH

# include <memory>
# include <string>
# include "Texture.hh"
# include "Image.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FileTexture: public Texture {
        public:

          FileTexture(SDL_Renderer* renderer,
                      const Palette::ColorRole& role,
                      ImageShPtr img);

          ~FileTexture();

          /**
           * @brief - Reimplementation of the base `Texture` method. This class can specializes
           *          the query by directly returning the size of the image used to create it
           *          instead of relying on the underlying engine. This allows to provide a way
           *          to query the size of the texture even when it has not yet been loaded.
           * @return - the size of the texture.
           */
          utils::Sizef
          query() override;

        protected:

          SDL_Texture*
          create() override;

        private:

          ImageShPtr m_img;
      };

      using FileTextureShPtr = std::shared_ptr<FileTexture>;
    }
  }
}

# include "FileTexture.hxx"

#endif    /* FILE_TEXTURE_HH */
