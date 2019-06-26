#ifndef    RESIZE_EVENT_HH
# define   RESIZE_EVENT_HH

# include <memory>
# include "Event.hh"
# include <core_utils/Uuid.hh>
# include <maths_utils/Box.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class ResizeEvent: public Event {
        public:

          ResizeEvent(const utils::Boxf& newSize,
                      const utils::Boxf& oldSize,
                      EngineObject* receiver = nullptr);

          ~ResizeEvent();

          void
          populateFromEngineData(Engine& engine) override;

          const utils::Boxf&
          getNewSize() const noexcept;

          const utils::Boxf&
          getOldSize() const noexcept;

          void
          setNewSize(const utils::Boxf& newSize) noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          utils::Boxf m_new;
          utils::Boxf m_old;

      };

      using ResizeEventShPtr = std::shared_ptr<ResizeEvent>;
    }
  }
}

# include "ResizeEvent.hxx"

#endif    /* RESIZE_EVENT_HH */
