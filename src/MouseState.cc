
# include "MouseState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      MouseState::updateEvent(MouseEvent& event) {
        // Call the dedicated handler.
        switch (event.getType()) {
          case Event::Type::MouseDrag:
            updateDragData(event);
            break;
          case Event::Type::MouseButtonPress:
          case Event::Type::MouseButtonRelease:
          case Event::Type::MouseDoubleClick:
            updateClickData(event);
            break;
          case Event::Type::MouseMove:
            updateMotionData(event);
            break;
          case Event::Type::MouseWheel:
            updateWheelData(event);
            break;
          default:
            // Other cases should not happen as the input event
            // is a mouse event already.
            break;
        }
      }

      void
      MouseState::updateDragData(MouseEvent& event) {
        // Update the drag state of the corresponding buttons.
        mouse::Buttons b = event.getButtons();

        bool valid = false;
        mouse::Button best = mouse::Button::Left;
        Timestamp tick;

        if (b.isSet(mouse::Button::Left)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(mouse::Button::Left);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          // Initialize the best button found so far.
          valid = true;
          tick = desc.dragStart;
        }

        if (b.isSet(mouse::Button::Middle)) {
          // Retrieve the button's data.
          ButtonDesc& desc = getDescForButton(mouse::Button::Middle);

          // Update the dragged state if needed.
          if (!desc.dragged) {
            desc.dragged = true;
            desc.dragStart = getTimestamp();
          }

          if (!valid || tick < desc.dragStart) {
            valid = true;
            tick = desc.dragStart;
            best = mouse::Button::Middle;
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

          if (!valid || tick < desc.dragStart) {
            valid = true;
            tick = desc.dragStart;
            best = mouse::Button::Right;
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
        else {
          ButtonDesc& desc = getDescForButton(best);

          if (desc.lastClick == nullptr) {
            log(
              std::string("Could not assign initial position of button ") + mouse::getNameFromButton(best) +
              std::string(" which has not been clicked yet"),
              utils::Level::Warning
            );

            return;
          }

          event.updateLastClickPosition(*desc.lastClick);
        }
      }

      void
      MouseState::updateClickData(MouseEvent& event) {
        // Retrieve the button's data.
        ButtonDesc& desc = getDescForButton(event.getButton());

        // Update the pressed status and the position of the click.
        desc.pressed = (event.getType() != Event::Type::MouseButtonRelease);
        desc.lastClick = std::make_shared<utils::Vector2f>(event.getMousePosition());

        // The drag status should be reset in case it is active: we
        // should also issue a drop event.
        if (desc.dragged && event.getType() == Event::Type::MouseButtonRelease) {
          log("Should issue a drop event", utils::Level::Warning);
        }
      }

    }
  }
}
