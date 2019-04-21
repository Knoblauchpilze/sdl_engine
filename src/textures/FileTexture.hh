#ifndef    FILE_TEXTURE_HH
# define   FILE_TEXTURE_HH

# include <memory>
# include <string>
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FileTexture: public Texture {
        public:

          FileTexture(SDL_Renderer* renderer,
                      const Palette::ColorRole& role,
                      const std::string& file);

          ~FileTexture();

        protected:

          SDL_Texture*
          create() override;

        private:

          std::string m_file;
      };

      using FileTextureShPtr = std::shared_ptr<FileTexture>;
    }
  }
}

# include "FileTexture.hxx"

#endif    /* FILE_TEXTURE_HH */
