#ifndef    MOUSE_STATE_HH
# define   MOUSE_STATE_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include "MouseEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class MouseState: public utils::CoreObject {
        public:

          /**
           * @brief - Creates a mouse state with default properties.
           */
          MouseState();

          ~MouseState() = default;

          /**
           * @brief - Used to perform the update of both the internal state
           *          and of the input event with the additional data provided
           *          by it.
           *          Most of the job here is to update the internal state to
           *          reflect the new event, but on some specific events like
           *          mouse drag it provides some more information abuot the
           *          position of the mouse at the beginning of the drag and
           *          drop event.
           * @param event - the mouse event to use to update the internal state.
           *                It can be modified in some occasions.
           */
          void
          updateEvent(MouseEvent& event);

        private:

          /**
           * @brief - Convenience define to allow for an easy-to-detect not
           *          assigned vector.
           */
          using OptionalPosition = std::shared_ptr<utils::Vector2f>;

          /**
           * @brief - A timestamp.
           */
          using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

          /**
           * @brief - A description of all the values needed to define a mouse
           *          button such as whether it is being dragged or if a click
           *          already occurred and where.
           */
          struct ButtonDesc {
            bool pressed;
            bool dragged;
            OptionalPosition lastClick;
            Timestamp dragStart;

            /**
             * @brief - We need to provide such an operator in case of collisions
             *          in the table.
             * @param rhs - the value to compare with `this`.
             * @return - `true` if `rhs` and `this` are equal, `false` otherwise.
             */
            bool
            operator==(const ButtonDesc& rhs) const noexcept;
          };

          /**
           * @brief - Used to init the internal table containing the state of the
           *          buttons.
           */
          void
          init();

          /**
           * @brief - Retrieves the description of the button provided as input.
           *          The return value allows full modification of the state of
           *          the button's data if needed.
           * @param button - the button which description should be retrieved.
           * @return - the internal state registered for this button.
           */
          ButtonDesc&
          getDescForButton(mouse::Button button);

          /**
           * @brief - Used internally to perform the update of the drag properties
           *          of the buttons.
           * @param event - the event to use to update the internal state.
           */
          void
          updateDragData(MouseEvent& event);

          /**
           * @brief - Used internally to perform the update of the click properties
           *          of the buttons.
           * @param event - the event to use to update the internal state.
           */
          void
          updateClickData(MouseEvent& event);

          /**
           * @brief - Used internally to perform the update of the motion properties
           *          of the mouse.
           * @param event - the event to use to update the internal state.
           */
          void
          updateMotionData(MouseEvent& event);

          /**
           * @brief - Used internally to perform the update of the wheel properties
           *          of the mouse.
           * @param event - the event to use to update the internal state.
           */
          void
          updateWheelData(MouseEvent& event);

          /**
           * @brief - Retrieve a timestamp to be used to update the internal state for
           *          example
           * @return - a timestamp to be used.
           */
          static
          Timestamp
          getTimestamp() noexcept;

        private:

          /**
           * @brief - Convenience define to describe a map where any
           *          button is associated to its last known click
           *          position.
           */
          using ButtonsTable = std::unordered_map<mouse::Button, ButtonDesc>;

          /**
           * @brief - These booleans keeps track of whether the mouse is currently being
           *          dragged or not. The default value is `false`. As for the 
           */
          bool m_mouseDragged;

          /**
           * @brief - Contains the information of all the mouse buttons.
           */
           ButtonsTable m_buttons;
      };

      using MouseStateShPtr = std::shared_ptr<MouseState>;
    }
  }
}

# include "MouseState.hxx"

#endif    /* MOUSE_STATE_HH */
