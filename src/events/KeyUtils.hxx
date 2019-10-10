#ifndef    KEY_UTILS_HXX
# define   KEY_UTILS_HXX

# include "KeyUtils.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Key
      fromSDLScancode(const SDL_Scancode& k) {
        // Handle each value and set `None` for unrecognized ones.
        switch (k) {
          case SDL_SCANCODE_A:
            return Key::A;
          case SDL_SCANCODE_B:
            return Key::B;
          case SDL_SCANCODE_C:
            return Key::C;
          case SDL_SCANCODE_D:
            return Key::D;
          case SDL_SCANCODE_E:
            return Key::E;
          case SDL_SCANCODE_F:
            return Key::F;
          case SDL_SCANCODE_G:
            return Key::G;
          case SDL_SCANCODE_H:
            return Key::H;
          case SDL_SCANCODE_I:
            return Key::I;
          case SDL_SCANCODE_J:
            return Key::J;
          case SDL_SCANCODE_K:
            return Key::K;
          case SDL_SCANCODE_L:
            return Key::L;
          case SDL_SCANCODE_M:
            return Key::M;
          case SDL_SCANCODE_N:
            return Key::N;
          case SDL_SCANCODE_O:
            return Key::O;
          case SDL_SCANCODE_P:
            return Key::P;
          case SDL_SCANCODE_Q:
            return Key::Q;
          case SDL_SCANCODE_R:
            return Key::R;
          case SDL_SCANCODE_S:
            return Key::S;
          case SDL_SCANCODE_T:
            return Key::T;
          case SDL_SCANCODE_U:
            return Key::U;
          case SDL_SCANCODE_V:
            return Key::V;
          case SDL_SCANCODE_W:
            return Key::W;
          case SDL_SCANCODE_X:
            return Key::X;
          case SDL_SCANCODE_Y:
            return Key::Y;
          case SDL_SCANCODE_Z:
            return Key::Z;
          case SDL_SCANCODE_1:
            return Key::One;
          case SDL_SCANCODE_2:
            return Key::Two;
          case SDL_SCANCODE_3:
            return Key::Three;
          case SDL_SCANCODE_4:
            return Key::Four;
          case SDL_SCANCODE_5:
            return Key::Five;
          case SDL_SCANCODE_6:
            return Key::Six;
          case SDL_SCANCODE_7:
            return Key::Seven;
          case SDL_SCANCODE_8:
            return Key::Eight;
          case SDL_SCANCODE_9:
            return Key::Nine;
          case SDL_SCANCODE_0:
            return Key::Zero;

          case SDL_SCANCODE_RETURN:
            return Key::Return;
          case SDL_SCANCODE_ESCAPE:
            return Key::Escape;
          case SDL_SCANCODE_BACKSPACE:
            return Key::BackSpace;
          case SDL_SCANCODE_TAB:
            return Key::Tab;
          case SDL_SCANCODE_SPACE:
            return Key::Space;

          case SDL_SCANCODE_MINUS:
            return Key::Minus;
          case SDL_SCANCODE_EQUALS:
            return Key::Equals;
          case SDL_SCANCODE_LEFTBRACKET:
            return Key::LeftBracket;
          case SDL_SCANCODE_RIGHTBRACKET:
            return Key::RightBracket;
          case SDL_SCANCODE_BACKSLASH:
            return Key::Backslash;
          /* SDL_SCANCODE_NONUSHASH */
          case SDL_SCANCODE_SEMICOLON:
            return Key::Semicolon;
          case SDL_SCANCODE_APOSTROPHE:
            return Key::Apostrophe;
          case SDL_SCANCODE_GRAVE:
            return Key::Grave;
          case SDL_SCANCODE_COMMA:
            return Key::Comma;
          case SDL_SCANCODE_PERIOD:
            return Key::Period;
          case SDL_SCANCODE_SLASH:
            return Key::Slash;
          case SDL_SCANCODE_CAPSLOCK:
            return Key::CapsLock;

          case SDL_SCANCODE_F1:
            return Key::F1;
          case SDL_SCANCODE_F2:
            return Key::F2;
          case SDL_SCANCODE_F3:
            return Key::F3;
          case SDL_SCANCODE_F4:
            return Key::F4;
          case SDL_SCANCODE_F5:
            return Key::F5;
          case SDL_SCANCODE_F6:
            return Key::F6;
          case SDL_SCANCODE_F7:
            return Key::F7;
          case SDL_SCANCODE_F8:
            return Key::F8;
          case SDL_SCANCODE_F9:
            return Key::F9;
          case SDL_SCANCODE_F10:
            return Key::F10;
          case SDL_SCANCODE_F11:
            return Key::F11;
          case SDL_SCANCODE_F12:
            return Key::F12;

          case SDL_SCANCODE_PRINTSCREEN:
            return Key::PrintScreen;
          case SDL_SCANCODE_SCROLLLOCK:
            return Key::ScrollLock;
          case SDL_SCANCODE_PAUSE:
            return Key::Pause;
          case SDL_SCANCODE_INSERT:
            return Key::Insert;
          case SDL_SCANCODE_HOME:
            return Key::Home;
          case SDL_SCANCODE_PAGEUP:
            return Key::PageUp;
          case SDL_SCANCODE_DELETE:
            return Key::Delete;
          case SDL_SCANCODE_END:
            return Key::End;
          case SDL_SCANCODE_PAGEDOWN:
            return Key::PageDown;
          case SDL_SCANCODE_RIGHT:
            return Key::Right;
          case SDL_SCANCODE_LEFT:
            return Key::Left;
          case SDL_SCANCODE_DOWN:
            return Key::Down;
          case SDL_SCANCODE_UP:
            return Key::Up;

          case SDL_SCANCODE_NUMLOCKCLEAR:
            return Key::NumLockClear;
          case SDL_SCANCODE_KP_DIVIDE:
            return Key::KPDivide;
          case SDL_SCANCODE_KP_MULTIPLY:
            return Key::KPMultiply;
          case SDL_SCANCODE_KP_MINUS:
            return Key::KPMinus;
          case SDL_SCANCODE_KP_PLUS:
            return Key::KPPlus;
          case SDL_SCANCODE_KP_ENTER:
            return Key::KPEnter;
          case SDL_SCANCODE_KP_1:
            return Key::KP1;
          case SDL_SCANCODE_KP_2:
            return Key::KP2;
          case SDL_SCANCODE_KP_3:
            return Key::KP3;
          case SDL_SCANCODE_KP_4:
            return Key::KP4;
          case SDL_SCANCODE_KP_5:
            return Key::KP5;
          case SDL_SCANCODE_KP_6:
            return Key::KP6;
          case SDL_SCANCODE_KP_7:
            return Key::KP7;
          case SDL_SCANCODE_KP_8:
            return Key::KP8;
          case SDL_SCANCODE_KP_9:
            return Key::KP9;
          case SDL_SCANCODE_KP_0:
            return Key::KP0;
          case SDL_SCANCODE_KP_PERIOD:
            return Key::KPPeriod;

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

          case SDL_SCANCODE_LCTRL:
            return Key::LeftCtrl;
          case SDL_SCANCODE_LSHIFT:
            return Key::LeftShift;
          case SDL_SCANCODE_LALT:
            return Key::LeftAlt;
          case SDL_SCANCODE_LGUI:
            return Key::LeftCommand;
          case SDL_SCANCODE_RCTRL:
            return Key::RightCtrl;
          case SDL_SCANCODE_RSHIFT:
            return Key::RightShift;
          case SDL_SCANCODE_RALT:
            return Key::RightAlt;
          case SDL_SCANCODE_RGUI:
            return Key::RightCommand;

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
          default:
            return Key::None;
        }
      }

      inline
      KeyModifier
      fromSDLMod(const std::uint16_t& m) {
        // Handle each value and set `None` for unrecognized ones.
        KeyModifier mods;

        if (m & KMOD_LALT) {
          mods.set(modifier::Mode::LeftAlt);
        }
        if (m & KMOD_LCTRL) {
          mods.set(modifier::Mode::LeftCtrl);
        }
        if (m & KMOD_LSHIFT) {
          mods.set(modifier::Mode::LeftShift);
        }

        if (m & KMOD_RALT) {
          mods.set(modifier::Mode::RightAlt);
        }
        if (m & KMOD_RCTRL) {
          mods.set(modifier::Mode::RightCtrl);
        }
        if (m & KMOD_RSHIFT) {
          mods.set(modifier::Mode::RightShift);
        }


        if (m & KMOD_CAPS) {
          mods.set(modifier::Mode::Caps);
        }
        if (m & KMOD_NUM) {
          mods.set(modifier::Mode::Num);
        }

        // Return the built-in modifiers.
        return mods;
      }

      inline
      bool
      isKeyAlphanumeric(const Key& k) noexcept {
        switch (k) {
          case Key::A:
          case Key::B:
          case Key::C:
          case Key::D:
          case Key::E:
          case Key::F:
          case Key::G:
          case Key::H:
          case Key::I:
          case Key::J:
          case Key::K:
          case Key::L:
          case Key::M:
          case Key::N:
          case Key::O:
          case Key::P:
          case Key::Q:
          case Key::R:
          case Key::S:
          case Key::T:
          case Key::U:
          case Key::V:
          case Key::W:
          case Key::X:
          case Key::Y:
          case Key::Z:
          case Key::Zero:
          case Key::One:
          case Key::Two:
          case Key::Three:
          case Key::Four:
          case Key::Five:
          case Key::Six:
          case Key::Seven:
          case Key::Eight:
          case Key::Nine:
            return true;
          default:
            // Not an alphanumeric character.
            return false;
        }
      }

      inline
      bool
      isKeyPrintable(const Key& k) noexcept {
        switch(k) {
          case Key::Space:
          case Key::Exclaim:
          case Key::DoubleQuote:
          case Key::Hash:
          case Key::Percent:
          case Key::Dollar:
          case Key::Ampersand:
          case Key::Quote:
          case Key::LeftParenthesis:
          case Key::RightParenthesis:
          case Key::Asterisk:
          case Key::Plus:
          case Key::Comma:
          case Key::Minus:
          case Key::Period:
          case Key::Slash:
          case Key::Zero:
          case Key::One:
          case Key::Two:
          case Key::Three:
          case Key::Four:
          case Key::Five:
          case Key::Six:
          case Key::Seven:
          case Key::Eight:
          case Key::Nine:
          case Key::Colon:
          case Key::Semicolon:
          case Key::Less:
          case Key::Equals:
          case Key::Greater:
          case Key::Question:
          case Key::At:
          case Key::LeftBracket:
          case Key::Backslash:
          case Key::RightBracket:
          case Key::Caret:
          case Key::Underscore:
          case Key::Backquote:
          case Key::A:
          case Key::B:
          case Key::C:
          case Key::D:
          case Key::E:
          case Key::F:
          case Key::G:
          case Key::H:
          case Key::I:
          case Key::J:
          case Key::K:
          case Key::L:
          case Key::M:
          case Key::N:
          case Key::O:
          case Key::P:
          case Key::Q:
          case Key::R:
          case Key::S:
          case Key::T:
          case Key::U:
          case Key::V:
          case Key::W:
          case Key::X:
          case Key::Y:
          case Key::Z:
          case Key::KPDivide:
          case Key::KPMultiply:
          case Key::KPMinus:
          case Key::KPPlus:
          case Key::KPEnter:
          case Key::KP1:
          case Key::KP2:
          case Key::KP3:
          case Key::KP4:
          case Key::KP5:
          case Key::KP6:
          case Key::KP7:
          case Key::KP8:
          case Key::KP9:
          case Key::KP0:
          case Key::KPPeriod:
            // Key is printable.
            return true;
          default:
            // Not printable.
            return false;
        }
      }

      inline
      char
      getCharFromKey(const Key& k,
                     const KeyModifier& m) noexcept
      {
        // If the key is not alpha numeric, we can't do much.
        // We also need to consider the input modifiers.
        const char offset = (shiftEnabled(m) ? ' ' : '\0');

        // TODO: We should probably change the way we handle the keys to something
        // maybe similar to here: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html.
        // This would help to account for more characters and the layout.
        // Apparently the best way would be to use scan codes instead of key codes. So we should
        // probably do that as well. So basically the process would be to use scan code and translate it into
        // our own key code if needed.
        // The thing is that we would modify this function to actually account for the various conditions.
        // So typically if the user press the `è` key on a `AZERTY` keyboard we would produce an event with the
        // key `Key::Seven` and only translates it to `è` in this method based on whether we're on a `QWERTY`
        // keyboard or `AZERTY` keyboard.

        switch (k) {
          case Key::Space:
            return ' ';
          case Key::Exclaim:
            return '!';
          case Key::DoubleQuote:
            return '"';
          case Key::Hash:
            return '#';
          case Key::Percent:
            return '%';
          case Key::Dollar:
            return '$';
          case Key::Ampersand:
            return '&';
          case Key::Quote:
            return '\'';
          case Key::LeftParenthesis:
            return '(';
          case Key::RightParenthesis:
            return ')';
          case Key::Asterisk:
            return '*';
          case Key::Plus:
            return '+';
          case Key::Comma:
            return ',';
          case Key::Minus:
            return '-';
          case Key::Period:
            return '.';
          case Key::Slash:
            return '/';
          case Key::Zero:
            return '0';
          case Key::One:
            return '1';
          case Key::Two:
            return '2';
          case Key::Three:
            return '3';
          case Key::Four:
            return '4';
          case Key::Five:
            return '5';
          case Key::Six:
            return '6';
          case Key::Seven:
            return '7';
          case Key::Eight:
            return '8';
          case Key::Nine:
            return '9';
          case Key::Colon:
            return ':';
          case Key::Semicolon:
            return ';';
          case Key::Less:
            return '<';
          case Key::Equals:
            return '=';
          case Key::Greater:
            return '>';
          case Key::Question:
            return '?';
          case Key::At:
            return '@';
          case Key::LeftBracket:
            return '[';
          case Key::Backslash:
            return '\\';
          case Key::RightBracket:
            return ']';
          case Key::Caret:
            return '^';
          case Key::Underscore:
            return '_';
          case Key::Backquote:
            return '`';
          case Key::A:
            return 'a' - offset;
          case Key::B:
            return 'b' - offset;
          case Key::C:
            return 'c' - offset;
          case Key::D:
            return 'd' - offset;
          case Key::E:
            return 'e' - offset;
          case Key::F:
            return 'f' - offset;
          case Key::G:
            return 'g' - offset;
          case Key::H:
            return 'h' - offset;
          case Key::I:
            return 'i' - offset;
          case Key::J:
            return 'j' - offset;
          case Key::K:
            return 'k' - offset;
          case Key::L:
            return 'l' - offset;
          case Key::M:
            return 'm' - offset;
          case Key::N:
            return 'n' - offset;
          case Key::O:
            return 'o' - offset;
          case Key::P:
            return 'p' - offset;
          case Key::Q:
            return 'q' - offset;
          case Key::R:
            return 'r' - offset;
          case Key::S:
            return 's' - offset;
          case Key::T:
            return 't' - offset;
          case Key::U:
            return 'u' - offset;
          case Key::V:
            return 'v' - offset;
          case Key::W:
            return 'w' - offset;
          case Key::X:
            return 'x' - offset;
          case Key::Y:
            return 'y' - offset;
          case Key::Z:
            return 'z' - offset;
          case Key::KPDivide:
            return '/';
          case Key::KPMultiply:
            return '*';
          case Key::KPMinus:
            return '-';
          case Key::KPPlus:
            return '+';
          case Key::KP1:
            return '1';
          case Key::KP2:
            return '2';
          case Key::KP3:
            return '3';
          case Key::KP4:
            return '4';
          case Key::KP5:
            return '5';
          case Key::KP6:
            return '6';
          case Key::KP7:
            return '7';
          case Key::KP8:
            return '8';
          case Key::KP9:
            return '9';
          case Key::KP0:
            return '0';
          case Key::KPPeriod:
            return '.';
          default:
            // Not an alphanumeric character, return a default value.
            return '\0';
        }
      }

    }
  }
}

#endif    /* KEY_UTILS_HXX */
