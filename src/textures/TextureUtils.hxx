#ifndef    TEXTURE_UTILS_HH
# define   TEXTURE_UTILS_HH

# include <SDL2/SDL.h>
# include <maths_utils/Box.hh>

namespace sdl {
  namespace core {
    namespace engine {

      /**
       * @brief - Builds a top left SDL_Rect object from the input box.
       * @return - a sdl rect object based on the input description of the box.
       */
      template <typename CoordinateType>
      inline
      SDL_Rect
      toSDLRect(const utils::Box<CoordinateType>& box) noexcept {
        return SDL_Rect{
          static_cast<int>(box.getLeftBound()),
          static_cast<int>(box.getBottomBound()),
          static_cast<int>(box.w()),
          static_cast<int>(box.h())
        };
      }

    }
  }
}


#endif    /* TEXTURE_UTILS_HH */
