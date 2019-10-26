#ifndef    PAINT_EVENT_HXX
# define   PAINT_EVENT_HXX

# include "PaintEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace update {

        inline
        std::string
        getNameFromFrame(const Frame& frame) noexcept {
          switch (frame) {
            case Frame::Local:
              return "local";
            case Frame::Global:
              return "global";
            default:
              return "unknown";
          }
        }

        inline
        std::string
        Region::toString() const noexcept {
          std::string out("[");

          out += area.toString();
          out += ", ";
          out += getNameFromFrame(frame);

          out += "]";

          return out;
        }

        inline
        bool
        Region::operator==(const Region& rhs) const noexcept {
          return frame == rhs.frame && area == rhs.area;
        }

        inline
        bool
        Region::operator!=(const Region& rhs) const noexcept {
          return !operator==(rhs);
        }

      }

      inline
      PaintEvent::PaintEvent(EngineObject* receiver):
        Event(Event::Type::Repaint,
              receiver,
              std::string("paint_event")),

        m_updateRegions()
      {}

      inline
      PaintEvent::PaintEvent(const utils::Boxf& updateRegion,
                             const update::Frame& frame,
                             EngineObject* receiver):
        Event(Event::Type::Repaint,
              receiver,
              std::string("paint_event")),

        m_updateRegions(1u, update::Region{updateRegion, frame})
      {}

      inline
      PaintEvent::~PaintEvent() {}

      inline
      bool
      PaintEvent::hasUpdateRegions() const noexcept {
        return !m_updateRegions.empty();
      }

      inline
      const std::vector<update::Region>&
      PaintEvent::getUpdateRegions() const noexcept {
        return m_updateRegions;
      }

      inline
      bool
      PaintEvent::addUpdateRegion(const utils::Boxf& area,
                                  const update::Frame& frame) noexcept
      {
        return addUpdateRegion(update::Region{area, frame});
      }

    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HXX */
