#ifndef    KEY_MODIFIER_HH
# define   KEY_MODIFIER_HH

# include <memory>

namespace sdl {
  namespace core {
    namespace engine {

      class KeyModifier {
        public:

          enum Modifier {
            Empty      = 0,
            LeftAlt    = 1 << 0,
            LeftCtrl   = 1 << 1,
            LeftShift  = 1 << 2,
            RightAlt   = 1 << 3,
            RightCtrl  = 1 << 4,
            RightShift = 1 << 5,
            Caps       = 1 << 6,
            Num        = 1 << 7
          };

        public:

          /**
           * @brief - Creates a default key modifier with a `None` policy associated to it.
           */
          KeyModifier();

          /**
           * @brief - Creates a key modifier with the specified modifier state associated to
           *          it.
           * @param modifier - the modifier to assign to this object.
           */
          KeyModifier(const Modifier& modifier);

          /**
           * @brief - Destruction of the object.
           */
          ~KeyModifier() = default;

          /**
           * @brief - Convenience values to used to define some complex modifiers.
           */
          static const Modifier None;
          static const Modifier Alt;
          static const Modifier Ctrl;
          static const Modifier Shift;
          static const Modifier Numpad;

        public:

          /**
           * @brief - Used to compare to key modifiers.
           * @param km - the other element with which `this` should be compared.
           * @return - `true` if both elements are identical, `false` otherwise.
           */
          bool
          operator==(const KeyModifier& km) const noexcept;

          /**
           * @brief - Used to retrieve the current modifiers associated to this object.
           * @return - a flag containing all the modifiers associated to this oject.
           */
          const Modifier&
          getModifiers() const noexcept;

          /**
           * @brief - Used to set a new set of modifiers for this object.
           * @param modifiers - the new modifiers to assign to this object.
           */
          void
          setModifiers(const Modifier& modifiers) noexcept;

          /**
           * @brief - Used to add the specified modifier to the existing modifiers for
           *          this object.
           *          Note that existing modifiers will be kept unchanged and nothing
           *          will happen if the input modifier already exist.
           * @param modifier - the modifier to add.
           */
          void
          addModifier(const Modifier& modifier) noexcept;

          /**
           * @brief - Returns `true` if any of the `Alt` keys is active.
           * @return - `true` if any `Alt` keys is active.
           */
          bool
          altEnabled() const noexcept;

          /**
           * @brief - Returns `true` if any of the `Ctrl` keys is active.
           * @return - `true` if any `Ctrl` keys is active.
           */
          bool
          ctrlEnabled() const noexcept;

          /**
           * @brief - Returns `true` if any of the `Shift` keys is active.
           *          Note that this include the `CapsLock` key.
           * @return - `true` if any `Shift` keys is active.
           */
          bool
          shiftEnabled() const noexcept;

          /**
           * @brief - Returns `true` if the keypad is enabled.
           * @return - `true` if the keypad is active, `false` otherwise.
           */
          bool
          numpadEnabled() const noexcept;

          /**
           * @brief - Displays the modifiers associated to this object as a
           *          human readable string.
           * @return - a human readable string containing all the modifiers
           *           associated to this object.
           */
          std::string
          toString() const noexcept;

        private:

          /**
           * @brief - Used to check whether this object describes the input
           *          modifier.
           * @param modifier - the value which should be checked in the internal
           *                   modifiers flag.
           * @return - `true` if the internal state describes the input modifier
           *           and `false` otherwise.
           */
          bool
          hasModifier(const Modifier& modifier) const noexcept;

          /**
           * @brief - Retrieves a human readable name from the input modifiers.
           * @param modifiers - a flag containing several modifiers for which a
           *                    a name should be provided.
           * @return - a string describing the names of the modifiers registered
           *           in the input argument.
           */
          static
          std::string
          getNameFromModifiers(const KeyModifier& modifiers) noexcept;

        private:

          Modifier m_mods;

      };

      using KeyModifierShPtr = std::shared_ptr<KeyModifier>;
    }
  }
}

std::ostream&
operator<<(const sdl::core::engine::KeyModifier& modifier, std::ostream& out) noexcept;

std::ostream&
operator<<(std::ostream& out, const sdl::core::engine::KeyModifier& modifier) noexcept;

# include "KeyModifier.hxx"

#endif    /* KEY_MODIFIER_HH */
