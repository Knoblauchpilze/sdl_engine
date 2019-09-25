#ifndef    MOUSE_EVENT_SPECIALIZATION_HXX
# define   MOUSE_EVENT_SPECIALIZATION_HXX

# include "MouseEvent.hh"

namespace utils {

  template <>
  inline
  std::string
  getNameForKey(const sdl::core::engine::mouse::Button& button) {
    return sdl::core::engine::mouse::getNameFromButton(button);
  }

}

#endif    /* MOUSE_EVENT_SPECIALIZATION_HXX */
