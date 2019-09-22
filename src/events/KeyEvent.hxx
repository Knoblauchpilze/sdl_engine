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

        m_converted(Key::None),
        m_mods()
      {
        init();
      }

      inline
      KeyEvent::~KeyEvent() {}

      inline
      Key
      KeyEvent::getKey() const noexcept {
        return m_converted;
      }

      inline
      KeyModifier
      KeyEvent::getModifiers() const noexcept {
        return m_mods;
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
      KeyEvent::isEscape() const noexcept {
        return getKey() == Key::Escape;
      }

      inline
      bool
      KeyEvent::isAlphaNumeric() const noexcept {
        return engine::isKeyAlphanumeric(getKey());
        ;
      }

      inline
      char
      KeyEvent::getChar() const {
        // Check whether the key is alpha numeric: if this is not the case we can't really
        // provide an equivalent char.
        if (!isAlphaNumeric()) {
          error(
            std::string("Cannot return equivalent char to key"),
            std::string("Key is not alphanumeric")
          );
        }

        // Use the dedicated handler.
        return getCharFromKey(getKey(), getModifiers());
      }

      inline
      bool
      KeyEvent::equal(const Event& other) const noexcept {
        const KeyEvent& e = dynamic_cast<const KeyEvent&>(other);
        return Event::equal(other) && getKey() == e.getKey() && getModifiers() == e.getModifiers();
      }

    }
  }
}

#endif    /* KEY_EVENT_HH */
