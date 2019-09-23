#ifndef    KEY_MODIFIER_HH
# define   KEY_MODIFIER_HH

# include <memory>
# include <core_utils/CoreFlag.hh>

namespace sdl {
  namespace core {
    namespace engine {

      namespace modifier {

        /**
         * @brief - Modes available to represent a key modifier.
         */
        enum class Mode {
          LeftAlt,
          LeftCtrl,
          LeftShift,
          RightAlt,
          RightCtrl,
          RightShift,
          Caps,
          Num
        };

        constexpr int count = 8;

        /**
         * @brief - Retrieves a human readable name from the input modifiers.
         * @param modifiers - a flag containing several modifiers for which a
         *                    name should be provided.
         * @return - a string describing the names of the modifiers registered
         *           in the input argument.
         */
        std::string
        getNameFromMode(const Mode& mode) noexcept;

      }

      class KeyModifier: public utils::CoreFlag<modifier::count> {
        public:

          /**
           * @brief - Creates a default key modifier with no active modes.
           */
          KeyModifier();

          /**
           * @brief - Creates a key modifier with the specified mode intialized
           *          to `true`.
           * @param mode - the key mode which should be activated.
           */
          KeyModifier(const modifier::Mode& mode);

          /**
           * @brief - Destruction of the object.
           */
          ~KeyModifier() = default;

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

        private:

          /**
           * @brief - Used to initialize the key modifier bits in order to be
           *          able to easily use this flag. Basically registers each
           *          individual flag value in the base class.
           */
          void
          init();

          /**
           * @brief - Attemps to retrieve the bit index provided for the input
           *          modifier mode when registereing it through the `addNamedBit`
           *          interface. If no such information is available an error is
           *          raised.
           * @param mode - the mode for which the bit index should be retrieved.
           * 
           * @return - the index of the bit in the base class as returned by the
           *           `addNamedBit` method.
           */
          int
          getBitID(const modifier::Mode& mode) const;

          /**
           * @brief - Used to register the input `mode` enumeration value in the
           *          parent class through the `addNamedBit` interface. Also insert
           *          the returned bit index in the internal `m_modesToIDs`.
           *          Note that the mode is registered with an initial value and a
           *          default value of `false`.
           * @param mode - the mode to register to the base class.
           */
          void
          registerKeyMode(const modifier::Mode& mode);

        private:

          using ModesTable = std::unordered_map<modifier::Mode, int>;

          /**
           * @brief - Describes the association between a given mode to its
           *          identifier in the base class bits array.
           *          This map is populated by the `init` function upon building
           *          any `KeyModifier` object.
           */
          ModesTable m_modesToIDs;
      };

      using KeyModifierShPtr = std::shared_ptr<KeyModifier>;
    }
  }
}

# include "KeyModifier.hxx"

#endif    /* KEY_MODIFIER_HH */
