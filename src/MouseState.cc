
# include "MouseState.hh"
# include "DropEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

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

      void
      MouseState::updateDragData(MouseEvent& event,
                                 std::vector<EventShPtr>& /*newEvents*/)
      {
        // Update the drag state of the corresponding buttons.
        mouse::Buttons b = event.getButtons();

        bool valid = false;

        if (b.isSet(mouse::Button::Left)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(mouse::Button::Left);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          // Initialize the click position for this button.
          if (desc.lastClick == nullptr) {
            log(
              std::string("Could not assign initial position of button ") + mouse::getNameFromButton(mouse::Button::Left) +
              std::string(" which has not been clicked yet"),
              utils::Level::Warning
            );
          }
          else {
            valid = true;
            event.updateLastClickPosition(mouse::Button::Left, *desc.lastClick);
          }
        }

        if (b.isSet(mouse::Button::Middle)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(mouse::Button::Middle);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          // Initialize the click position for this button.
          if (desc.lastClick == nullptr) {
            log(
              std::string("Could not assign initial position of button ") + mouse::getNameFromButton(mouse::Button::Middle) +
              std::string(" which has not been clicked yet"),
              utils::Level::Warning
            );
          }
          else {
            valid = true;
            event.updateLastClickPosition(mouse::Button::Middle, *desc.lastClick);
          }
        }

        if (b.isSet(mouse::Button::Right)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(mouse::Button::Right);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          // Initialize the click position for this button.
          if (desc.lastClick == nullptr) {
            log(
              std::string("Could not assign initial position of button ") + mouse::getNameFromButton(mouse::Button::Right) +
              std::string(" which has not been clicked yet"),
              utils::Level::Warning
            );
          }
          else {
            valid = true;
            event.updateLastClickPosition(mouse::Button::Right, *desc.lastClick);
          }
        }

        // Update the last click position: we should use the button which
        // has been pressed last.
        if (!valid) {
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
      }

    }
  }
}
