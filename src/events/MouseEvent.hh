#ifndef    MOUSE_EVENT_HH
# define   MOUSE_EVENT_HH

# include <memory>
# include <SDL2/SDL.h>
# include <maths_utils/Size.hh>
# include <maths_utils/Vector2.hh>
# include <core_utils/CoreFlag.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace mouse {

        /**
         * @brief - Mouse buttons handled by this kind of event.
         */
        enum class Button {
          Left        = 0,
          Right       = 1,
          Middle      = 2,
          ValuesCount = 3
        };

        /**
         * @brief - Retrieves a human readable name from the input button.
         * @param button - an enumeration value containing a button whose
         *                 name should be retrieved.
         * @return - a string describing the button provided as argument.
         */
        std::string
        getNameFromButton(const Button& button) noexcept;

        /**
         * @brief - Enumeration which describes the direction of scrolling.
         */
        enum class Direction {
          NoScroll,
          Up,
          Down
        };

        /**
         * @brief - Retrieves a human readable name from the input scroll
         *          direction.
         * @param button - an enumeration value containing a scroll direction
         *                 to interpret.
         * @return - a string describing the scroll direction provided as
         *           argument.
         */
        std::string
        getNameFromScroll(const Direction& direction) noexcept;

        /**
         * @brief - Flag describing the buttons pressed at any moment.
         */
        using Buttons = utils::CoreFlag<mouse::Button>;

      }

      class MouseEvent: public Event {

        public:

          MouseEvent(const SDL_MouseButtonEvent& event);

          MouseEvent(const SDL_MouseMotionEvent& event);

          MouseEvent(const SDL_MouseWheelEvent& event);

          ~MouseEvent();

          void
          populateFromEngineData(Engine& engine) override;

          /**
           * @brief - Used to retrieve the current state of all the buttons
           *          of the mouse. In the case of a mouse pressed or released
           *          event it will *also* contain the pressed or released
           *          button.
           *          In the case of a mouse motion it will contain all the
           *          buttons pressed at the moment of the motion.
           * @return - the state of all the buttons of the mouse.
           */
          mouse::Buttons
          getButtons() const noexcept;

          /**
           * @brief - Returns the button associated to this event. Mostly useful
           *          in the case of a mouse button pressed or released, otherwise
           *          it throws an exception.
           * @return - the button associated to this mouse event in the case of a
           *           mouse button pressed or released.
           */
          mouse::Button
          getButton() const;

          bool
          isPress() const noexcept;

          bool
          isRelease() const noexcept;

          /**
           * @bried - Retrieves the position of the mouse at the beginning of the
           *          current action. Most of the time this value will be identical
           *          to the one returned by `getMousePosition` but in the case of
           *          a drag event for example, this position will be keeping the
           *          position of the cursor at the moment the mouse started to be
           *          dragged: this allows to easily perform some update while the
           *          mouse is being dragged.
           * @return - the position of the mouse at the beginning of the current
           *           action. Usually equal to the value returned by the method
           *           `getMousePosition` but might differ in some cases.
           */
          utils::Vector2f
          getInitMousePosition() const noexcept;

          /**
           * @brief - Returns the mouse position as a vector expressed in the
           *          corresponding window's coordinate system.
           *          Note that all but the mouse wheel events have a position
           *          associated to them.
           * @return - the position associated to this mouse event if any in
           *           the related window's coordinate frame.
           */
          utils::Vector2f
          getMousePosition() const noexcept;

          utils::Vector2i
          getMove() const noexcept;

          mouse::Direction
          getDirection() const noexcept;

          utils::Vector2i
          getScroll() const noexcept;

          /**
           * @brief - Used to update the last position of the the mouse when a click
           *          was detected. This allows to update internally the attribute
           *          `m_mouseInitPosition`.
           *          Note that the input position is expected to be valid in the
           *          window associated to this event: no further conversion will be
           *          performed on the provided value.
           * @param click - the last position of the mouse when a click was detected.
           */
          void
          updateLastClickPosition(const utils::Vector2f& click) noexcept;

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

          /**
           * @brief - Used to populate the internal `m_buttons` flag from the input value describing
           *          the `API` information about the buttons currently being pressed.
           *          We use the provided value which is some sort of raw flag of all the buttons as
           *          described by the `API`.
           * @param apiButtons - some sort of flag describing the buttons pressed as reported by the
           *                     underlying `API`.
           */
          void
          initButtonFromState(std::uint32_t apiButtons);

        private:

          std::shared_ptr<SDL_MouseButtonEvent> m_button;
          std::shared_ptr<SDL_MouseMotionEvent> m_motion;
          std::shared_ptr<SDL_MouseWheelEvent> m_wheel;

          /**
           * @brief - The following attribute are used to keep track of the position of the mouse. The
           *          `m_mousePosition` is always populated with the current position of the cursor
           *          while `m_initMousePosition` is populated with the position of the mouse at the
           *          beginning of the current action. It is equivalent to `m_mousePosition` in most
           *          cases but can differ for example in the event of the mouse being dragged.
           */
          utils::Vector2f m_initMousePosition;
          utils::Vector2f m_mousePosition;

          /**
           * @brief - Describes the mouse button pressed as described by the
           *          underlying API. Several mouse buttons can be active at
           *          the same time.
           */
          mouse::Buttons m_buttons;

      };

      using MouseEventShPtr = std::shared_ptr<MouseEvent>;
    }
  }
}

# include "MouseEvent.hxx"
# include "MouseEvent_specialization.hxx"

#endif    /* MOUSE_EVENT_HH */
