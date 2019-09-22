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
      KeyModifier::KeyModifier():
        utils::CoreFlag<modifier::count>(std::string("key_modifier")),
        m_modesToIDs()
      {
        init();
      }

      inline
      KeyModifier::KeyModifier(const modifier::Mode& mode):
        utils::CoreFlag<modifier::count>(std::string("key_modifier")),
        m_modesToIDs()
      {
        init();

        set(getBitID(mode));
      }

      inline
      bool
      KeyModifier::altEnabled() const noexcept {
        return
          isSet(getBitID(modifier::Mode::LeftAlt)) ||
          isSet(getBitID(modifier::Mode::RightAlt))
        ;
      }

      inline
      bool
      KeyModifier::ctrlEnabled() const noexcept {
        return
          isSet(getBitID(modifier::Mode::LeftCtrl)) ||
          isSet(getBitID(modifier::Mode::RightCtrl))
        ;
      }

      inline
      bool
      KeyModifier::shiftEnabled() const noexcept {
        return
          isSet(getBitID(modifier::Mode::LeftShift)) ||
          isSet(getBitID(modifier::Mode::RightShift)) ||
          isSet(getBitID(modifier::Mode::Caps))
        ;
      }

      inline
      bool
      KeyModifier::numpadEnabled() const noexcept {
        return isSet(getBitID(modifier::Mode::Num));
      }

      inline
      void
      KeyModifier::init() {
        // Register all key modes.
        registerKeyMode(modifier::Mode::LeftAlt);
        registerKeyMode(modifier::Mode::LeftCtrl);
        registerKeyMode(modifier::Mode::LeftShift);
        registerKeyMode(modifier::Mode::RightAlt);
        registerKeyMode(modifier::Mode::RightCtrl);
        registerKeyMode(modifier::Mode::RightShift);
        registerKeyMode(modifier::Mode::Caps);
        registerKeyMode(modifier::Mode::Num);
      }

      inline
      int
      KeyModifier::getBitID(const modifier::Mode& mode) const {
        // Find the corresponding mode in the internal table.
        ModesTable::const_iterator it = m_modesToIDs.find(mode);

        // Check for errors.
        if (it == m_modesToIDs.cend()) {
          throw utils::CoreException(
            std::string("Could not get bit index for \"") + modifier::getNameFromMode(mode) + "\"",
            std::string("getBitID"),
            std::string("KeyModifier"),
            std::string("No such bit registered")
          );
        }

        // Return the corresponding index.
        return it->second;
      }

      inline
      void
      KeyModifier::registerKeyMode(const modifier::Mode& mode) {
        // Register the name corresponding to the input mode with false value and default
        // value.
        int id = addNamedBit(modifier::getNameFromMode(mode), false, false);

        // Register the returned index to easily retrieve its value later on.
        m_modesToIDs[mode] = id;
      }

    }
  }
}

#endif    /* KEY_MODIFIER_HXX */
