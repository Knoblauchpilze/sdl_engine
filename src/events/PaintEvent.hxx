#ifndef    PAINT_EVENT_HXX
# define   PAINT_EVENT_HXX

# include "PaintEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      PaintEvent::PaintEvent(const utils::Boxf& updateRegion,
                             EngineObject* receiver):
        Event(Event::Type::Repaint,
              receiver,
              std::string("paint_event")),
        m_updateRegion(updateRegion)
      {}

      inline
      PaintEvent::~PaintEvent() {}

      inline
      const utils::Boxf&
      PaintEvent::getUpdateRegion() const noexcept {
        return m_updateRegion;
      }

    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HXX */
