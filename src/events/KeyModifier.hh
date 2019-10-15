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
          LeftAlt     = 0,
          LeftCtrl    = 1,
          LeftShift   = 2,
          RightAlt    = 3,
          RightCtrl   = 4,
          RightShift  = 5,
          Caps        = 6,
          Num         = 7,
          ValuesCount = 8
        };

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

      using KeyModifier = utils::CoreFlag<modifier::Mode>;

      /**
       * @brief - Returns `true` if any of the `Alt` keys is active.
       *          The user can specify whether a specific key should
       *          be checked by specifying a `false` value for `both`
       *          and specifying whether the left or right key is to
       *          be checked.
       * @param modifier - the modifier which should be checked for
       *                   `Alt` keys active.
       * @param both - `true` if any of the two alt keys should be
       *               checked and `false` if the `left` value should
       *               be retrieved to get the key to check.
       *               Note that using `false` for this value (default)
       *               will make the `left` parameter ignored.
       * @param left - ignored if `both` is `true`, allows to specify
       *               which of the alt keys should be checked.
       * @return - `true` if any `Alt` keys is active.
       */
      bool
      altEnabled(const KeyModifier& modifier,
                 bool both = true,
                 bool left = true) noexcept;

      /**
       * @brief - Returns `true` if any of the `Ctrl` keys is active.
       *          The user can specify whether a specific key should
       *          be checked by specifying a `false` value for `both`
       *          and specifying whether the left or right key is to
       *          be checked.
       * @param modifier - the modifier which should be checked for
       *                   `Ctrl` keys active.
       * @param both - `true` if any of the two control keys should be
       *               checked and `false` if the `left` value should
       *               be retrieved to get the key to check.
       *               Note that using `false` for this value (default)
       *               will make the `left` parameter ignored.
       * @param left - ignored if `both` is `true`, allows to specify
       *               which of the control keys should be checked.
       * @return - `true` if any `Ctrl` keys is active.
       */
      bool
      ctrlEnabled(const KeyModifier& modifier,
                   bool both = true,
                   bool left = true) noexcept;

      /**
       * @brief - Returns `true` if any of the `Shift` keys is active.
       *          The user can specify whether a specific key should
       *          be checked by specifying a `false` value for `both`
       *          and specifying whether the left or right key is to
       *          be checked.
       *          Note that this include the `CapsLock` key.
       * @param modifier - the modifier which should be checked for
       *                   `Shift` keys active.
       * @param both - `true` if any of the two shift keys should be
       *               checked and `false` if the `left` value should
       *               be retrieved to get the key to check.
       *               Note that using `false` for this value (default)
       *               will make the `left` parameter ignored.
       * @param left - ignored if `both` is `true`, allows to specify
       *               which of the shift keys should be checked.
       * @return - `true` if any `Shift` keys is active.
       */
      bool
      shiftEnabled(const KeyModifier& modifier,
                   bool both = true,
                   bool left = true) noexcept;

      /**
       * @brief - Returns `true` if the keypad is enabled.
       * @param modifier - the modifier which should be checked for
       *                   `Numpad` key active.
       * @return - `true` if the keypad is active, `false` otherwise.
       */
      bool
      numpadEnabled(const KeyModifier& modifier) noexcept;

    }
  }
}

# include "KeyModifier.hxx"
# include "KeyModifier_specialization.hxx"

#endif    /* KEY_MODIFIER_HH */
