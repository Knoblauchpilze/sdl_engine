#ifndef    MOUSE_STATE_HXX
# define   MOUSE_STATE_HXX

# include "MouseState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      bool
      MouseState::ButtonDesc::operator==(const ButtonDesc& rhs) const noexcept {
        if (pressed != rhs.pressed || dragged != rhs.dragged || dragStart != rhs.dragStart) {
          return false;
        }

        if (lastClick == nullptr && rhs.lastClick == nullptr) {
          return true;
        }
        else if (lastClick == nullptr && rhs.lastClick != nullptr) {
          return false;
        }
        else if (lastClick != nullptr && rhs.lastClick == nullptr) {
          return false;
        }
        else {
          return *lastClick == *rhs.lastClick;
        }
      }

      inline
      MouseState::MouseState():
        utils::CoreObject(std::string("mouse_state")),

        m_buttons(),

        m_lastMousePosition(),

        m_isInWindow(false),
        m_lastWinID()
      {
        init();
      }

      inline
      void
      MouseState::init() {
        m_buttons[mouse::Button::Left] = ButtonDesc{false, false, nullptr, getTimestamp()};
        m_buttons[mouse::Button::Middle] = ButtonDesc{false, false, nullptr, getTimestamp()};
        m_buttons[mouse::Button::Right] = ButtonDesc{false, false, nullptr, getTimestamp()};
      }

      inline
      MouseState::ButtonDesc&
      MouseState::getDescForButton(mouse::Button button) {
        ButtonsTable::iterator it = m_buttons.find(button);

        if (it == m_buttons.end()) {
          error(
            std::string("Could not get description for button ") + mouse::getNameFromButton(button),
            std::string("No such description")
          );
        }

        return it->second;
      }

      inline
      void
      MouseState::updateMotionData(MouseEvent& event,
                                   std::vector<EventShPtr>& /*newEvents*/)
      {
        // A mouse motion can occur inside the window. We want to update the `m_isInWindow`
        // boolean for the case where the mouse is already inside the application when the
        // first window is drawn. We need to check whether the input mouse event has an
        // associated window identifier: if this is the case it means that the motion is
        // happening inside this window. Indeed otherwise the event system will not be
        // notified of such events.
        utils::Uuid id = event.getWindID();

        // If the identifier is valid, we consider that we're inside the window.
        if (id.valid()) {
          m_isInWindow = true;
        }

        // Also update the position of the mouse.
        m_lastMousePosition = event.getMousePosition();
      }

      inline
      void
      MouseState::updateWheelData(MouseEvent& event,
                                  std::vector<EventShPtr>& /*newEvents*/)
      {
        // Assign the mouse position from the last known position.
        event.updateMousePosition(m_lastMousePosition);
      }

      inline
      MouseState::Timestamp
      MouseState::getTimestamp() noexcept {
        return std::chrono::steady_clock::now();
      }

    }
  }
}

#endif    /* MOUSE_STATE_HXX */
