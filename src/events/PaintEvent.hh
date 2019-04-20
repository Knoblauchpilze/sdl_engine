#ifndef    PAINT_EVENT_HH
# define   PAINT_EVENT_HH

# include <memory>
# include <maths_utils/Box.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class PaintEvent: public Event {
        public:

          PaintEvent(const utils::Boxf& updateRegion);

          ~PaintEvent();

          const utils::Boxf&
          getUpdateRegion() const noexcept;

          void
          populateFromEngineData(Engine& engine) override;

        private:

          utils::Boxf m_updateRegion;

      };

      using PaintEventShPtr = std::shared_ptr<PaintEvent>;
    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HH */
