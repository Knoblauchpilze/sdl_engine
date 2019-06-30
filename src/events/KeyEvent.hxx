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
        m_key(event)
      {
        init();
      }

      inline
      KeyEvent::~KeyEvent() {}

      inline
      int
      KeyEvent::getKey() const noexcept {
        return m_key.keysym.sym;
      }

      inline
      bool
      KeyEvent::isPress() const noexcept {
        return getType() == Event::Type::KeyPress;
      }

      inline
      bool
      KeyEvent::isRelease() const noexcept {
        return getType() == Event::Type::KeyRelease;
      }

      inline
      bool
      KeyEvent::isEscape() const noexcept {
        return getKey() == SDLK_ESCAPE;
      }

      inline
      bool
      KeyEvent::equal(const Event& other) const noexcept {
        const KeyEvent& e = dynamic_cast<const KeyEvent&>(other);
        return Event::equal(other) && getKey() == e.getKey();
      }

    }
  }
}

#endif    /* KEY_EVENT_HH */
