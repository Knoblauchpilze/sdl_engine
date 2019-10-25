
# include "MouseState.hh"
# include "DropEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      MouseState::updateFromWindowEvent(const WindowEvent& e) noexcept {
        // We want to save the last window identifier based on the window
        // linked to this event.
        m_lastWinID = e.getWindID();

        // We also need to update the current status of the mouse: is it
        // in a valid window or outside ?
        // Based on the type of the input event we can update things:
        // - a window enter/leave event are pretty self-explanatory.
        // - a window resize does not allow to conclude anything.
        switch (e.getType()) {
          case Event::Type::WindowEnter:
            m_isInWindow = true;
            break;
          case Event::Type::WindowLeave:
            m_isInWindow = false;
            break;
          case Event::Type::WindowResize:
            // Cannot conclude anything: let the state as it is.
            break;
          default:
            // Not handled window event type: do nothing.
            break;
        }
      }

      std::vector<EventShPtr>
      MouseState::updateEvent(MouseEvent& event) {
        std::vector<EventShPtr> newEvents;

        // Call the dedicated handler.
        switch (event.getType()) {
          case Event::Type::MouseDrag:
            updateDragData(event, newEvents);
            break;
          case Event::Type::MouseButtonPress:
          case Event::Type::MouseButtonRelease:
          case Event::Type::MouseDoubleClick:
            updateClickData(event, newEvents);
            break;
          case Event::Type::MouseMove:
            updateMotionData(event, newEvents);
            break;
          case Event::Type::MouseWheel:
            updateWheelData(event, newEvents);
            break;
          default:
            // Other cases should not happen as the input event
            // is a mouse event already.
            break;
        }

        // Return the new events created by the update.
        return newEvents;
      }

      utils::Uuid
      MouseState::updateWithBestSuitedWindow(MouseEvent& event) {
        // We want to determine the best suited window. Basically we want to
        // only assign the `m_lastWinID` to the input event in case it does
        // not already have one assigned.
        // This solution might not be perfect but it's still better than to
        // have no indication as to the window related to this event at all.
        if (!event.getWindID().valid()) {
          event.setWindowID(m_lastWinID);

          return m_lastWinID;
        }

        // The identifier associated to the event is already valid, return it.
        return event.getWindID();
      }

      void
      MouseState::updateDragData(MouseEvent& event,
                                 std::vector<EventShPtr>& /*newEvents*/)
      {
        // Update the drag state of the corresponding buttons.
        mouse::Buttons b = event.getButtons();

        bool vl = updateDragDataForButton(b, event, mouse::Button::Left);
        bool vm = updateDragDataForButton(b, event, mouse::Button::Middle);
        bool vr = updateDragDataForButton(b, event, mouse::Button::Right);

        // Check consistency.
        if (!vl && !vm && !vr) {
          // Not a single button was found even though it's a drag event.
          // This is weird.
          log(
            std::string("Found drag event with no known button being pressed, coult not") +
            std::string(" update initial mouse position"),
            utils::Level::Warning
          );

          return;
        }
      }

      void
      MouseState::updateClickData(MouseEvent& event,
                                  std::vector<EventShPtr>& newEvents)
      {
        // Retrieve the button's data.
        ButtonDesc& desc = getDescForButton(event.getButton());

        // Update the pressed status and the position of the click.
        desc.pressed = (event.getType() != Event::Type::MouseButtonRelease);

        // The drag status should be reset in case it is active: we
        // should also issue a drop event.
        if (desc.dragged && event.getType() == Event::Type::MouseButtonRelease) {
          // Untick the `dragged` flag.
          desc.dragged = false;

          // Update the dragged status for the event.
          event.updateDraggedState(true);

          // Issue a `Drop` event if possible.
          if (desc.lastClick == nullptr) {
            log(
              std::string("Released mouse button ") + mouse::getNameFromButton(event.getButton()) +
              " while no click has been registered so far",
              utils::Level::Warning
            );
          }
          else {
            EventShPtr drop = std::make_shared<DropEvent>(
              *desc.lastClick,
              event.getMousePosition()
            );

            newEvents.push_back(drop);
          }
        }

        // Finally update the last click position.
        desc.lastClick = std::make_shared<utils::Vector2f>(event.getMousePosition());

        // Also we will handle the update of the `m_isInWindow` boolean: when the user clicks
        // somewhere in the application we are notified and we want to update said boolean in
        // order to keep consistent state of the mouse.
        utils::Uuid id = event.getWindID();

        // If the identifier is valid, we consider that we're inside the window, unless the
        // identifier already describes the last known window: indeed in this case we can't
        // conclude anything as the mouse might have left the window in the meantime.
        if (id.valid() && id != m_lastWinID) {
          m_isInWindow = true;
        }
      }

      bool
      MouseState::updateDragDataForButton(const mouse::Buttons& b,
                                          MouseEvent& e,
                                          const mouse::Button& button)
      {
        bool valid = false;

        if (b.isSet(button)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(button);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          // Initialize the click position for this button.
          if (desc.lastClick == nullptr) {
            log(
              std::string("Could not assign initial position of button ") + mouse::getNameFromButton(button) +
              std::string(" which has not been clicked yet"),
              utils::Level::Warning
            );
          }
          else {
            valid = true;
            e.updateLastClickPosition(button, *desc.lastClick);
          }
        }

        return valid;
      }

    }
  }
}
