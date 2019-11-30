#ifndef    IMAGE_HH
# define   IMAGE_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      class Image: public utils::CoreObject {
        public:

          /**
           * @brief - Creates a new image from the specified file. Note that we assume
           *          that the file describes a bitmap image. We use lazy loading to try
           *          to delay the reading of the file at a convenient moment. This is
           *          transparent to the user.
           *          Loading the image in this case means creating a surface from it.
           * @param file - the name of the file to use to create the image.
           */
          Image(const std::string& file);

          ~Image();

          /**
           * @brief - Retrieves the file name associated to this image. We assume that
           *          the file name cannot be changed during the life of this object
           *          and thus we don't need to provide a locker protection.
           * @return - the name of the file from which this image is created.
           */
          const std::string&
          getFileName() const noexcept;

          /**
           * @brief - Determine whether this image is actually linked to some data. The
           *          heuristic used to determine it is to check whether the internal
           *          file name is empty.
           * @return - `true` if this image has some associated data and `false` otherwise.
           */
          bool
          hasData() const noexcept;

          /**
           * @brief - Used to retrieve the dimensions of this image. Requires the image to
           *          be loaded. Note that the size is returned using a floating point value
           *          even though images usually have integer coordinates.
           * @return - the size of the texture.
           */
          utils::Sizef
          getSize();

          /**
           * @brief - Used to retrieve the raw pointer to the surface created for this image.
           *          This method performs the loading of the image if needed (i.e. if it is
           *          note already loaded).
           *          If this method returns it is guaranteed to return a valid pointer.
           * @return - a raw pointer to the created surface.
           */
          SDL_Surface*
          getSurface();

        protected:

          /**
           * @brief - Used to determine whether this image has already its data loaded. Assumes
           *          that the internal locker is already acquired.
           * @return - `true` if the image's data is already loaded and `false` otherwise.
           */
          bool
          isLoaded() const noexcept;


          /**
           * @brief - Used to perform the loading of the data for this image. Note that it is safe
           *          to call this method if the data is already loaded.
           *          Assumes that the locker is already acquired.
           */
          void
          load();

          /**
           * @brief - Acquires the locker to release the data associated to this image.
           */
          void
          unload();

        private:

          /**
           * @brief - A mutex to protect from concurrent accesses.
           */
          mutable std::mutex m_locker;

          /**
           * @brief - The name of the file from which the image should be created.
           */
          std::string m_file;

          /**
           * @brief - The loaded data for this image. This attribute is `null` until
           *          the `load` method is called. It is managed internally.
           */
          SDL_Surface* m_image;
      };

      using ImageShPtr = std::shared_ptr<Image>;
    }
  }
}

# include "Image.hxx"

#endif    /* IMAGE_HH */
