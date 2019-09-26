#ifndef    DROP_EVENT_HXX
# define   DROP_EVENT_HXX

# include "DropEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      DropEvent::DropEvent(const utils::Vector2f& startPos,
                           const utils::Vector2f& endPos,
                           EngineObject* receiver):
        Event(Event::Type::Drop,
              receiver,
              std::string("drop_event")),

        m_startPosition(startPos),
        m_endPosition(endPos)
      {}

      inline
      DropEvent::~DropEvent() {}

      inline
      const utils::Vector2f&
      DropEvent::getStartPosition() const noexcept {
        return m_startPosition;
      }

      inline
      const utils::Vector2f&
      DropEvent::getEndPosition() const noexcept {
        return m_endPosition;
      }

      inline
      bool
      DropEvent::equal(const Event& other) const noexcept {
        const DropEvent& e = dynamic_cast<const DropEvent&>(other);

        return
          Event::equal(other) &&
          getStartPosition() == e.getStartPosition() &&
          getEndPosition() == e.getEndPosition()
        ;
      }

    }
  }
}

#endif    /* DROP_EVENT_HXX */
