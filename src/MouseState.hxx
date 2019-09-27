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

        m_mouseDragged(false),
        m_buttons()
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
      MouseState::updateMotionData(MouseEvent& /*event*/) {
        // Nothing to do for now.
      }

      inline
      void
      MouseState::updateWheelData(MouseEvent& /*event*/) {
        // Nothing to do for now.
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
