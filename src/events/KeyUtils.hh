#ifndef    KEY_UTILS_HH
# define   KEY_UTILS_HH

# include <cstdint>
# include <SDL2/SDL.h>
# include "KeyModifier.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace keyboard {

        /**
         * @brief - Describes the available keyboard layouts.
         */
        enum class Mode {
          Qwerty,
          Azerty
        };

        /**
         * @brief - Used to try to guess the keyboard layout by interpreting the
         *          associations made by the underlying `API` between the scan
         *          codes of the keys (i.e. their physical positions) and their
         *          key codes (i.e. their logical positions).
         *          Note that an exception is raised if the layout cannot be
         *          guessed.
         * @return - the guessed keyboard layout.
         */
        Mode
        guessLayout();

        /**
         * @brief - Assigns a human-readable name to a keyboard mode. Note that if
         *          the keyboard layout cannot be recognized the string `Unknown`
         *          is returned.
         * @param m - the layout which should be transformed to a human readable
         *            string.
         * @return - the corresponding human-readable string.
         */
        std::string
        toString(const Mode& m) noexcept;

      }

      /**
       * @brief - Convenience enumeration describing the handled keys by this type of
       *          event. Any key that is not defined here will be mapped to the `None`
       *          value.
       *          Note that this describes physical keys as logical position on the
       *          keyboard: in order to get the full set of keys we need to account
       *          for the modifiers and the keyboard layout.
       */
      enum class RawKey {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Zero,

        Return,
        Escape,
        BackSpace,
        Tab,
        Space,

        Minus,
        Equals,
        LeftBracket,
        RightBracket,
        Backslash,
        /* SDL_SCANCODE_NONUSHASH */
        Semicolon,
        /* SDL_SCANCODE_APOSTROPHE */
        Grave,
        Comma,
        Period,
        Slash,
        CapsLock,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        PrintScreen,
        ScrollLock,
        Pause,
        Insert,
        Home,
        PageUp,
        Delete,
        End,
        PageDown,
        Right,
        Left,
        Down,
        Up,

        NumLockClear,
        KPDivide,
        KPMultiply,
        KPMinus,
        KPPlus,
        KPEnter,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KP0,
        KPPeriod,

        /* SDL_SCANCODE_NONUSBACKSLASH */
        /* SDL_SCANCODE_APPLICATION */
        /* SDL_SCANCODE_POWER */
        /* SDL_SCANCODE_KP_EQUALS */
        /* SDL_SCANCODE_F13 */
        /* SDL_SCANCODE_F14 */
        /* SDL_SCANCODE_F15 */
        /* SDL_SCANCODE_F16 */
        /* SDL_SCANCODE_F17 */
        /* SDL_SCANCODE_F18 */
        /* SDL_SCANCODE_F19 */
        /* SDL_SCANCODE_F20 */
        /* SDL_SCANCODE_F21 */
        /* SDL_SCANCODE_F22 */
        /* SDL_SCANCODE_F23 */
        /* SDL_SCANCODE_F24 */
        /* SDL_SCANCODE_EXECUTE */
        /* SDL_SCANCODE_HELP */
        /* SDL_SCANCODE_MENU */
        /* SDL_SCANCODE_SELECT */
        /* SDL_SCANCODE_STOP */
        /* SDL_SCANCODE_AGAIN */
        /* SDL_SCANCODE_UNDO */
        /* SDL_SCANCODE_CUT */
        /* SDL_SCANCODE_COPY */
        /* SDL_SCANCODE_PASTE */
        /* SDL_SCANCODE_FIND */
        /* SDL_SCANCODE_MUTE */
        /* SDL_SCANCODE_VOLUMEUP */
        /* SDL_SCANCODE_VOLUMEDOWN */

        /* SDL_SCANCODE_KP_COMMA */
        /* SDL_SCANCODE_KP_EQUALSAS400 */

        /* SDL_SCANCODE_INTERNATIONAL1 */
        /* SDL_SCANCODE_INTERNATIONAL2 */
        /* SDL_SCANCODE_INTERNATIONAL3 */
        /* SDL_SCANCODE_INTERNATIONAL4 */
        /* SDL_SCANCODE_INTERNATIONAL5 */
        /* SDL_SCANCODE_INTERNATIONAL6 */
        /* SDL_SCANCODE_INTERNATIONAL7 */
        /* SDL_SCANCODE_INTERNATIONAL8 */
        /* SDL_SCANCODE_INTERNATIONAL9 */
        /* SDL_SCANCODE_LANG1 */
        /* SDL_SCANCODE_LANG2 */
        /* SDL_SCANCODE_LANG3 */
        /* SDL_SCANCODE_LANG4 */
        /* SDL_SCANCODE_LANG5 */
        /* SDL_SCANCODE_LANG6 */
        /* SDL_SCANCODE_LANG7 */
        /* SDL_SCANCODE_LANG8 */
        /* SDL_SCANCODE_LANG9 */

        /* SDL_SCANCODE_ALTERASE */
        /* SDL_SCANCODE_SYSREQ */
        /* SDL_SCANCODE_CANCEL */
        /* SDL_SCANCODE_CLEAR */
        /* SDL_SCANCODE_PRIOR */
        /* SDL_SCANCODE_RETURN2 */
        /* SDL_SCANCODE_SEPARATOR */
        /* SDL_SCANCODE_OUT */
        /* SDL_SCANCODE_OPER */
        /* SDL_SCANCODE_CLEARAGAIN */
        /* SDL_SCANCODE_CRSEL */
        /* SDL_SCANCODE_EXSEL */

        /* SDL_SCANCODE_KP_00 */
        /* SDL_SCANCODE_KP_000 */
        /* SDL_SCANCODE_THOUSANDSSEPARATOR */
        /* SDL_SCANCODE_DECIMALSEPARATOR */
        /* SDL_SCANCODE_CURRENCYUNIT */
        /* SDL_SCANCODE_CURRENCYSUBUNIT */
        /* SDL_SCANCODE_KP_LEFTPAREN */
        /* SDL_SCANCODE_KP_RIGHTPAREN */
        /* SDL_SCANCODE_KP_LEFTBRACE */
        /* SDL_SCANCODE_KP_RIGHTBRACE */
        /* SDL_SCANCODE_KP_TAB */
        /* SDL_SCANCODE_KP_BACKSPACE */
        /* SDL_SCANCODE_KP_A */
        /* SDL_SCANCODE_KP_B */
        /* SDL_SCANCODE_KP_C */
        /* SDL_SCANCODE_KP_D */
        /* SDL_SCANCODE_KP_E */
        /* SDL_SCANCODE_KP_F */
        /* SDL_SCANCODE_KP_XOR */
        /* SDL_SCANCODE_KP_POWER */
        /* SDL_SCANCODE_KP_PERCENT */
        /* SDL_SCANCODE_KP_LESS */
        /* SDL_SCANCODE_KP_GREATER */
        /* SDL_SCANCODE_KP_AMPERSAND */
        /* SDL_SCANCODE_KP_DBLAMPERSAND */
        /* SDL_SCANCODE_KP_VERTICALBAR */
        /* SDL_SCANCODE_KP_DBLVERTICALBAR */
        /* SDL_SCANCODE_KP_COLON */
        /* SDL_SCANCODE_KP_HASH */
        /* SDL_SCANCODE_KP_SPACE */
        /* SDL_SCANCODE_KP_AT */
        /* SDL_SCANCODE_KP_EXCLAM */
        /* SDL_SCANCODE_KP_MEMSTORE */
        /* SDL_SCANCODE_KP_MEMRECALL */
        /* SDL_SCANCODE_KP_MEMCLEAR */
        /* SDL_SCANCODE_KP_MEMADD */
        /* SDL_SCANCODE_KP_MEMSUBTRACT */
        /* SDL_SCANCODE_KP_MEMMULTIPLY */
        /* SDL_SCANCODE_KP_MEMDIVIDE */
        /* SDL_SCANCODE_KP_PLUSMINUS */
        /* SDL_SCANCODE_KP_CLEAR */
        /* SDL_SCANCODE_KP_CLEARENTRY */
        /* SDL_SCANCODE_KP_BINARY */
        /* SDL_SCANCODE_KP_OCTAL */
        /* SDL_SCANCODE_KP_DECIMAL */
        /* SDL_SCANCODE_KP_HEXADECIMAL */

        LeftCtrl,
        LeftShift,
        LeftAlt,
        LeftCommand,
        RightCtrl,
        RightShift,
        RightAlt,
        RightCommand,

        /* SDL_SCANCODE_MODE */
        /* SDL_SCANCODE_AUDIONEXT */
        /* SDL_SCANCODE_AUDIOPREV */
        /* SDL_SCANCODE_AUDIOSTOP */
        /* SDL_SCANCODE_AUDIOPLAY */
        /* SDL_SCANCODE_AUDIOMUTE */
        /* SDL_SCANCODE_MEDIASELECT */
        /* SDL_SCANCODE_WWW */
        /* SDL_SCANCODE_MAIL */
        /* SDL_SCANCODE_CALCULATOR */
        /* SDL_SCANCODE_COMPUTER */
        /* SDL_SCANCODE_AC_SEARCH */
        /* SDL_SCANCODE_AC_HOME */
        /* SDL_SCANCODE_AC_BACK */
        /* SDL_SCANCODE_AC_FORWARD */
        /* SDL_SCANCODE_AC_STOP */
        /* SDL_SCANCODE_AC_REFRESH */
        /* SDL_SCANCODE_AC_BOOKMARKS */

        /* SDL_SCANCODE_BRIGHTNESSDOWN */
        /* SDL_SCANCODE_BRIGHTNESSUP */
        /* SDL_SCANCODE_DISPLAYSWITCH */
        /* SDL_SCANCODE_KBDILLUMTOGGLE */
        /* SDL_SCANCODE_KBDILLUMDOWN */
        /* SDL_SCANCODE_KBDILLUMUP */
        /* SDL_SCANCODE_EJECT */
        /* SDL_SCANCODE_SLEEP */

        /* SDL_SCANCODE_APP1 */
        /* SDL_SCANCODE_APP2 */

        /* SDL_SCANCODE_AUDIOREWIND */
        /* SDL_SCANCODE_AUDIOFASTFORWARD */
        /* SDL_NUM_SCANCODES */

        None
      };

      /**
       * @brief - Convenience enumeration describing the handled keys by this type
       *          of event. Note that compared to the `RawKey` state we add some more
       *          keys which comes from interpretation of the keyboard layout. As an
       *          example the `Ampersand` key is not part of the `RawKey` enumeration
       *          because there's no physical keys linked to it, but it is part of the
       *          interpreted keys as the french layout as a logical key (matching a
       *          physical key defined in `RawKey`) which is an `Ampersand`.
       */
      enum class Key {
        Return,
        Escape,
        Backspace,
        Tab,
        Space,
        Exclaim,
        DoubleQuote,
        Hash,
        Percent,
        Dollar,
        Ampersand,
        Quote,
        LeftParenthesis,
        RightParenthesis,
        Asterisk,
        Plus,
        Comma,
        Minus,
        Period,
        Slash,
        Zero,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Colon,
        Semicolon,
        Less,
        Equals,
        Greater,
        Question,
        At,

        LeftBracket,
        Backslash,
        RightBracket,
        Caret,
        Underscore,
        Backquote,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        CapsLock,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        PrintScreen,
        ScrollLock,
        Pause,
        Insert,
        Home,
        PageUp,
        Delete,
        End,
        PageDown,
        Right,
        Left,
        Down,
        Up,

        NumLockClear,
        KPDivide,
        KPMultiply,
        KPMinus,
        KPPlus,
        KPEnter,
        KP1,
        KP2,
        KP3,
        KP4,
        KP5,
        KP6,
        KP7,
        KP8,
        KP9,
        KP0,
        KPPeriod,

        /* SDLK_APPLICATION */
        /* SDLK_POWER */
        /* SDLK_KP_EQUALS */
        /* SDLK_F13 */
        /* SDLK_F14 */
        /* SDLK_F15 */
        /* SDLK_F16 */
        /* SDLK_F17 */
        /* SDLK_F18 */
        /* SDLK_F19 */
        /* SDLK_F20 */
        /* SDLK_F21 */
        /* SDLK_F22 */
        /* SDLK_F23 */
        /* SDLK_F24 */
        /* SDLK_EXECUTE */
        /* SDLK_HELP */
        /* SDLK_MENU */
        /* SDLK_SELECT */
        /* SDLK_STOP */
        /* SDLK_AGAIN */
        /* SDLK_UNDO */
        /* SDLK_CUT */
        /* SDLK_COPY */
        /* SDLK_PASTE */
        /* SDLK_FIND */
        /* SDLK_MUTE */
        /* SDLK_VOLUMEUP */
        /* SDLK_VOLUMEDOWN */
        /* SDLK_KP_COMMA */
        /* SDLK_KP_EQUALSAS400 */

        /* SDLK_ALTERASE */
        /* SDLK_SYSREQ */
        /* SDLK_CANCEL */
        /* SDLK_CLEAR */
        /* SDLK_PRIOR */
        /* SDLK_RETURN2 */
        /* SDLK_SEPARATOR */
        /* SDLK_OUT */
        /* SDLK_OPER */
        /* SDLK_CLEARAGAIN */
        /* SDLK_CRSEL */
        /* SDLK_EXSEL */

        /* SDLK_KP_00 */
        /* SDLK_KP_000 */
        /* SDLK_THOUSANDSSEPARATOR */
        /* SDLK_DECIMALSEPARATOR */
        /* SDLK_CURRENCYUNIT */
        /* SDLK_CURRENCYSUBUNIT */
        /* SDLK_KP_LEFTPAREN */
        /* SDLK_KP_RIGHTPAREN */
        /* SDLK_KP_LEFTBRACE */
        /* SDLK_KP_RIGHTBRACE */
        /* SDLK_KP_TAB */
        /* SDLK_KP_BACKSPACE */
        /* SDLK_KP_A */
        /* SDLK_KP_B */
        /* SDLK_KP_C */
        /* SDLK_KP_D */
        /* SDLK_KP_E */
        /* SDLK_KP_F */
        /* SDLK_KP_XOR */
        /* SDLK_KP_POWER */
        /* SDLK_KP_PERCENT */
        /* SDLK_KP_LESS */
        /* SDLK_KP_GREATER */
        /* SDLK_KP_AMPERSAND */
        /* SDLK_KP_DBLAMPERSAND */
        /* SDLK_KP_VERTICALBAR */
        /* SDLK_KP_DBLVERTICALBAR */
        /* SDLK_KP_COLON */
        /* SDLK_KP_HASH */
        /* SDLK_KP_SPACE */
        /* SDLK_KP_AT */
        /* SDLK_KP_EXCLAM */
        /* SDLK_KP_MEMSTORE */
        /* SDLK_KP_MEMRECALL */
        /* SDLK_KP_MEMCLEAR */
        /* SDLK_KP_MEMADD */
        /* SDLK_KP_MEMSUBTRACT */
        /* SDLK_KP_MEMMULTIPLY */
        /* SDLK_KP_MEMDIVIDE */
        /* SDLK_KP_PLUSMINUS */
        /* SDLK_KP_CLEAR */
        /* SDLK_KP_CLEARENTRY */
        /* SDLK_KP_BINARY */
        /* SDLK_KP_OCTAL */
        /* SDLK_KP_DECIMAL */
        /* SDLK_KP_HEXADECIMAL */

        LeftCtrl,
        LeftShift,
        LeftAlt,
        LeftCommand,
        RightCtrl,
        RightShift,
        RightAlt,
        RightCommand,

        /* SDLK_MODE */

        /* SDLK_AUDIONEXT */
        /* SDLK_AUDIOPREV */
        /* SDLK_AUDIOSTOP */
        /* SDLK_AUDIOPLAY */
        /* SDLK_AUDIOMUTE */
        /* SDLK_MEDIASELECT */
        /* SDLK_WWW */
        /* SDLK_MAIL */
        /* SDLK_CALCULATOR */
        /* SDLK_COMPUTER */
        /* SDLK_AC_SEARCH */
        /* SDLK_AC_HOME */
        /* SDLK_AC_BACK */
        /* SDLK_AC_FORWARD */
        /* SDLK_AC_STOP */
        /* SDLK_AC_REFRESH */
        /* SDLK_AC_BOOKMARKS */

        /* SDLK_BRIGHTNESSDOWN */
        /* SDLK_BRIGHTNESSUP */
        /* SDLK_DISPLAYSWITCH */
        /* SDLK_KBDILLUMTOGGLE */
        /* SDLK_KBDILLUMDOWN */
        /* SDLK_KBDILLUMUP */
        /* SDLK_EJECT */
        /* SDLK_SLEEP */
        /* SDLK_APP1 */
        /* SDLK_APP2 */

        /* SDLK_AUDIOREWIND */
        /* SDLK_AUDIOFASTFORWARD */

        None
      };

      /**
       * @brief - Converts the input `SDL` scan code to an equivalent key enumeration. If no such
       *          conversion can be performed the value `None` is used.
       *          Note that a scan code is linked to a physical position of a key on the keyboard
       *          and does not take into consideration the layout of the keyboard.
       * @param k - the `SDL` scan code to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      RawKey
      fromSDLScancode(const SDL_Scancode& k);

      /**
       * @brief - Converts the input `SDL` key modifier to an equivalent enumeration. If no such
       *          conversion can be performed the value `None` is used.
       * @param m - the `SDL` modifier to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      KeyModifier
      fromSDLMod(std::uint16_t m);

      /**
       * @brief - Used to determine whether the input key corresponds to a alphanumeric character.
       *          The key alone is not enough to determine whether it is alphanumeric because some
       *          modifiers might transform a non-alphanumeric key into a digit or a letter.
       *          Also the keyboard layout is important to determine whether the physical key is
       *          mapped to an alphanumeric character.
       * @param key - the key which should be checked for the alphanumeric status.
       * @param modes - the modifiers associated to the physical key in input.
       * @param mode - the keyboard layout which produced the input key.
       * @return - `true` if the key is alphanumeric (i.e. belongs to `[a-A-Z0-9]`) and `false` if
       *           this is not the case.
       */
      bool
      isKeyAlphanumeric(const RawKey& key,
                        const KeyModifier& mods,
                        const keyboard::Mode& mode) noexcept;

      /**
       * @brief - Used to determine whether the input key can be displayed or not. This allows to
       *          filter special key which do not have a visual representation (like modifiers and
       *          motion keys).
       *          The key alone is not enough to determine whether it is alphanumeric because some
       *          modifiers might transform a non-alphanumeric key into a digit or a letter.
       *          Also the keyboard layout is important to determine whether the physical key is
       *          mapped to an alphanumeric character.
       * @param key - the key which should be checked for displayability.
       * @param modes - the modifiers associated to the physical key in input.
       * @param mode - the keyboard layout which produced the input key.
       * @return - `true` if the key can be displayed and `false` if this is not the case.
       */
      bool
      isKeyPrintable(const RawKey& key,
                     const KeyModifier& mods,
                     const keyboard::Mode& mode) noexcept;

      /**
       * @brief - Returns the character value associated to the input key. Works well for alphanumeric
       *          characters and return '\0' for non alphanumeric values.
       *          Note that one can check whether a character is alphanumeric using the above method.
       * @param key - the key for which the corresponding character should be retrieved.
       * @param mods - the modifier currently set. Might modify the corresponding character returned.
       * @param mode - the keyboard mode.
       * @return - the character corresponding to the input key or '\0' if no character can be associated
       *           to the key.
       */
      char
      getCharFromKey(const RawKey& key,
                     const KeyModifier& mods,
                     const keyboard::Mode& mode) noexcept;

    }
  }
}

# include "KeyUtils.hxx"

#endif    /* KEY_UTILS_HH */
