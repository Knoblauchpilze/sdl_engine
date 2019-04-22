#ifndef    RESIZE_EVENT_HH
# define   RESIZE_EVENT_HH

# include "Event.hh"
# include <core_utils/Uuid.hh>
# include <maths_utils/Size.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class ResizeEvent: public Event {
        public:

          ResizeEvent(const utils::Sizef& newSize,
                      const utils::Sizef& oldSize,
                      EngineObject* receiver = nullptr);

          ~ResizeEvent();

          void
          populateFromEngineData(Engine& engine) override;

          const utils::Sizef&
          getNewSize() const noexcept;

          const utils::Sizef&
          getOldSize() const noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          utils::Sizef m_new;
          utils::Sizef m_old;

      };

    }
  }
}

# include "ResizeEvent.hxx"

#endif    /* RESIZE_EVENT_HH */
