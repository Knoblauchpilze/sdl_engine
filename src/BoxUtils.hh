#ifndef    BOX_UTILS_HH
# define   BOX_UTILS_HH

# include <SDL2/SDL.h>
# include <maths_utils/Box.hh>

namespace utils {

  /**
   * @brief - Builds a top left SDL_Rect object from the input box.
   * @return - a sdl rect object based on the input description of the box.
   */
  template <typename CoordinateType>
  SDL_Rect
  toSDLRect(const Box<CoordinateType>& box) noexcept;

}

# include "BoxUtils.hxx"

#endif    /* BOX_UTILS_HH */
