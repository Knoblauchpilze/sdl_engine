
# include "KeyUtils.hh"

namespace {

  bool
  isQWERTYKeyAlphanumeric(const ::sdl::core::engine::RawKey& key,
                          const ::sdl::core::engine::KeyModifier& mods) noexcept
  {
    using namespace sdl::core::engine;

    // Compute information on the modifiers.
    const bool shift = shiftEnabled(mods);
    const bool altGr = altEnabled(mods, false, false);

    // We have several case based on whether the key always produce a alphanumeric
    // character or only based on some modifiers. Certain keys also never produce
    // any alphanumeric characters.
    switch (key) {
      case RawKey::A:
      case RawKey::E:
      case RawKey::B:
      case RawKey::F:
      case RawKey::G:
      case RawKey::H:
      case RawKey::I:
      case RawKey::J:
      case RawKey::K:
      case RawKey::L:
      case RawKey::N:
      case RawKey::O:
      case RawKey::P:
      case RawKey::Q:
      case RawKey::U:
      case RawKey::V:
      case RawKey::W:
      case RawKey::X:
      case RawKey::Y:

      case RawKey::Space:

      case RawKey::KP1:
      case RawKey::KP2:
      case RawKey::KP3:
      case RawKey::KP4:
      case RawKey::KP5:
      case RawKey::KP6:
      case RawKey::KP7:
      case RawKey::KP8:
      case RawKey::KP9:
      case RawKey::KP0:
        return true;

      case RawKey::S:
        return !shift || !altGr;

      case RawKey::One:
      case RawKey::Two:
      case RawKey::Three:
      case RawKey::Four:
      case RawKey::Five:
      case RawKey::Six:
      case RawKey::Seven:
      case RawKey::Eight:
      case RawKey::Nine:
      case RawKey::Zero:
        return !shift && !altGr;

      case RawKey::C:
      case RawKey::T:
      case RawKey::Z:
        return !altGr;

      case RawKey::Comma:
        return altGr;

      case RawKey::D:
      case RawKey::M:
      case RawKey::R:
        return shift || !altGr;

      default:
        return false;
    }
  }

  bool
  isAZERTYKeyAlphanumeric(const ::sdl::core::engine::RawKey& key,
                          const ::sdl::core::engine::KeyModifier& mods) noexcept
  {
    using namespace sdl::core::engine;

    // Compute information on the modifiers.
    const bool shift = shiftEnabled(mods);
    const bool altGr = altEnabled(mods, false, false);

    // We have several case based on whether the key always produce an alphanumeric
    // character or only based on some modifiers. Certain keys also never produce
    // any alphanumeric characters.
    switch (key) {
      case RawKey::A:
      case RawKey::D:
      case RawKey::J:
      case RawKey::K:
      case RawKey::I:
      case RawKey::P:
      case RawKey::R:
      case RawKey::U:
      case RawKey::W:
      case RawKey::Y:

      case RawKey::Space:

      case RawKey::Semicolon:

      case RawKey::KP1:
      case RawKey::KP2:
      case RawKey::KP3:
      case RawKey::KP4:
      case RawKey::KP5:
      case RawKey::KP6:
      case RawKey::KP7:
      case RawKey::KP8:
      case RawKey::KP9:
      case RawKey::KP0:
        return true;

      case RawKey::RightBracket:
        return altGr;

      case RawKey::B:
      case RawKey::C:
      case RawKey::E:
      case RawKey::F:
      case RawKey::G:
      case RawKey::L:
      case RawKey::N:
      case RawKey::O:
      case RawKey::Q:
      case RawKey::T:
      case RawKey::V:
      case RawKey::X:
      case RawKey::Z:
        return !altGr;

      case RawKey::Four:
      case RawKey::Five:
      case RawKey::Six:
      case RawKey::Eight:
        return shift && !altGr;

      case RawKey::H:

      case RawKey::Zero:
      case RawKey::Two:
      case RawKey::Seven:
      case RawKey::Nine:
        return shift || !altGr;

      case RawKey::One:
      case RawKey::Three:
        return shift;

      case RawKey::S:
        return !shift || !altGr;

      default:
        return false;
    }
  }

  bool
  isQWERTYKeyPrintable(const ::sdl::core::engine::RawKey& key,
                       const ::sdl::core::engine::KeyModifier& /*mods*/) noexcept
  {
    using namespace sdl::core::engine;

    // We have several case based on whether the key always produce a displayable
    // character or only based on some modifiers. Certain keys also never produce
    // any displayable characters.
    switch (key) {
      case RawKey::A:
      case RawKey::B:
      case RawKey::C:
      case RawKey::D:
      case RawKey::E:
      case RawKey::F:
      case RawKey::G:
      case RawKey::H:
      case RawKey::I:
      case RawKey::J:
      case RawKey::K:
      case RawKey::L:
      case RawKey::M:
      case RawKey::N:
      case RawKey::O:
      case RawKey::P:
      case RawKey::Q:
      case RawKey::R:
      case RawKey::S:
      case RawKey::T:
      case RawKey::U:
      case RawKey::V:
      case RawKey::W:
      case RawKey::X:
      case RawKey::Y:
      case RawKey::Z:
      case RawKey::Zero:
      case RawKey::One:
      case RawKey::Two:
      case RawKey::Three:
      case RawKey::Four:
      case RawKey::Five:
      case RawKey::Six:
      case RawKey::Seven:
      case RawKey::Eight:
      case RawKey::Nine:

      case RawKey::Space:

      case RawKey::Minus:
      case RawKey::Equals:
      case RawKey::LeftBracket:
      case RawKey::RightBracket:
      case RawKey::Backslash:
      case RawKey::Semicolon:
      case RawKey::Grave:
      case RawKey::Comma:
      case RawKey::Period:
      case RawKey::Slash:

      case RawKey::KPDivide:
      case RawKey::KPMultiply:
      case RawKey::KPMinus:
      case RawKey::KPPlus:
      case RawKey::KP1:
      case RawKey::KP2:
      case RawKey::KP3:
      case RawKey::KP4:
      case RawKey::KP5:
      case RawKey::KP6:
      case RawKey::KP7:
      case RawKey::KP8:
      case RawKey::KP9:
      case RawKey::KP0:
      case RawKey::KPPeriod:
        return true;
      default:
        // Default case is to not be printable.
        return false;
    }
  }

  bool
  isAZERTYKeyPrintable(const ::sdl::core::engine::RawKey& key,
                       const ::sdl::core::engine::KeyModifier& /*mods*/) noexcept
  {
    using namespace sdl::core::engine;

    // We have several case based on whether the key always produce a displayable
    // character or only based on some modifiers. Certain keys also never produce
    // any displayable characters.
    switch (key) {
      case RawKey::A:
      case RawKey::B:
      case RawKey::C:
      case RawKey::D:
      case RawKey::E:
      case RawKey::F:
      case RawKey::G:
      case RawKey::H:
      case RawKey::I:
      case RawKey::J:
      case RawKey::K:
      case RawKey::L:
      case RawKey::M:
      case RawKey::N:
      case RawKey::O:
      case RawKey::P:
      case RawKey::Q:
      case RawKey::R:
      case RawKey::S:
      case RawKey::T:
      case RawKey::U:
      case RawKey::V:
      case RawKey::W:
      case RawKey::X:
      case RawKey::Y:
      case RawKey::Z:
      case RawKey::Zero:
      case RawKey::One:
      case RawKey::Two:
      case RawKey::Three:
      case RawKey::Four:
      case RawKey::Five:
      case RawKey::Six:
      case RawKey::Seven:
      case RawKey::Eight:
      case RawKey::Nine:

      case RawKey::Space:

      case RawKey::Minus:
      case RawKey::Equals:
      case RawKey::LeftBracket:
      case RawKey::RightBracket:
      case RawKey::Backslash:
      case RawKey::Semicolon:
      case RawKey::Grave:
      case RawKey::Comma:
      case RawKey::Period:
      case RawKey::Slash:

      case RawKey::KPDivide:
      case RawKey::KPMultiply:
      case RawKey::KPMinus:
      case RawKey::KPPlus:
      case RawKey::KP1:
      case RawKey::KP2:
      case RawKey::KP3:
      case RawKey::KP4:
      case RawKey::KP5:
      case RawKey::KP6:
      case RawKey::KP7:
      case RawKey::KP8:
      case RawKey::KP9:
      case RawKey::KP0:
      case RawKey::KPPeriod:
        return true;
      default:
        // Default case is to not be printable.
        return false;
    }
  }

// TODO: We should try to handle some sort of extended ASCII. Maybe we could transform
// the return value from `char` to some `wchar_t` or `int` altogether and encode our
// own string class which would allow to use these characters using UNICODE encoding.

# ifdef NOT_ASCII_COMPLIANT
  std::string
# else
  char
# endif
  getCharFromQWERTY(const ::sdl::core::engine::RawKey& key,
                    const ::sdl::core::engine::KeyModifier& mods) noexcept
  {
    using namespace sdl::core::engine;

    // Compute information on the modifiers.
    const bool shift = shiftEnabled(mods);
# ifdef NOT_ASCII_COMPLIANT
    const bool altGr = altEnabled(mods, false, false);
# endif

    // Distinguish based on the input key.
    switch (key) {
# ifdef NOT_ASCII_COMPLIANT
      case RawKey::A:
        return (shift ? (altGr ? "Á" : "A") : (altGr ? "á" : "a"));
      case RawKey::B:
        return (shift ? "B" : "b");
      case RawKey::C:
        return (shift ? (altGr ? "¢" : "C") : (altGr ? "©" : "c"));
      case RawKey::D:
        return (shift ? (altGr ? "Ð" : "D") : (altGr ? "ð" : "d"));
      case RawKey::E:
        return (shift ? (altGr ? "É" : "E") : (altGr ? "é" : "e"));
      case RawKey::F:
        return (shift ? "F" : "f");
      case RawKey::G:
        return (shift ? "G" : "g");
      case RawKey::H:
        return (shift ? "H" : "h");
      case RawKey::I:
        return (shift ? (altGr ? "Í" : "I") : (altGr ? "í" : "i"));
      case RawKey::J:
        return (shift ? "J" : "j");
      case RawKey::K:
        return (shift ? "K" : "k");
      case RawKey::L:
        return (shift ? (altGr ? "Ø" : "L") : (altGr ? "ø" : "l"));
      case RawKey::M:
        return (shift ? "M" : (altGr ? "µ" : "m"));
      case RawKey::N:
        return (shift ? (altGr ? "Ñ" : "N") : (altGr ? "ñ" : "n"));
      case RawKey::O:
        return (shift ? (altGr ? "Ó" : "O") : (altGr ? "ó" : "o"));
      case RawKey::P:
        return (shift ? (altGr ? "Ö" : "P") : (altGr ? "ö" : "p"));
      case RawKey::Q:
        return (shift ? (altGr ? "Ä" : "Q") : (altGr ? "ä" : "q"));
      case RawKey::R:
        return (shift ? "R" : (altGr ? "®" : "r"));
      case RawKey::S:
        return (shift ? (altGr ? "§" : "S") : (altGr ? "ß" : "s"));
      case RawKey::T:
        return (shift ? (altGr ? "Þ" : "T") : (altGr ? "þ" : "t"));
      case RawKey::U:
        return (shift ? (altGr ? "Ú" : "U") : (altGr ? "ú" : "u"));
      case RawKey::V:
        return (shift ? "V" : "v");
      case RawKey::W:
        return (shift ? (altGr ? "Å" : "W") : (altGr ? "å" : "w"));
      case RawKey::X:
        return (shift ? "X" : "x");
      case RawKey::Y:
        return (shift ? (altGr ? "Ü" : "Y") : (altGr ? "ü" : "y"));
      case RawKey::Z:
        return (shift ? (altGr ? "Æ" : "Z") : (altGr ? "æ" : "z"));
      case RawKey::One:
        return (shift ? (altGr ? "¡" : "!") : (altGr ? "¹" : "1"));
      case RawKey::Two:
        return (shift ? "@" : (altGr ? "²" : "2"));
      case RawKey::Three:
        return (shift ? "#" : (altGr ? "³" : "3"));
      case RawKey::Four:
        return (shift ? (altGr ? "£" : "$") : (altGr ? "¤" : "4"));
      case RawKey::Five:
        return (shift ? "%" : (altGr ? "€" : "5"));
      case RawKey::Six:
        return (shift ? "^" : (altGr ? "¼" : "6"));
      case RawKey::Seven:
        return (shift ? "&" : (altGr ? "½" : "7"));
      case RawKey::Eight:
        return (shift ? "*" : (altGr ? "¾" : "8"));
      case RawKey::Nine:
        return (shift ? "(" : (altGr ? "‘" : "9"));
      case RawKey::Zero:
        return (shift ? ")" : (altGr ? "’" : "0"));

      case RawKey::Space:
        return " ";

      case RawKey::Minus:
        return (shift ? "_" : (altGr ? "¥" : "-"));
      case RawKey::Equals:
        return (shift ? (altGr ? "÷" : "+") : (altGr ? "×" : "="));
      case RawKey::LeftBracket:
        return (shift ? "{" : (altGr ? "«" : "["));
      case RawKey::RightBracket:
        return (shift ? "}" : (altGr ? "»" : "]"));
      case RawKey::Backslash:
        return (shift ? (altGr ? "¦" : "|") : (altGr ? "¬" : "\\"));
      case RawKey::Semicolon:
        return (shift ? (altGr ? "°" : ":") : (altGr ? "¶" : ";"));
      case RawKey::Grave:
        return (shift ? "~" : "`");
      case RawKey::Comma:
        return (shift ? (altGr ? "Ç" : "<") : (altGr ? "ç" : ","));
      case RawKey::Period:
        return (shift ? ">" : ".");
      case RawKey::Slash:
        return (shift ? "?" : (altGr ? "¿" : "/"));

      case RawKey::KPDivide:
        return "/";
      case RawKey::KPMultiply:
        return "*";
      case RawKey::KPMinus:
        return "-";
      case RawKey::KPPlus:
        return "+";
      case RawKey::KP1:
        return "1";
      case RawKey::KP2:
        return "2";
      case RawKey::KP3:
        return "3";
      case RawKey::KP4:
        return "4";
      case RawKey::KP5:
        return "5";
      case RawKey::KP6:
        return "6";
      case RawKey::KP7:
        return "7";
      case RawKey::KP8:
        return "8";
      case RawKey::KP9:
        return "9";
      case RawKey::KP0:
        return "0";
      case RawKey::KPPeriod:
        return ".";

      case RawKey::Return:
      case RawKey::Escape:
      case RawKey::BackSpace:
      case RawKey::Tab:

      case RawKey::CapsLock:

      case RawKey::F1:
      case RawKey::F2:
      case RawKey::F3:
      case RawKey::F4:
      case RawKey::F5:
      case RawKey::F6:
      case RawKey::F7:
      case RawKey::F8:
      case RawKey::F9:
      case RawKey::F10:
      case RawKey::F11:
      case RawKey::F12:

      case RawKey::PrintScreen:
      case RawKey::ScrollLock:
      case RawKey::Pause:
      case RawKey::Insert:
      case RawKey::Home:
      case RawKey::PageUp:
      case RawKey::Delete:
      case RawKey::End:
      case RawKey::PageDown:
      case RawKey::Right:
      case RawKey::Left:
      case RawKey::Down:
      case RawKey::Up:

      case RawKey::NumLockClear:

      case RawKey::LeftCtrl:
      case RawKey::LeftShift:
      case RawKey::LeftAlt:
      case RawKey::LeftCommand:
      case RawKey::RightCtrl:
      case RawKey::RightShift:
      case RawKey::RightAlt:
      case RawKey::RightCommand:

      case RawKey::None:
      default:
        return "";
# else
      case RawKey::A:
        return (shift ? 'A' : 'a');
      case RawKey::B:
        return (shift ? 'B' : 'b');
      case RawKey::C:
        return (shift ? 'C' : 'c');
      case RawKey::D:
        return (shift ? 'D' : 'd');
      case RawKey::E:
        return (shift ? 'E' : 'e');
      case RawKey::F:
        return (shift ? 'F' : 'f');
      case RawKey::G:
        return (shift ? 'G' : 'g');
      case RawKey::H:
        return (shift ? 'H' : 'h');
      case RawKey::I:
        return (shift ? 'I' : 'i');
      case RawKey::J:
        return (shift ? 'J' : 'j');
      case RawKey::K:
        return (shift ? 'K' : 'k');
      case RawKey::L:
        return (shift ? 'L' : 'l');
      case RawKey::M:
        return (shift ? 'M' : 'm');
      case RawKey::N:
        return (shift ? 'N' : 'n');
      case RawKey::O:
        return (shift ? 'O' : 'o');
      case RawKey::P:
        return (shift ? 'P' : 'p');
      case RawKey::Q:
        return (shift ? 'Q' : 'q');
      case RawKey::R:
        return (shift ? 'R' : 'r');
      case RawKey::S:
        return (shift ? 'S' : 's');
      case RawKey::T:
        return (shift ? 'T' : 't');
      case RawKey::U:
        return (shift ? 'U' : 'u');
      case RawKey::V:
        return (shift ? 'V' : 'v');
      case RawKey::W:
        return (shift ? 'W' : 'w');
      case RawKey::X:
        return (shift ? 'X' : 'x');
      case RawKey::Y:
        return (shift ? 'Y' : 'y');
      case RawKey::Z:
        return (shift ? 'Z' : 'z');
      case RawKey::One:
        return (shift ? '!' : '1');
      case RawKey::Two:
        return (shift ? '@' : '2');
      case RawKey::Three:
        return (shift ? '#' : '3');
      case RawKey::Four:
        return (shift ? '$' : '4');
      case RawKey::Five:
        return (shift ? '%' : '5');
      case RawKey::Six:
        return (shift ? '^' : '6');
      case RawKey::Seven:
        return (shift ? '&' : '7');
      case RawKey::Eight:
        return (shift ? '*' : '8');
      case RawKey::Nine:
        return (shift ? '(' : '9');
      case RawKey::Zero:
        return (shift ? ')' : '0');

      case RawKey::Space:
        return ' ';

      case RawKey::Minus:
        return (shift ? '_' : '-');
      case RawKey::Equals:
        return (shift ? '+' : '=');
      case RawKey::LeftBracket:
        return (shift ? '{' : '[');
      case RawKey::RightBracket:
        return (shift ? '}' : ']');
      case RawKey::Backslash:
        return (shift ? '|' : '\\');
      case RawKey::Semicolon:
        return (shift ? ':' : ';');
      case RawKey::Grave:
        return (shift ? '~' : '`');
      case RawKey::Comma:
        return (shift ? '<' : ',');
      case RawKey::Period:
        return (shift ? '>' : '.');
      case RawKey::Slash:
        return (shift ? '?' : '/');

      case RawKey::KPDivide:
        return '/';
      case RawKey::KPMultiply:
        return '*';
      case RawKey::KPMinus:
        return '-';
      case RawKey::KPPlus:
        return '+';
      case RawKey::KP1:
        return '1';
      case RawKey::KP2:
        return '2';
      case RawKey::KP3:
        return '3';
      case RawKey::KP4:
        return '4';
      case RawKey::KP5:
        return '5';
      case RawKey::KP6:
        return '6';
      case RawKey::KP7:
        return '7';
      case RawKey::KP8:
        return '8';
      case RawKey::KP9:
        return '9';
      case RawKey::KP0:
        return '0';
      case RawKey::KPPeriod:
        return '.';

      case RawKey::Return:
      case RawKey::Escape:
      case RawKey::BackSpace:
      case RawKey::Tab:

      case RawKey::CapsLock:

      case RawKey::F1:
      case RawKey::F2:
      case RawKey::F3:
      case RawKey::F4:
      case RawKey::F5:
      case RawKey::F6:
      case RawKey::F7:
      case RawKey::F8:
      case RawKey::F9:
      case RawKey::F10:
      case RawKey::F11:
      case RawKey::F12:

      case RawKey::PrintScreen:
      case RawKey::ScrollLock:
      case RawKey::Pause:
      case RawKey::Insert:
      case RawKey::Home:
      case RawKey::PageUp:
      case RawKey::Delete:
      case RawKey::End:
      case RawKey::PageDown:
      case RawKey::Right:
      case RawKey::Left:
      case RawKey::Down:
      case RawKey::Up:

      case RawKey::NumLockClear:

      case RawKey::LeftCtrl:
      case RawKey::LeftShift:
      case RawKey::LeftAlt:
      case RawKey::LeftCommand:
      case RawKey::RightCtrl:
      case RawKey::RightShift:
      case RawKey::RightAlt:
      case RawKey::RightCommand:

      case RawKey::None:
      default:
        return '\0';
# endif
    }
  }

# ifdef NOT_ASCII_COMPLIANT
  std::string
# else
  char
# endif
  getCharFromAZERTY(const ::sdl::core::engine::RawKey& key,
                    const ::sdl::core::engine::KeyModifier& mods) noexcept
  {
    using namespace sdl::core::engine;

    // Compute information on the modifiers.
    const bool shift = shiftEnabled(mods);
    const bool altGr = altEnabled(mods, false, false);

    // Distinguish based on the input key.
    switch (key) {
# ifdef NOT_ASCII_COMPLIANT
      case RawKey::A:
        return (shift ? (altGr ? "Ä" : "Q") : (altGr ? "ä" : "q"));
      case RawKey::B:
        return (shift ? (altGr ? "↑" : "B") : (altGr ? "↓" : "b"));
      case RawKey::C:
        return (shift ? (altGr ? "®" : "C") : (altGr ? "©" : "c"));
      case RawKey::D:
        return (shift ? (altGr ? "Ë" : "D") : (altGr ? "ë" : "d"));
      case RawKey::E:
        return (shift ? (altGr ? "¢" : "E") : (altGr ? "€" : "e"));
      case RawKey::F:
        return (shift ? (altGr ? "," : "F") : (altGr ? "‘" : "f"));
      case RawKey::G:
        return (shift ? (altGr ? "¥" : "G") : (altGr ? "’" : "g"));
      case RawKey::H:
        return (shift ? (altGr ? "Ð" : "H") : (altGr ? "ð" : "h"));
      case RawKey::I:
        return (shift ? (altGr ? "Î" : "I") : (altGr ? "î" : "i"));
      case RawKey::J:
        return (shift ? (altGr ? "Ü" : "J") : (altGr ? "ü" : "j"));
      case RawKey::K:
        return (shift ? (altGr ? "Ï" : "K") : (altGr ? "ï" : "k"));
      case RawKey::L:
        return (shift ? (altGr ? "Ł" : "L") : (altGr ? "ł" : "l"));
      case RawKey::M:
        return (shift ? (altGr ? "…" : "?") : (altGr ? "¿" : ","));
      case RawKey::N:
        return (shift ? (altGr ? "➔" : "N") : (altGr ? "¬" : "n"));
      case RawKey::O:
        return (shift ? (altGr ? "Œ" : "O") : (altGr ? "œ" : "o"));
      case RawKey::P:
        return (shift ? (altGr ? "Ô" : "P") : (altGr ? "ô" : "p"));
      case RawKey::Q:
        return (shift ? (altGr ? "Æ" : "A") : (altGr ? "æ" : "a"));
      case RawKey::R:
        return (shift ? (altGr ? "Ê" : "R") : (altGr ? "ê" : "r"));
      case RawKey::S:
        return (shift ? (altGr ? "„" : "S") : (altGr ? "ß" : "s"));
      case RawKey::T:
        return (shift ? (altGr ? "Þ" : "T") : (altGr ? "þ" : "t"));
      case RawKey::U:
        return (shift ? (altGr ? "Û" : "U") : (altGr ? "û" : "u"));
      case RawKey::V:
        return (shift ? (altGr ? "←" : "V") : (altGr ? " " : "v"));
      case RawKey::W:
        return (shift ? (altGr ? "Â" : "Z") : (altGr ? "â" : "z"));
      case RawKey::X:
        return (shift ? (altGr ? "”" : "X") : (altGr ? "»" : "x"));
      case RawKey::Y:
        return (shift ? (altGr ? "Ÿ" : "Y") : (altGr ? "ÿ" : "y"));
      case RawKey::Z:
        return (shift ? (altGr ? "‟" : "W") : (altGr ? "«" : "w"));
      case RawKey::One:
        return (shift ? "1" : "&");
      case RawKey::Two:
        return (shift ? (altGr ? "É" : "2") : (altGr ? "~" : "é"));
      case RawKey::Three:
        return (shift ? "3" : (altGr ? "#" : "\""));
      case RawKey::Four:
        return (shift ? (altGr ? "―" : "4") : (altGr ? "{" : "'"));
      case RawKey::Five:
        return (shift ? (altGr ? "–" : "5") : (altGr ? "[" : "("));
      case RawKey::Six:
        return (shift ? (altGr ? "‑" : "6") : (altGr ? "|" : "-"));
      case RawKey::Seven:
        return (shift ? (altGr ? "È" : "7") : (altGr ? "`" : "è"));
      case RawKey::Eight:
        return (shift ? (altGr ? "™" : "8") : (altGr ? "\\" : "_"));
      case RawKey::Nine:
        return (shift ? (altGr ? "Ç" : "9") : (altGr ? "^" : "ç"));
      case RawKey::Zero:
        return (shift ? (altGr ? "À" : "0") : (altGr ? "@" : "à"));

      case RawKey::Space:
        return " ";

      case RawKey::Minus:
        return (shift ? (altGr ? "≠" : "°") : (altGr ? "]" : ")"));
      case RawKey::Equals:
        return (shift ? (altGr ? "±" : "+") : (altGr ? "}" : "="));
      case RawKey::RightBracket:
        return (shift ? (altGr ? "Ø" : "£") : (altGr ? "ø" : "$"));
      case RawKey::Backslash:
        return (shift ? "µ" : "*");
      case RawKey::Semicolon:
        return (shift ? (altGr ? "Ö" : "M") : (altGr ? "ö" : "m"));
      case RawKey::Grave:
        return (shift ? (altGr ? "³" : "~") : (altGr ? "¹" : "²"));
      case RawKey::Comma:
        return (shift ? (altGr ? "·" : ".") : (altGr ? "×" : ";"));
      case RawKey::Period:
        return (shift ? (altGr ? "／" : "/") : (altGr ? "÷" : ":"));
      case RawKey::Slash:
        return (shift ? (altGr ? "–" : "§") : (altGr ? "¡" : "!"));

      case RawKey::KPDivide:
        return "/";
      case RawKey::KPMultiply:
        return "*";
      case RawKey::KPMinus:
        return "-";
      case RawKey::KPPlus:
        return "+";
      case RawKey::KP1:
        return "1";
      case RawKey::KP2:
        return "2";
      case RawKey::KP3:
        return "3";
      case RawKey::KP4:
        return "4";
      case RawKey::KP5:
        return "5";
      case RawKey::KP6:
        return "6";
      case RawKey::KP7:
        return "7";
      case RawKey::KP8:
        return "8";
      case RawKey::KP9:
        return "9";
      case RawKey::KP0:
        return "0";
      case RawKey::KPPeriod:
        return ".";

      case RawKey::Return:
      case RawKey::Escape:
      case RawKey::BackSpace:
      case RawKey::Tab:

      case RawKey::LeftBracket:
      case RawKey::CapsLock:

      case RawKey::F1:
      case RawKey::F2:
      case RawKey::F3:
      case RawKey::F4:
      case RawKey::F5:
      case RawKey::F6:
      case RawKey::F7:
      case RawKey::F8:
      case RawKey::F9:
      case RawKey::F10:
      case RawKey::F11:
      case RawKey::F12:

      case RawKey::PrintScreen:
      case RawKey::ScrollLock:
      case RawKey::Pause:
      case RawKey::Insert:
      case RawKey::Home:
      case RawKey::PageUp:
      case RawKey::Delete:
      case RawKey::End:
      case RawKey::PageDown:
      case RawKey::Right:
      case RawKey::Left:
      case RawKey::Down:
      case RawKey::Up:

      case RawKey::NumLockClear:

      case RawKey::LeftCtrl:
      case RawKey::LeftShift:
      case RawKey::LeftAlt:
      case RawKey::LeftCommand:
      case RawKey::RightCtrl:
      case RawKey::RightShift:
      case RawKey::RightAlt:
      case RawKey::RightCommand:

      case RawKey::None:
      default:
        return "";
# else
      case RawKey::A:
        return (shift ? 'Q' : 'q');
      case RawKey::B:
        return (shift ? 'B' : 'b');
      case RawKey::C:
        return (shift ? 'C' : 'c');
      case RawKey::D:
        return (shift ? 'D' : 'd');
      case RawKey::E:
        return (shift ? 'E' : 'e');
      case RawKey::F:
        return (shift ? 'F' : 'f');
      case RawKey::G:
        return (shift ? 'G' : 'g');
      case RawKey::H:
        return (shift ? 'H' : 'h');
      case RawKey::I:
        return (shift ? 'I' : 'i');
      case RawKey::J:
        return (shift ? 'J' : 'j');
      case RawKey::K:
        return (shift ? 'K' : 'k');
      case RawKey::L:
        return (shift ? 'L' : 'l');
      case RawKey::M:
        return (shift ? '?' : ',');
      case RawKey::N:
        return (shift ? 'N' : 'n');
      case RawKey::O:
        return (shift ? 'O' : 'o');
      case RawKey::P:
        return (shift ? 'P' : 'p');
      case RawKey::Q:
        return (shift ? 'A' : 'a');
      case RawKey::R:
        return (shift ? 'R' : 'r');
      case RawKey::S:
        return (shift ? 'S' : 's');
      case RawKey::T:
        return (shift ? 'T' : 't');
      case RawKey::U:
        return (shift ? 'U' : 'u');
      case RawKey::V:
        return (shift ? 'V' : 'v');
      case RawKey::W:
        return (shift ? 'Z' : 'z');
      case RawKey::X:
        return (shift ? 'X' : 'x');
      case RawKey::Y:
        return (shift ? 'Y' : 'y');
      case RawKey::Z:
        return (shift ? 'W' : 'w');
      case RawKey::One:
        return (shift ? '1' : '&');
      case RawKey::Two:
        return (shift ? '2' : (altGr ? '~' : 'e'));
      case RawKey::Three:
        return (shift ? '3' : (altGr ? '#' : '\"'));
      case RawKey::Four:
        return (shift ? '4' : (altGr ? '{' : '\''));
      case RawKey::Five:
        return (shift ? '5' : (altGr ? '[' : '('));
      case RawKey::Six:
        return (shift ? (altGr ? '-' : '6') : (altGr ? '|' : '-'));
      case RawKey::Seven:
        return (shift ? (altGr ? 'E' : '7') : (altGr ? '`' : 'e'));
      case RawKey::Eight:
        return (shift ? '8' : (altGr ? '\\' : '_'));
      case RawKey::Nine:
        return (shift ? (altGr ? 'C' : '9') : (altGr ? '^' : 'c'));
      case RawKey::Zero:
        return (shift ? (altGr ? 'A' : '0') : (altGr ? '@' : 'a'));

      case RawKey::Space:
        return ' ';

      case RawKey::Minus:
        return (altGr ? ']' : ')');
      case RawKey::Equals:
        return (shift ? '+' : (altGr ? '}' : '='));
      case RawKey::LeftBracket:
        return '^';
      case RawKey::RightBracket:
        return '$';
      case RawKey::Backslash:
        return '*';
      case RawKey::Semicolon:
        return (shift ? (altGr ? 'O' : 'M') : (altGr ? 'o' : 'm'));
      case RawKey::Grave:
        return '~';
      case RawKey::Comma:
        return (shift ? '.' : ';');
      case RawKey::Period:
        return (shift ? '/' : ':');
      case RawKey::Slash:
        return '!';

      case RawKey::KPDivide:
        return '/';
      case RawKey::KPMultiply:
        return '*';
      case RawKey::KPMinus:
        return '-';
      case RawKey::KPPlus:
        return '+';
      case RawKey::KP1:
        return '1';
      case RawKey::KP2:
        return '2';
      case RawKey::KP3:
        return '3';
      case RawKey::KP4:
        return '4';
      case RawKey::KP5:
        return '5';
      case RawKey::KP6:
        return '6';
      case RawKey::KP7:
        return '7';
      case RawKey::KP8:
        return '8';
      case RawKey::KP9:
        return '9';
      case RawKey::KP0:
        return '0';
      case RawKey::KPPeriod:
        return '.';

      case RawKey::Return:
      case RawKey::Escape:
      case RawKey::BackSpace:
      case RawKey::Tab:

      case RawKey::CapsLock:

      case RawKey::F1:
      case RawKey::F2:
      case RawKey::F3:
      case RawKey::F4:
      case RawKey::F5:
      case RawKey::F6:
      case RawKey::F7:
      case RawKey::F8:
      case RawKey::F9:
      case RawKey::F10:
      case RawKey::F11:
      case RawKey::F12:

      case RawKey::PrintScreen:
      case RawKey::ScrollLock:
      case RawKey::Pause:
      case RawKey::Insert:
      case RawKey::Home:
      case RawKey::PageUp:
      case RawKey::Delete:
      case RawKey::End:
      case RawKey::PageDown:
      case RawKey::Right:
      case RawKey::Left:
      case RawKey::Down:
      case RawKey::Up:

      case RawKey::NumLockClear:

      case RawKey::LeftCtrl:
      case RawKey::LeftShift:
      case RawKey::LeftAlt:
      case RawKey::LeftCommand:
      case RawKey::RightCtrl:
      case RawKey::RightShift:
      case RawKey::RightAlt:
      case RawKey::RightCommand:

      case RawKey::None:
      default:
        return '\0';
# endif
    }
  }

}

namespace sdl {
  namespace core {
    namespace engine {

      bool
      isKeyAlphanumeric(const RawKey& key,
                        const KeyModifier& mods,
                        const keyboard::Mode& mode) noexcept
      {
        switch (mode) {
          case keyboard::Mode::Azerty:
            return isAZERTYKeyAlphanumeric(key, mods);
          case keyboard::Mode::Qwerty:
          default:
            return isQWERTYKeyAlphanumeric(key, mods);
        }
      }

      bool
      isKeyPrintable(const RawKey& key,
                     const KeyModifier& mods,
                     const keyboard::Mode& mode) noexcept
      {
        switch (mode) {
          case keyboard::Mode::Azerty:
            return isAZERTYKeyPrintable(key, mods);
          case keyboard::Mode::Qwerty:
          default:
            return isQWERTYKeyPrintable(key, mods);
        }
      }

# ifdef NOT_ASCII_COMPLIANT
      std::string
# else
      char
# endif
      getCharFromKey(const RawKey& key,
                     const KeyModifier& mods,
                     const keyboard::Mode& mode) noexcept
      {
        switch (mode) {
          case keyboard::Mode::Azerty:
            return getCharFromAZERTY(key, mods);
          case keyboard::Mode::Qwerty:
          default:
            return getCharFromQWERTY(key, mods);
        }
      }

    }
  }
}
