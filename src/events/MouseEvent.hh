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

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific behavior to compare both the common attribute (using the
           *          base handler) and the properties defined by this type of event.
           * @param other - the `other` event to check for equality with `this`.
           * @return - true if both `other` and `this` are equal, false otherwise.
           */
          bool
          equal(const Event& other) const noexcept override;

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific merge strategy for this type of event. We will use the
           *          base handler internally to merge common attributes of the event,
           *          and then downcast the input `other` event to `this` dynamic type
           *          to perform custom merging.
           *          Note that the return value of the base class will indicate whether
           *          we should perform the custom merge strategy.
           *          The return value of this method is indistinguishable from the
           *          return value of the base `Event` method.
           * @param other - the `other` event to merge with `this`.
           * @return - true if the `other` event was merged with `this`, false otherwise.
           */
          bool
          mergePrivate(const Event& other) noexcept override;

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
