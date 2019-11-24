#ifndef    IMAGE_HXX
# define   IMAGE_HXX

# include "Image.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Image::~Image() {
        // Unload the data for this image.
        unload();
      }

      inline
      const std::string&
      Image::getFileName() const noexcept {
        return m_file;
      }

      inline
      utils::Sizef
      Image::getSize() {
        // Acquire the lock.
        Guard guard(m_locker);

        // We need to load the data if it is not already done.
        load();

        // Now query the underlying image to find its dimensions.
        // If the image is empty, return an invalid size.
        if (m_image == nullptr) {
          return utils::Sizef();
        }

        return utils::Sizef(1.0f * m_image->w, 1.0f * m_image->h);
      }

      inline
      SDL_Surface*
      Image::getSurface() {
        // Acquire the lock.
        Guard guard(m_locker);

        // Load the data.
        load();

        // Check whether the data is available.
        if (m_image == nullptr) {
          error(
            std::string("Could not retrieve surface from image \"") + m_file + "\"",
            std::string("Invalid image data")
          );
        }

        // Return the loaded image.
        return m_image;
      }

      inline
      bool
      Image::isLoaded() const noexcept {
        return m_image != nullptr;
      }

    }
  }
}

#endif    /* IMAGE_HXX */
