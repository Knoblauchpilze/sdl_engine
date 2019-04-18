#ifndef    MOUSE_EVENT_HH
# define   MOUSE_EVENT_HH

# include <memory>
# include <SDL2/SDL.h>
# include <maths_utils/Vector2.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class MouseEvent: public Event {
        public:

          enum class Button {
            NoButton,
            LeftButton,
            RightButton,
            MiddleButton
          };

          enum class Direction {
            NoScroll,
            Up,
            Down
          };

        public:

          MouseEvent(const SDL_MouseButtonEvent& event);

          MouseEvent(const SDL_MouseMotionEvent& event);

          MouseEvent(const SDL_MouseWheelEvent& event);

          ~MouseEvent();

          void
          populateFromEngineData(Engine& engine) override;

          Button
          getButton() const noexcept;

          bool
          isPress() const noexcept;

          bool
          isRelease() const noexcept;

          utils::Vector2f
          getMousePosition() const noexcept;

          int
          getXRel() const noexcept;

          int
          getYRel() const noexcept;

          Direction
          getDirection() const noexcept;

          int
          getXScroll() const noexcept;

          int
          getYScroll() const noexcept;

        private:

          void
          init();

          void
          initButton();

          void
          initMotion();

          void
          initWheel();

        private:

          std::shared_ptr<SDL_MouseButtonEvent> m_button;
          std::shared_ptr<SDL_MouseMotionEvent> m_motion;
          std::shared_ptr<SDL_MouseWheelEvent> m_wheel;

      };

      using MouseEventShPtr = std::shared_ptr<MouseEvent>;
    }
  }
}

# include "MouseEvent.hxx"

#endif    /* MOUSE_EVENT_HH */
