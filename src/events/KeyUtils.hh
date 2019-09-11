#ifndef    KEY_UTILS_HH
# define   KEY_UTILS_HH

# include <cstdint>
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      /**
       * @brief - Convenience enumeration describing the modifier associated to a key.
       *          Modifiers typically are represented by control key which might affect
       *          the way a key is interpreted.
       */
      enum class Modifier {
        None,  //<!- Set when no modifier key is pressed.
        Ctrl,  //<!- Set when any of the control keys is pressed.
        Alt,   //<!- Set when any of the alt keys is pressed.
        Shift  //<!- Set when any of the shift keys is pressed.
      };

      /**
       * @brief - Convenience enumeration describing the handled keys by this type of
       *          event. Any key that is not defined here will be mapped to the `None`
       *          value.
       */
      enum class Key {
        // ASCII characters
        None,
        Return,
        Escape,
        BackSpace,
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
        // Caps lock
        CapsLock,
        // Function keys
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
        // Access keys
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
        // Keypad
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
        // Modifiers
        LeftCtrl,
        LeftShift,
        LeftAlt,
        RightCtrl,
        RightShift,
        RightAlt
      };

      /**
       * @brief - Converts the input `SDL` key code to an equivalent key enumeration. If no such
       *          conversion can be performed the value `None` is used.
       * @param k - the `SDL` key code to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      Key
      fromSDLKey(const SDL_Keycode& k);

      /**
       * @brief - Converts the input `SDL` key modifier to an equivalent enumeration. If no such
       *          conversion can be performed the value `None` is used.
       * @param m - the `SDL` modifier to convert.
       * @return - the enumeration value corresponding to the input `SDL` code or `None` if no
       *           such value exist.
       */
      Modifier
      fromSDLMod(const std::uint16_t& m);

      /**
       * @brief - Used to determine whether the input key corresponds to a alphanumeric character.
       * @param k - the key which should be checked for the alphanumeric status.
       * @return - `true` if the key is alphanumeric (i.e. belongs to `[a-z0-9]`) and `false` if
       *           this is not the case.
       */
      bool
      isKeyAlphanumeric(const Key& k) noexcept;

      /**
       * @brief - Returns the character value associated to the input key. Works well for alphanumeric
       *          characters and return '\0' for non alphanumeric values.
       *          Note that one can check whether a character is alphanumeric using the above method.
       * @param k - the key for which the corresponding character should be retrieved.
       * @param m - the modifier currently set. Might modify the corresponding character returned.
       * @return - the character corresponding to the input key or '\0' if no character can be associated
       *           to the key.
       */
      char
      getCharFromKey(const Key& k,
                     const Modifier& m = Modifier::None) noexcept;

    }
  }
}

# include "KeyUtils.hxx"

#endif    /* KEY_UTILS_HH */
