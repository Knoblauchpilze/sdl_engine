#ifndef    MOUSE_STATE_HH
# define   MOUSE_STATE_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include "MouseEvent.hh"
# include "WindowEvent.hh"

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
           * @brief - Used to perform the update of the internal state based on
           *          the data contained in the input window event. The update
           *          includes updating the internal attribute to keep track of
           *          the current active window.
           * @param e - the window event to process.
           */
          void
          updateFromWindowEvent(const WindowEvent& e) noexcept;

          /**
           * @brief - Used to perform the update of both the internal state
           *          and of the input event with the additional data provided
           *          by it.
           *          Most of the job here is to update the internal state to
           *          reflect the new event, but on some specific events like
           *          mouse drag it provides some more information about the
           *          position of the mouse at the beginning of the drag and
           *          drop event.
           *          Some event might also trigger some new events which are
           *          used to refine the engine's information with some more
           *          context.
           * @param event - the mouse event to use to update the internal state.
           *                It can be modified in some occasions.
           * @return - a list of events (which may be empty) containing all
           *           the events generated from the information conveyed by
           *           the input mouse event.
           */
          std::vector<EventShPtr>
          updateEvent(MouseEvent& event);

          /**
           * @brief - Used to try to guess a valid window identifier for the
           *          input mouse event based on the internal saved state of
           *          the mouse. The goal is to determine some sort of logic
           *          when an event is generated outside of any context by
           *          using the saved data to find the most logical window
           *          identifier to prolongate the event.
           *          Note that if this method is unable to determine any id
           *          which could make sense nothing is changed in the input
           *          event. Otherwise the best guess at the window identifier
           *          is filled for the input event.
           * @param event - the event for which a valid window identifier
           *                should be determined. Note that this value is
           *                modified if it has no window identifier associated
           *                to it upon entering this method and if a valid id
           *                can be found internally.
           * @return - the window identifier assigned to the window event if
           *           any, its initial value if one was already provided or
           *           an invalid identifier if nothing could be found.
           */
          utils::Uuid
          updateWithBestSuitedWindow(MouseEvent& event);

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
           *          of the buttons. The new events which might be generated by the
           *          update are pushed in the output argument `newEvents`.
           * @param event - the event to use to update the internal state.
           */
          void
          updateDragData(MouseEvent& event,
                         std::vector<EventShPtr>& newEvents);

          /**
           * @brief - Used internally to perform the update of the click properties
           *          of the buttons. The new events which might be generated by the
           *          update are pushed in the output argument `newEvents`.
           * @param event - the event to use to update the internal state.
           */
          void
          updateClickData(MouseEvent& event,
                          std::vector<EventShPtr>& newEvents);

          /**
           * @brief - Used internally to perform the update of the motion properties
           *          of the mouse. The new events which might be generated by the
           *          update are pushed in the output argument `newEvents`.
           * @param event - the event to use to update the internal state.
           */
          void
          updateMotionData(MouseEvent& event,
                           std::vector<EventShPtr>& newEvents);

          /**
           * @brief - Used internally to perform the update of the wheel properties
           *          of the mouse. The new events which might be generated by the
           *          update are pushed in the output argument `newEvents`.
           * @param event - the event to use to update the internal state.
           */
          void
          updateWheelData(MouseEvent& event,
                          std::vector<EventShPtr>& newEvents);

          /**
           * @brief - Updates the click data for the button specified in input given
           *          the mouse event and pressed buttons as input data. Note that
           *          this method returns a boolean indicating if the data for the
           *          specified event was updated or not.
           *          Note that the input event might be updated in case the button
           *          exists in the drag data.
           * @param b - the list of mouse buttons pressed as per calling this method.
           * @param e - the mouse event which generated the call to this method in
           *            the first place.
           * @param button - the button for which the drag data should be updated.
           * @return - `true` if the input button is pressed and if its drag data
           *           has been updated, `false` otherwise.
           */
          bool
          updateDragDataForButton(const mouse::Buttons& b,
                                  MouseEvent& e,
                                  const mouse::Button& button);

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
           * @brief - Contains the information of all the mouse buttons.
           */
           ButtonsTable m_buttons;

          /**
           * @brief - This boolean allows to keep track of whether the
           *          mouse is currently inside a window or not. If it
           *          is the case the `m_lastWinID` represents the id
           *          of the current window.
           *          If not the `m_lastWinID` represents the id of
           *          the last window the mouse was in.
           */
           bool m_isInWindow;

           /**
            * @brief - The identifier of the last window the mouse was
            *          in. Note that if the mouse has not yet been in
            *           any window this id might be invalid.
            */
           utils::Uuid m_lastWinID;
      };

      using MouseStateShPtr = std::shared_ptr<MouseState>;
    }
  }
}

# include "MouseState.hxx"

#endif    /* MOUSE_STATE_HH */
