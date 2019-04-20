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
      void
      KeyEvent::init() {
        // Check whether the event has a right type.
        if (m_key.type != SDL_KEYDOWN && m_key.type != SDL_KEYUP) {
          error(std::string("Cannot create key event from invalid type ") + std::to_string(static_cast<int>(m_key.type)));
        }

        Event::Type type = Event::Type::KeyPress;
        if (m_key.type == SDL_KEYUP) {
          type = Event::Type::KeyRelease;
        }

        setType(type);
      }

    }
  }
}

#endif    /* KEY_EVENT_HH */
