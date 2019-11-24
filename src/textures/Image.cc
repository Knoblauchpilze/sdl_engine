
# include "Image.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Image::Image(const std::string& file):
        utils::CoreObject(std::string("image_") + file),

        m_locker(),

        m_file(file),
        m_image(nullptr)
      {
        setService("image");
      }

      void
      Image::load() {
        // Attempt to load the image from the file if needed.
        if (m_file.empty()) {
          return;
        }

        m_image = SDL_LoadBMP(m_file.c_str());

        if (m_image == nullptr) {
          error(
            std::string("Unable to create image from file \"") + m_file + "\"",
            SDL_GetError()
          );
        }
      }

      void
      Image::unload() {
        Guard guard(m_locker);

        if (isLoaded()) {
          SDL_FreeSurface(m_image);
        }
      }

    }
  }
}
