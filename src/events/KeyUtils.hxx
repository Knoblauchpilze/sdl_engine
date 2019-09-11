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
            return Key::F;
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
      Modifier
      fromSDLMod(const std::uint16_t& m) {
        // Handle each value and set `None` for unrecognized ones.
        // TODO: Improve modifiers.
        switch (m) {
          case KMOD_LSHIFT:
          case KMOD_RSHIFT:
          case KMOD_CAPS:
            return Modifier::Shift;
          case KMOD_LCTRL:
          case KMOD_RCTRL:
            return Modifier::Ctrl;
          case KMOD_LALT:
          case KMOD_RALT:
            return Modifier::Alt;
          case KMOD_NUM:
          case KMOD_MODE:
          case KMOD_NONE:
          default:
            return Modifier::None;
        }
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
      char
      getCharFromKey(const Key& k,
                     const Modifier& m) noexcept
      {
        // If the key is not alpha numeric, we can't do much.
        switch (k) {
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
          case Key::A:
            return 'a' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::B:
            return 'b' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::C:
            return 'c' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::D:
            return 'd' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::E:
            return 'e' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::F:
            return 'f' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::G:
            return 'g' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::H:
            return 'h' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::I:
            return 'i' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::J:
            return 'j' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::K:
            return 'k' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::L:
            return 'l' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::M:
            return 'm' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::N:
            return 'n' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::O:
            return 'o' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::P:
            return 'p' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::Q:
            return 'q' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::R:
            return 'r' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::S:
            return 's' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::T:
            return 't' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::U:
            return 'u' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::V:
            return 'v' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::W:
            return 'w' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::X:
            return 'x' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::Y:
            return 'y' + (m == Modifier::Shift ? ' ' : '\0');
          case Key::Z:
            return 'z' + (m == Modifier::Shift ? ' ' : '\0');
          default:
            // Not an alphanumeric character, return a default value.
            return '\0';
        }
      }

    }
  }
}

#endif    /* KEY_UTILS_HXX */
