#ifndef    MOUSE_EVENT_HXX
# define   MOUSE_EVENT_HXX

# include "MouseEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      MouseEvent::MouseEvent(const SDL_MouseButtonEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_button_") + std::to_string(event.button)),
        m_button(std::make_shared<SDL_MouseButtonEvent>(event)),
        m_motion(nullptr),
        m_wheel(nullptr),
        m_mousePosition()
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseMotionEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_motion_") + std::to_string(event.state)),
        m_button(nullptr),
        m_motion(std::make_shared<SDL_MouseMotionEvent>(event)),
        m_wheel(nullptr),
        m_mousePosition()
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseWheelEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_wheel_") + std::to_string(event.direction)),
        m_button(nullptr),
        m_motion(nullptr),
        m_wheel(std::make_shared<SDL_MouseWheelEvent>(event)),
        m_mousePosition()
      {
        init();
      }

      inline
      MouseEvent::~MouseEvent() {}

      inline
      MouseEvent::Button
      MouseEvent::getButton() const noexcept {
        // We can retrieve a button either if the event corresponds to a mouse pressed
        // or released or if the mouse is being dragged.
        if (m_button != nullptr) {
          if (m_button->button == SDL_BUTTON_LEFT) {
            return Button::LeftButton;
          }
          if (m_button->button == SDL_BUTTON_RIGHT) {
            return Button::RightButton;
          }
          if (m_button->button == SDL_BUTTON_MIDDLE) {
            return Button::MiddleButton;
          }
        }

        // TODO: The state can actually hold several buttons.
        if (m_motion != nullptr) {
          if (m_motion->state == SDL_BUTTON_LEFT) {
            return Button::LeftButton;
          }
          if (m_motion->state == SDL_BUTTON_RIGHT) {
            return Button::RightButton;
          }
          if (m_motion->state == SDL_BUTTON_MIDDLE) {
            return Button::MiddleButton;
          }
        }

        return Button::NoButton;
      }

      inline
      bool
      MouseEvent::isPress() const noexcept {
        return getType() == Event::Type::MouseButtonPress;
      }

      inline
      bool
      MouseEvent::isRelease() const noexcept {
        // A release event is either a mouse button release event or a double click.
        return
          getType() == Event::Type::MouseButtonRelease ||
          getType() == Event::Type::MouseDoubleClick
        ;
      }

      inline
      utils::Vector2f
      MouseEvent::getMousePosition() const noexcept {
        return m_mousePosition;
      }

      inline
      utils::Vector2i
      MouseEvent::getMove() const noexcept {
        if (m_motion != nullptr) {
          return utils::Vector2i(m_motion->xrel, m_motion->yrel);
        }

        return utils::Vector2i();
      }

      inline
      MouseEvent::Direction
      MouseEvent::getDirection() const noexcept {
        if (m_wheel != nullptr) {
          if (getScroll().y() > 0) {
            return Direction::Up;
          }
          if (getScroll().y() < 0) {
            return Direction::Down;
          }
        }

        return Direction::NoScroll;
      }

      inline
      utils::Vector2i
      MouseEvent::getScroll() const noexcept {
        if (m_wheel != nullptr) {
          return utils::Vector2i(m_wheel->x, m_wheel->y);
        }

        return utils::Vector2i();
      }

      inline
      void
      MouseEvent::init() {
        initButton();
        initMotion();
        initWheel();
      }

    }
  }
}

#endif    /* MOUSE_EVENT_HXX */
