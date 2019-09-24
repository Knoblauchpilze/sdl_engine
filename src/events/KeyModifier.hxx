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
      altEnabled(const KeyModifier& modifier) noexcept {
        return
          modifier.isSet(modifier::Mode::LeftAlt) ||
          modifier.isSet(modifier::Mode::RightAlt)
        ;
      }

      inline
      bool
      ctrlEnabled(const KeyModifier& modifier) noexcept {
        return
          modifier.isSet(modifier::Mode::LeftCtrl) ||
          modifier.isSet(modifier::Mode::RightCtrl)
        ;
      }

      inline
      bool
      shiftEnabled(const KeyModifier& modifier) noexcept {
        return
          modifier.isSet(modifier::Mode::LeftShift) ||
          modifier.isSet(modifier::Mode::RightShift) ||
          modifier.isSet(modifier::Mode::Caps)
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
