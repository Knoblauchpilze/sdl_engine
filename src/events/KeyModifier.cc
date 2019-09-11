
# include "KeyModifier.hh"

namespace {

  inline
  sdl::core::engine::KeyModifier::Modifier
  operator|(const sdl::core::engine::KeyModifier::Modifier& lhs, const sdl::core::engine::KeyModifier::Modifier& rhs) {
    return static_cast<sdl::core::engine::KeyModifier::Modifier>(static_cast<int>(lhs) | static_cast<int>(rhs));
  }

}

namespace sdl {
  namespace core {
    namespace engine {

      const KeyModifier::Modifier KeyModifier::None(KeyModifier::Modifier::Empty);
      const KeyModifier::Modifier KeyModifier::Alt(KeyModifier::Modifier::LeftAlt | KeyModifier::Modifier::RightAlt);
      const KeyModifier::Modifier KeyModifier::Ctrl(KeyModifier::Modifier::LeftCtrl | KeyModifier::Modifier::RightCtrl);
      const KeyModifier::Modifier KeyModifier::Shift(KeyModifier::Modifier::LeftShift | KeyModifier::Modifier::RightShift | KeyModifier::Modifier::Caps);
      const KeyModifier::Modifier KeyModifier::Numpad(KeyModifier::Modifier::Num);

      void
      KeyModifier::addModifier(const Modifier& modifier) noexcept {
        m_mods = m_mods | modifier;
      }

    }
  }
}
