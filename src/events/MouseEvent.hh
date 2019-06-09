#ifndef    MOUSE_EVENT_HH
# define   MOUSE_EVENT_HH

# include <memory>
# include <SDL2/SDL.h>
# include <maths_utils/Size.hh>
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

          utils::Vector2i
          getMove() const noexcept;

          Direction
          getDirection() const noexcept;

          utils::Vector2i
          getScroll() const noexcept;

          /**
           * @brief - Used to transform the internal mouse position to
           *          valid coordinates given the size of the window in
           *          input.
           *          Basically transfrom from a top left corner based
           *          coordinate frame to a centered one.
           * @param size - the total size of the window for which this
           *               event is associated.
           */
          void
          transformForWindow(const utils::Sizef& size) noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

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

          utils::Vector2f m_mousePosition;

      };

      using MouseEventShPtr = std::shared_ptr<MouseEvent>;
    }
  }
}

# include "MouseEvent.hxx"

#endif    /* MOUSE_EVENT_HH */
