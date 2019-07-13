#ifndef    PAINT_EVENT_HXX
# define   PAINT_EVENT_HXX

# include "PaintEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      PaintEvent::PaintEvent(EngineObject* receiver):
        Event(Event::Type::Repaint,
              receiver,
              std::string("paint_event")),
        m_updateRegions()
      {}

      inline
      PaintEvent::PaintEvent(const utils::Boxf& updateRegion,
                             EngineObject* receiver):
        Event(Event::Type::Repaint,
              receiver,
              std::string("paint_event")),
        m_updateRegions(1u, updateRegion)
      {}

      inline
      PaintEvent::~PaintEvent() {}

      inline
      const std::vector<utils::Boxf>&
      PaintEvent::getUpdateRegions() const noexcept {
        return m_updateRegions;
      }

    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HXX */
