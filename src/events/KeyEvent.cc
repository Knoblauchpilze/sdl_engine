
# include "KeyEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      KeyEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      KeyEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const KeyEvent& usable = dynamic_cast<const KeyEvent&>(other);

        // Equalize internal fields.
        m_key = usable.m_key;

        // Return the base handler's prescriptions.
        return canMerge;
      }

      void
      KeyEvent::init() {
        // Check whether the event has a right type.
        if (m_key.type != SDL_KEYDOWN && m_key.type != SDL_KEYUP) {
          error(
            std::string("Cannot create key event"),
            std::string("Key event has invalid type ") + std::to_string(static_cast<int>(m_key.type))
          );
        }

        // The type of the event is determined from the undelrying `API` event.
        Event::Type type = Event::Type::KeyPress;
        if (m_key.type == SDL_KEYUP) {
          type = Event::Type::KeyRelease;
        }

        // Determine the layout of the keyboard.
        guessKeyboardLayout();

        // Build both the raw and converted key values.
        m_raw = fromSDLScancode(m_key.keysym.scancode);
        m_interpreted = fromRawKey(m_raw, getKeyboardLayout());

        // Retrieve the key modifiers.
        m_mods = fromSDLMod(m_key.keysym.mod);

        log(
          std::string("Pressed ") +
          "key " + std::to_string(m_key.keysym.sym) + " " +
          "(scan: " + std::to_string(m_key.keysym.scancode) + ", name: \"" + SDL_GetKeyName(m_key.keysym.sym) + "\") " +
          "converted to " + std::to_string(static_cast<int>(m_raw)) + " "
          "interpreted in " + std::to_string(static_cast<int>(m_interpreted)) +
          " (mode: " + keyboard::toString(getKeyboardLayout()) + ")"
        );

        setType(type);

        setSDLWinID(m_key.windowID);
      }

      Key
      KeyEvent::fromRawKey(const RawKey& key,
                           const keyboard::Mode& mode) const noexcept
      {
        switch (mode) {
          case keyboard::Mode::Azerty:
            return fromRawToAZERTY(key);
          case keyboard::Mode::Qwerty:
            return fromRawToQWERTY(key);
          default:
            break;
        }

        // Could not interpret the mode, assume `QWERTY` mode.
        log(
          std::string("Could not interpret raw key ") + std::to_string(static_cast<int>(key)) +
          " using keyboard mode " + std::to_string(static_cast<int>(mode)) +
          " assuming 'QWERTY'",
          utils::Level::Warning
        );

        return fromRawToQWERTY(key);
      }

      Key
      KeyEvent::fromRawToQWERTY(const RawKey& key) const noexcept {
        // The `QWERTY` mode corresponds to the physical position of keys so
        // there's no real conversion happening, just a transform of the raw
        // key into the corresponding interpretated enumeration value.
        switch (key) {
          case RawKey::A:
            return Key::A;
          case RawKey::B:
            return Key::B;
          case RawKey::C:
            return Key::C;
          case RawKey::D:
            return Key::D;
          case RawKey::E:
            return Key::E;
          case RawKey::F:
            return Key::F;
          case RawKey::G:
            return Key::G;
          case RawKey::H:
            return Key::H;
          case RawKey::I:
            return Key::I;
          case RawKey::J:
            return Key::J;
          case RawKey::K:
            return Key::K;
          case RawKey::L:
            return Key::L;
          case RawKey::M:
            return Key::M;
          case RawKey::N:
            return Key::N;
          case RawKey::O:
            return Key::O;
          case RawKey::P:
            return Key::P;
          case RawKey::Q:
            return Key::Q;
          case RawKey::R:
            return Key::R;
          case RawKey::S:
            return Key::S;
          case RawKey::T:
            return Key::T;
          case RawKey::U:
            return Key::U;
          case RawKey::V:
            return Key::V;
          case RawKey::W:
            return Key::W;
          case RawKey::X:
            return Key::X;
          case RawKey::Y:
            return Key::Y;
          case RawKey::Z:
            return Key::Z;
          case RawKey::One:
            return Key::One;
          case RawKey::Two:
            return Key::Two;
          case RawKey::Three:
            return Key::Three;
          case RawKey::Four:
            return Key::Four;
          case RawKey::Five:
            return Key::Five;
          case RawKey::Six:
            return Key::Six;
          case RawKey::Seven:
            return Key::Seven;
          case RawKey::Eight:
            return Key::Eight;
          case RawKey::Nine:
            return Key::Nine;
          case RawKey::Zero:
            return Key::Zero;

          case RawKey::Return:
            return Key::Return;
          case RawKey::Escape:
            return Key::Escape;
          case RawKey::BackSpace:
            return Key::Backspace;
          case RawKey::Tab:
            return Key::Tab;
          case RawKey::Space:
            return Key::Space;

          case RawKey::Minus:
            return Key::Minus;
          case RawKey::Equals:
            return Key::Equals;
          case RawKey::LeftBracket:
            return Key::LeftBracket;
          case RawKey::RightBracket:
            return Key::RightBracket;
          case RawKey::Backslash:
            return Key::Backslash;
          /* SDL_SCANCODE_NONUSHASH */
          case RawKey::Semicolon:
            return Key::Semicolon;
          /* SDL_SCANCODE_APOSTROPHE */
          case RawKey::Grave:
            return Key::Backquote;
          case RawKey::Comma:
            return Key::Comma;
          case RawKey::Period:
            return Key::Period;
          case RawKey::Slash:
            return Key::Slash;
          case RawKey::CapsLock:
            return Key::CapsLock;

          case RawKey::F1:
            return Key::F1;
          case RawKey::F2:
            return Key::F2;
          case RawKey::F3:
            return Key::F3;
          case RawKey::F4:
            return Key::F4;
          case RawKey::F5:
            return Key::F5;
          case RawKey::F6:
            return Key::F6;
          case RawKey::F7:
            return Key::F7;
          case RawKey::F8:
            return Key::F8;
          case RawKey::F9:
            return Key::F9;
          case RawKey::F10:
            return Key::F10;
          case RawKey::F11:
            return Key::F11;
          case RawKey::F12:
            return Key::F12;

          case RawKey::PrintScreen:
            return Key::PrintScreen;
          case RawKey::ScrollLock:
            return Key::ScrollLock;
          case RawKey::Pause:
            return Key::Pause;
          case RawKey::Insert:
            return Key::Insert;
          case RawKey::Home:
            return Key::Home;
          case RawKey::PageUp:
            return Key::PageUp;
          case RawKey::Delete:
            return Key::Delete;
          case RawKey::End:
            return Key::End;
          case RawKey::PageDown:
            return Key::PageDown;
          case RawKey::Right:
            return Key::Right;
          case RawKey::Left:
            return Key::Left;
          case RawKey::Down:
            return Key::Down;
          case RawKey::Up:
            return Key::Up;

          case RawKey::NumLockClear:
            return Key::NumLockClear;
          case RawKey::KPDivide:
            return Key::KPDivide;
          case RawKey::KPMultiply:
            return Key::KPMultiply;
          case RawKey::KPMinus:
            return Key::KPMinus;
          case RawKey::KPPlus:
            return Key::KPPlus;
          case RawKey::KPEnter:
            return Key::KPEnter;
          case RawKey::KP1:
            return Key::KP1;
          case RawKey::KP2:
            return Key::KP2;
          case RawKey::KP3:
            return Key::KP3;
          case RawKey::KP4:
            return Key::KP4;
          case RawKey::KP5:
            return Key::KP5;
          case RawKey::KP6:
            return Key::KP6;
          case RawKey::KP7:
            return Key::KP7;
          case RawKey::KP8:
            return Key::KP8;
          case RawKey::KP9:
            return Key::KP9;
          case RawKey::KP0:
            return Key::KP0;
          case RawKey::KPPeriod:
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

          case RawKey::LeftCtrl:
            return Key::LeftCtrl;
          case RawKey::LeftShift:
            return Key::LeftShift;
          case RawKey::LeftAlt:
            return Key::LeftAlt;
          case RawKey::LeftCommand:
            return Key::LeftCommand;
          case RawKey::RightCtrl:
            return Key::RightCtrl;
          case RawKey::RightShift:
            return Key::RightShift;
          case RawKey::RightAlt:
            return Key::RightAlt;
          case RawKey::RightCommand:
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

          case RawKey::None:
          default:
            break;
        }

        // Could not interpret the key, return `None`.
        log(
          std::string("Could not interpret raw key ") + std::to_string(static_cast<int>(key)) +
          " in `QWERTY` mode",
          utils::Level::Warning
        );

        return Key::None;
      }

      Key
      KeyEvent::fromRawToAZERTY(const RawKey& key) const noexcept {
        // The `AZERTY` mode notably inverts the `Q` with the `A` and the
        // `W` with the `Z` keys among others.
        switch (key) {
          case RawKey::A:
            return Key::Q;
          case RawKey::B:
            return Key::B;
          case RawKey::C:
            return Key::C;
          case RawKey::D:
            return Key::D;
          case RawKey::E:
            return Key::E;
          case RawKey::F:
            return Key::F;
          case RawKey::G:
            return Key::G;
          case RawKey::H:
            return Key::H;
          case RawKey::I:
            return Key::I;
          case RawKey::J:
            return Key::J;
          case RawKey::K:
            return Key::K;
          case RawKey::L:
            return Key::L;
          case RawKey::M:
            return Key::Comma;
          case RawKey::N:
            return Key::N;
          case RawKey::O:
            return Key::O;
          case RawKey::P:
            return Key::P;
          case RawKey::Q:
            return Key::A;
          case RawKey::R:
            return Key::R;
          case RawKey::S:
            return Key::S;
          case RawKey::T:
            return Key::T;
          case RawKey::U:
            return Key::U;
          case RawKey::V:
            return Key::V;
          case RawKey::W:
            return Key::Z;
          case RawKey::X:
            return Key::X;
          case RawKey::Y:
            return Key::Y;
          case RawKey::Z:
            return Key::W;
          case RawKey::One:
            return Key::Ampersand;
          case RawKey::Two:
            // TODO: Should produce `é`.
            return Key::Two;
          case RawKey::Three:
            return Key::DoubleQuote;
          case RawKey::Four:
            return Key::Quote;
          case RawKey::Five:
            return Key::LeftParenthesis;
          case RawKey::Six:
            return Key::Minus;
          case RawKey::Seven:
            // TODO: Should produce `è`.
            return Key::Seven;
          case RawKey::Eight:
            return Key::Underscore;
          case RawKey::Nine:
            // TODO: Should produce `ç`.
            return Key::Nine;
          case RawKey::Zero:
            // TODO: Should produce `à`.
            return Key::Zero;

          case RawKey::Return:
            return Key::Return;
          case RawKey::Escape:
            return Key::Escape;
          case RawKey::BackSpace:
            return Key::Backspace;
          case RawKey::Tab:
            return Key::Tab;
          case RawKey::Space:
            return Key::Space;

          case RawKey::Minus:
            return Key::RightParenthesis;
          case RawKey::Equals:
            return Key::Equals;
          case RawKey::LeftBracket:
            // TODO: Should produce `trema` and `^`.
            return Key::Caret;
          case RawKey::RightBracket:
            return Key::Dollar;
          case RawKey::Backslash:
            return Key::Asterisk;
          /* SDL_SCANCODE_NONUSHASH */
          case RawKey::Semicolon:
            return Key::M;
          /* SDL_SCANCODE_APOSTROPHE */
          case RawKey::Grave:
            // TODO: Should produce a `²` and `~`
            return Key::None;
          case RawKey::Comma:
            return Key::Semicolon;
          case RawKey::Period:
            return Key::Colon;
          case RawKey::Slash:
            return Key::Exclaim;
          case RawKey::CapsLock:
            return Key::CapsLock;

          case RawKey::F1:
            return Key::F1;
          case RawKey::F2:
            return Key::F2;
          case RawKey::F3:
            return Key::F3;
          case RawKey::F4:
            return Key::F4;
          case RawKey::F5:
            return Key::F5;
          case RawKey::F6:
            return Key::F6;
          case RawKey::F7:
            return Key::F7;
          case RawKey::F8:
            return Key::F8;
          case RawKey::F9:
            return Key::F9;
          case RawKey::F10:
            return Key::F10;
          case RawKey::F11:
            return Key::F11;
          case RawKey::F12:
            return Key::F12;

          case RawKey::PrintScreen:
            return Key::PrintScreen;
          case RawKey::ScrollLock:
            return Key::ScrollLock;
          case RawKey::Pause:
            return Key::Pause;
          case RawKey::Insert:
            return Key::Insert;
          case RawKey::Home:
            return Key::Home;
          case RawKey::PageUp:
            return Key::PageUp;
          case RawKey::Delete:
            return Key::Delete;
          case RawKey::End:
            return Key::End;
          case RawKey::PageDown:
            return Key::PageDown;
          case RawKey::Right:
            return Key::Right;
          case RawKey::Left:
            return Key::Left;
          case RawKey::Down:
            return Key::Down;
          case RawKey::Up:
            return Key::Up;

          case RawKey::NumLockClear:
            return Key::NumLockClear;
          case RawKey::KPDivide:
            return Key::KPDivide;
          case RawKey::KPMultiply:
            return Key::KPMultiply;
          case RawKey::KPMinus:
            return Key::KPMinus;
          case RawKey::KPPlus:
            return Key::KPPlus;
          case RawKey::KPEnter:
            return Key::KPEnter;
          case RawKey::KP1:
            return Key::KP1;
          case RawKey::KP2:
            return Key::KP2;
          case RawKey::KP3:
            return Key::KP3;
          case RawKey::KP4:
            return Key::KP4;
          case RawKey::KP5:
            return Key::KP5;
          case RawKey::KP6:
            return Key::KP6;
          case RawKey::KP7:
            return Key::KP7;
          case RawKey::KP8:
            return Key::KP8;
          case RawKey::KP9:
            return Key::KP9;
          case RawKey::KP0:
            return Key::KP0;
          case RawKey::KPPeriod:
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

          case RawKey::LeftCtrl:
            return Key::LeftCtrl;
          case RawKey::LeftShift:
            return Key::LeftShift;
          case RawKey::LeftAlt:
            return Key::LeftAlt;
          case RawKey::LeftCommand:
            return Key::LeftCommand;
          case RawKey::RightCtrl:
            return Key::RightCtrl;
          case RawKey::RightShift:
            return Key::RightShift;
          case RawKey::RightAlt:
            return Key::RightAlt;
          case RawKey::RightCommand:
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

          case RawKey::None:
          default:
            break;
        }

        // Could not interpret the key, return `None`.
        log(
          std::string("Could not interpret raw key ") + std::to_string(static_cast<int>(key)) +
          " in `AZERTY` mode",
          utils::Level::Warning
        );

        return Key::None;
      }

    }
  }
}
