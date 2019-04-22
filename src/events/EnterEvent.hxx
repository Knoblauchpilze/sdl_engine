#ifndef    ENTER_EVENT_HXX
# define   ENTER_EVENT_HXX

# include "EnterEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EnterEvent::EnterEvent(const utils::Vector2f& coordinates,
                             EngineObject* receiver):
        Event(Event::Type::Enter,
              receiver,
              std::string("enter_event_") + coordinates.toString()),
        m_coordinates(coordinates)
      {}

      inline
      EnterEvent::~EnterEvent() {}

      inline
      const utils::Vector2f&
      EnterEvent::getMousePosition() const noexcept {
        return m_coordinates;
      }

      inline
      bool
      EnterEvent::equal(const Event& other) const noexcept {
        const EnterEvent& e = dynamic_cast<const EnterEvent&>(other);
        return Event::equal(other) && getMousePosition() == e.getMousePosition();
      }

    }
  }
}

#endif    /* ENTER_EVENT_HXX */
