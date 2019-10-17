#ifndef    KEY_EVENT_HXX
# define   KEY_EVENT_HXX

# include "KeyEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      KeyEvent::KeyEvent(const SDL_KeyboardEvent& event):
        Event(Event::Type::None, nullptr, std::string("key_event_") + std::to_string(event.keysym.sym)),
        m_key(event),

        m_raw(RawKey::None),

        m_mods(),

        m_keyboardLayout(keyboard::Mode::Qwerty)
      {
        init();
      }

      inline
      KeyEvent::~KeyEvent() {}

      inline
      RawKey
      KeyEvent::getRawKey() const noexcept {
        return m_raw;
      }

      inline
      KeyModifier
      KeyEvent::getModifiers() const noexcept {
        return m_mods;
      }

      inline
      const keyboard::Mode&
      KeyEvent::getKeyboardLayout() const noexcept {
        return m_keyboardLayout;
      }

      inline
      bool
      KeyEvent::isPress() const noexcept {
        return getType() == Event::Type::KeyPress;
      }

      inline
      bool
      KeyEvent::isRepeat() const noexcept {
        return (m_key.repeat != 0u);
      }

      inline
      bool
      KeyEvent::isRelease() const noexcept {
        return getType() == Event::Type::KeyRelease;
      }

      inline
      bool
      KeyEvent::isAlphaNumeric() const noexcept {
        return isKeyAlphanumeric(getRawKey(), getModifiers(), getKeyboardLayout());
      }

      inline
      bool
      KeyEvent::isPrintable() const noexcept {
        return isKeyPrintable(getRawKey(), getModifiers(), getKeyboardLayout());
      }

      inline
      char
      KeyEvent::getChar() const {
        // Check whether the key is alpha numeric: if this is not the case we can't really
        // provide an equivalent char.
        if (!isPrintable()) {
          error(
            std::string("Cannot return equivalent char to key '") + std::to_string(static_cast<int>(getRawKey())) + "'",
            std::string("Key is not printable")
          );
        }

        // Use the dedicated handler.
        return getCharFromKey(getRawKey(), getModifiers(), getKeyboardLayout());
      }

      inline
      bool
      KeyEvent::equal(const Event& other) const noexcept {
        const KeyEvent& e = dynamic_cast<const KeyEvent&>(other);
        return
          Event::equal(other) &&
          getRawKey() == e.getRawKey() &&
          getModifiers() == e.getModifiers() &&
          getKeyboardLayout() == e.getKeyboardLayout()
        ;
      }

      inline
      void
      KeyEvent::guessKeyboardLayout() noexcept {
        // Use the dedicated handler.
        m_keyboardLayout = keyboard::guessLayout();
      }

    }
  }
}

#endif    /* KEY_EVENT_HH */
