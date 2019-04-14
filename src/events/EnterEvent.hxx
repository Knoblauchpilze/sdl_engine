#ifndef    ENTER_EVENT_HXX
# define   ENTER_EVENT_HXX

# include "EnterEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EnterEvent::EnterEvent(const SDL_MouseMotionEvent& event):
        Event(Event::Type::None, std::string("enter_event_") + std::to_string(event.x) + "x" + std::to_string(event.y)),
        m_motion(event)
      {
        init();
      }

      inline
      EnterEvent::~EnterEvent() {}

      inline
      utils::Vector2f
      EnterEvent::getMousePosition() const noexcept {
        return utils::Vector2f(m_motion.x, m_motion.y);
      }

      inline
      void
      EnterEvent::init() {
        // Check whether the event has a right type.
        if (m_motion.type != SDL_MOUSEMOTION) {
          error(std::string("Cannot create enter event from invalid type ") + std::to_string(static_cast<int>(m_motion.type)));
        }

        setType(Event::Type::Enter);
      }

    }
  }
}

#endif    /* ENTER_EVENT_HXX */
