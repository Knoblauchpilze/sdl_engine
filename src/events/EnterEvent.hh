#ifndef    ENTER_EVENT_HH
# define   ENTER_EVENT_HH

# include "Event.hh"
# include <memory>
# include <maths_utils/Vector2.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EnterEvent: public Event {
        public:

          EnterEvent(const utils::Vector2f& coordinates,
                     EngineObject* receiver = nullptr);

          ~EnterEvent();

          void
          populateFromEngineData(Engine& engine) override;

          const utils::Vector2f&
          getMousePosition() const noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          utils::Vector2f m_coordinates;

      };

    }
  }
}

# include "EnterEvent.hxx"

#endif    /* ENTER_EVENT_HH */
