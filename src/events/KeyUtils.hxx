#ifndef    KEY_UTILS_HXX
# define   KEY_UTILS_HXX

# include "KeyUtils.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Key
      fromSDLKey(const SDL_Keycode& k) {
        // Handle each value and set `None` for unrecognized ones.
        switch (k) {
          case SDLK_RETURN:
            return Key::Return;
          case SDLK_ESCAPE:
            return Key::Escape;
          case SDLK_BACKSPACE:
            return Key::BackSpace;
          case SDLK_TAB:
            return Key::Tab;
          case SDLK_SPACE:
            return Key::Space;
          case SDLK_EXCLAIM:
            return Key::Exclaim;
          case SDLK_QUOTEDBL:
            return Key::DoubleQuote;
          case SDLK_HASH:
            return Key::Hash;
          case SDLK_PERCENT:
            return Key::Percent;
          case SDLK_DOLLAR:
            return Key::Dollar;
          case SDLK_AMPERSAND:
            return Key::Ampersand;
          case SDLK_QUOTE:
            return Key::Quote;
          case SDLK_LEFTPAREN:
            return Key::LeftParenthesis;
          case SDLK_RIGHTPAREN:
            return Key::RightParenthesis;
          case SDLK_ASTERISK:
            return Key::Asterisk;
          case SDLK_PLUS:
            return Key::Plus;
          case SDLK_COMMA:
            return Key::Comma;
          case SDLK_MINUS:
            return Key::Minus;
          case SDLK_PERIOD:
            return Key::Period;
          case SDLK_SLASH:
            return Key::Slash;
          case SDLK_0:
            return Key::Zero;
          case SDLK_1:
            return Key::One;
          case SDLK_2:
            return Key::Two;
          case SDLK_3:
            return Key::Three;
          case SDLK_4:
            return Key::Four;
          case SDLK_5:
            return Key::Five;
          case SDLK_6:
            return Key::Six;
          case SDLK_7:
            return Key::Seven;
          case SDLK_8:
            return Key::Eight;
          case SDLK_9:
            return Key::Nine;
          case SDLK_COLON:
            return Key::Colon;
          case SDLK_SEMICOLON:
            return Key::Semicolon;
          case SDLK_LESS:
            return Key::Less;
          case SDLK_EQUALS:
            return Key::Equals;
          case SDLK_GREATER:
            return Key::Greater;
          case SDLK_QUESTION:
            return Key::Question;
          case SDLK_AT:
            return Key::At;
          case SDLK_LEFTBRACKET:
            return Key::LeftBracket;
          case SDLK_BACKSLASH:
            return Key::Backslash;
          case SDLK_RIGHTBRACKET:
            return Key::RightBracket;
          case SDLK_CARET:
            return Key::Caret;
          case SDLK_UNDERSCORE:
            return Key::Underscore;
          case SDLK_BACKQUOTE:
            return Key::Backquote;
          case SDLK_a:
            return Key::A;
          case SDLK_b:
            return Key::B;
          case SDLK_c:
            return Key::C;
          case SDLK_d:
            return Key::D;
          case SDLK_e:
            return Key::E;
          case SDLK_f:
            return Key::F;
          case SDLK_g:
            return Key::G;
          case SDLK_h:
            return Key::H;
          case SDLK_i:
            return Key::I;
          case SDLK_j:
            return Key::J;
          case SDLK_k:
            return Key::K;
          case SDLK_l:
            return Key::L;
          case SDLK_m:
            return Key::M;
          case SDLK_n:
            return Key::N;
          case SDLK_o:
            return Key::O;
          case SDLK_p:
            return Key::P;
          case SDLK_q:
            return Key::Q;
          case SDLK_r:
            return Key::R;
          case SDLK_s:
            return Key::S;
          case SDLK_t:
            return Key::T;
          case SDLK_u:
            return Key::U;
          case SDLK_v:
            return Key::V;
          case SDLK_w:
            return Key::W;
          case SDLK_x:
            return Key::X;
          case SDLK_y:
            return Key::Y;
          case SDLK_z:
            return Key::Z;
          case SDLK_CAPSLOCK:
            return Key::CapsLock;
          case SDLK_F1:
            return Key::F1;
          case SDLK_F2:
            return Key::F2;
          case SDLK_F3:
            return Key::F3;
          case SDLK_F4:
            return Key::F4;
          case SDLK_F5:
            return Key::F5;
          case SDLK_F6:
            return Key::F6;
          case SDLK_F7:
            return Key::F7;
          case SDLK_F8:
            return Key::F8;
          case SDLK_F9:
            return Key::F9;
          case SDLK_F10:
            return Key::F10;
          case SDLK_F11:
            return Key::F11;
          case SDLK_F12:
            return Key::F12;
          case SDLK_PRINTSCREEN:
            return Key::PrintScreen;
          case SDLK_SCROLLLOCK:
            return Key::ScrollLock;
          case SDLK_PAUSE:
            return Key::Pause;
          case SDLK_INSERT:
            return Key::Insert;
          case SDLK_HOME:
            return Key::Home;
          case SDLK_PAGEUP:
            return Key::PageUp;
          case SDLK_DELETE:
            return Key::Delete;
          case SDLK_END:
            return Key::End;
          case SDLK_PAGEDOWN:
            return Key::PageDown;
          case SDLK_RIGHT:
            return Key::Right;
          case SDLK_LEFT:
            return Key::Left;
          case SDLK_DOWN:
            return Key::Down;
          case SDLK_UP:
            return Key::Up;
          case SDLK_NUMLOCKCLEAR:
            return Key::NumLockClear;
          case SDLK_KP_DIVIDE:
            return Key::KPDivide;
          case SDLK_KP_MULTIPLY:
            return Key::KPMultiply;
          case SDLK_KP_MINUS:
            return Key::KPMinus;
          case SDLK_KP_PLUS:
            return Key::KPPlus;
          case SDLK_KP_ENTER:
            return Key::KPEnter;
          case SDLK_KP_1:
            return Key::KP1;
          case SDLK_KP_2:
            return Key::KP2;
          case SDLK_KP_3:
            return Key::KP3;
          case SDLK_KP_4:
            return Key::KP4;
          case SDLK_KP_5:
            return Key::KP5;
          case SDLK_KP_6:
            return Key::KP6;
          case SDLK_KP_7:
            return Key::KP7;
          case SDLK_KP_8:
            return Key::KP8;
          case SDLK_KP_9:
            return Key::KP9;
          case SDLK_KP_0:
            return Key::KP0;
          case SDLK_KP_PERIOD:
            return Key::KPPeriod;
          case SDLK_LCTRL:
            return Key::LeftCtrl;
          case SDLK_LSHIFT:
            return Key::LeftShift;
          case SDLK_LALT:
            return Key::LeftAlt;
          case SDLK_RCTRL:
            return Key::RightCtrl;
          case SDLK_RSHIFT:
            return Key::RightShift;
          case SDLK_RALT:
            return Key::RightAlt;
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
            // This is a alphanumeric character.
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
