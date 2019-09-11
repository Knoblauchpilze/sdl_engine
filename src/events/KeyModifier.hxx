#ifndef    KEY_MODIFIER_HXX
# define   KEY_MODIFIER_HXX

# include "KeyModifier.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      KeyModifier::KeyModifier():
        m_mods(KeyModifier::None)
      {}

      inline
      KeyModifier::KeyModifier(const Modifier& modifiers):
        m_mods(modifiers)
      {}

      inline
      bool
      KeyModifier::operator==(const KeyModifier& km) const noexcept {
        return m_mods == km.m_mods;
      }

      inline
      const KeyModifier::Modifier&
      KeyModifier::getModifiers() const noexcept {
        return m_mods;
      }

      inline
      void
      KeyModifier::setModifiers(const Modifier& modifiers) noexcept {
        m_mods = modifiers;
      }

      inline
      bool
      KeyModifier::altEnabled() const noexcept {
        return
          hasModifier(Modifier::LeftAlt) ||
          hasModifier(Modifier::RightAlt) ||
          hasModifier(Modifier::Caps)
        ;
      }

      inline
      bool
      KeyModifier::ctrlEnabled() const noexcept {
        return hasModifier(Modifier::LeftCtrl) || hasModifier(Modifier::RightCtrl);
      }

      inline
      bool
      KeyModifier::shiftEnabled() const noexcept {
        return hasModifier(Modifier::LeftShift) || hasModifier(Modifier::RightShift);
      }

      inline
      bool
      KeyModifier::numpadEnabled() const noexcept {
        return hasModifier(Modifier::Num);
      }

      inline
      std::string
      KeyModifier::toString() const noexcept {
        return std::string("[Modifiers: ") + getNameFromModifiers(*this) + "]";
      }

      inline
      bool
      KeyModifier::hasModifier(const Modifier& modifier) const noexcept {
        return m_mods & modifier;
      }

      inline
      std::string
      KeyModifier::getNameFromModifiers(const KeyModifier& modifiers) noexcept {
        std::string name;
        if (modifiers.altEnabled()) {
          name += "Alt";
        }
        if (modifiers.ctrlEnabled()) {
          if (!name.empty()) {
            name += "|";
          }
          name += "Ctrl";
        }
        if (modifiers.shiftEnabled()) {
          if (!name.empty()) {
            name += "|";
          }
          name += "Shift";
        }
        if (modifiers.numpadEnabled()) {
          if (!name.empty()) {
            name += "|";
          }
          name += "Numpad";
        }

        if (name.empty()) {
          name = "None";
        }

        return name;
      }

    }
  }
}

inline
std::ostream&
operator<<(const sdl::core::engine::KeyModifier& modifier, std::ostream& out) noexcept {
  return operator<<(out, modifier);
}

inline
std::ostream&
operator<<(std::ostream& out, const sdl::core::engine::KeyModifier& modifier) noexcept {
  out << modifier.toString();
  return out;
}

#endif    /* KEY_MODIFIER_HXX */
