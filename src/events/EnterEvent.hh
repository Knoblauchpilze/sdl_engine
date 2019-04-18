#ifndef    ENTER_EVENT_HH
# define   ENTER_EVENT_HH

# include "Event.hh"
# include <memory>
# include <SDL2/SDL.h>
# include <maths_utils/Vector2.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EnterEvent: public Event {
        public:

          EnterEvent(const SDL_MouseMotionEvent& event);

          ~EnterEvent();

          void
          populateFromEngineData(Engine& engine) override;

          utils::Vector2f
          getMousePosition() const noexcept;

        private:

          void
          init();

        private:

          SDL_MouseMotionEvent m_motion;

      };

    }
  }
}

# include "EnterEvent.hxx"

#endif    /* ENTER_EVENT_HH */
