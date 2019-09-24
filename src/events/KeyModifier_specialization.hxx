#ifndef    KEY_MODIFIER_SPECIALIZATION_HXX
# define   KEY_MODIFIER_SPECIALIZATION_HXX

# include "KeyModifier.hh"

namespace utils {

  template <>
  inline
  std::string
  getNameForKey(const sdl::core::engine::modifier::Mode& mode) {
    return sdl::core::engine::modifier::getNameFromMode(mode);
  }

}

#endif    /* KEY_MODIFIER_SPECIALIZATION_HXX */
