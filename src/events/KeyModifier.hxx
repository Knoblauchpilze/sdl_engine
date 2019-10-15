#ifndef    KEY_MODIFIER_HXX
# define   KEY_MODIFIER_HXX

# include "KeyModifier.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace modifier {

        inline
        std::string
        getNameFromMode(const Mode& mode) noexcept {
          switch (mode) {
            case Mode::LeftAlt:
              return std::string("LeftAlt");
            case Mode::LeftCtrl:
              return std::string("LeftCtrl");
            case Mode::LeftShift:
              return std::string("LeftShift");
            case Mode::RightAlt:
              return std::string("RightAlt");
            case Mode::RightCtrl:
              return std::string("RightCtrl");
            case Mode::RightShift:
              return std::string("RightShift");
            case Mode::Caps:
              return std::string("Caps");
            case Mode::Num:
              return std::string("Num");
            default:
              return std::string("Unknown");
          }
        }

      }

      inline
      bool
      altEnabled(const KeyModifier& modifier,
                 bool both,
                 bool left) noexcept
      {
        if (both) {
          return
            modifier.isSet(modifier::Mode::LeftAlt) ||
            modifier.isSet(modifier::Mode::RightAlt)
          ;
        }

        return
          (modifier.isSet(modifier::Mode::LeftAlt) && left) ||
          (modifier.isSet(modifier::Mode::RightAlt) && !left)
        ;
      }

      inline
      bool
      ctrlEnabled(const KeyModifier& modifier,
                  bool both,
                  bool left) noexcept
      {
        if (both) {
          return
            modifier.isSet(modifier::Mode::LeftCtrl) ||
            modifier.isSet(modifier::Mode::RightCtrl)
          ;
        }

        return
          (modifier.isSet(modifier::Mode::LeftCtrl) && left) ||
          (modifier.isSet(modifier::Mode::RightCtrl) && !left)
        ;
      }

      inline
      bool
      shiftEnabled(const KeyModifier& modifier,
                   bool both,
                   bool left) noexcept
      {
        // Caps lock accounts for both shift keys.
        if (modifier.isSet(modifier::Mode::Caps)) {
          return true;
        }

        if (both) {
          return
            modifier.isSet(modifier::Mode::LeftShift) ||
            modifier.isSet(modifier::Mode::RightShift)
          ;
        }

        return
          (modifier.isSet(modifier::Mode::LeftShift) && left) ||
          (modifier.isSet(modifier::Mode::RightShift) && !left)
        ;
      }

      inline
      bool
      numpadEnabled(const KeyModifier& modifier) noexcept {
        return modifier.isSet(modifier::Mode::Num);
      }

    }
  }
}

#endif    /* KEY_MODIFIER_HXX */
