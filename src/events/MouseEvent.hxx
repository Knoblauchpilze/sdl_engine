#ifndef    MOUSE_EVENT_HXX
# define   MOUSE_EVENT_HXX

# include "MouseEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace mouse {

        inline
        std::string
        getNameFromButton(const Button& button) noexcept {
          switch (button) {
            case Button::Left:
              return std::string("Left");
            case Button::Right:
              return std::string("Right");
            case Button::Middle:
              return std::string("Middle");
            default:
              return std::string("Unknown");
          }
        }

        inline
        std::string
        getNameFromScroll(const Direction& direction) noexcept {
          switch (direction) {
            case Direction::NoScroll:
              return std::string("NoScroll");
            case Direction::Up:
              return std::string("Up");
            case Direction::Down:
              return std::string("Down");
            default:
              return std::string("Unknown");
          }
        }

      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseButtonEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_button_") + std::to_string(event.button)),

        m_button(std::make_shared<SDL_MouseButtonEvent>(event)),
        m_motion(nullptr),
        m_wheel(nullptr),

        m_initMousePosition(),
        m_mousePosition(),

        m_buttons()
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseMotionEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_motion_") + std::to_string(event.state)),

        m_button(nullptr),
        m_motion(std::make_shared<SDL_MouseMotionEvent>(event)),
        m_wheel(nullptr),

        m_initMousePosition(),
        m_mousePosition(),

        m_buttons()
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseWheelEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_wheel_") + std::to_string(event.direction)),

        m_button(nullptr),
        m_motion(nullptr),
        m_wheel(std::make_shared<SDL_MouseWheelEvent>(event)),

        m_initMousePosition(),
        m_mousePosition(),

        m_buttons()
      {
        init();
      }

      inline
      MouseEvent::~MouseEvent() {}

      inline
      mouse::Buttons
      MouseEvent::getButtons() const noexcept {
        return m_buttons;
      }

      inline
      mouse::Button
      MouseEvent::getButton() const {
        // Check whether a button is available.
        if (m_button != nullptr) {
          if (m_button->button == SDL_BUTTON_LEFT) {
            return mouse::Button::Left;
          }
          if (m_button->button == SDL_BUTTON_RIGHT) {
            return mouse::Button::Right;
          }
          if (m_button->button == SDL_BUTTON_MIDDLE) {
            return mouse::Button::Middle;
          }
        }

        // Either no button is defined or not a valid button anyway.
        error(
          std::string("Cannot retrieve button associated to event ") + Event::getNameFromType(getType()),
          std::string("No such button")
        );
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
      MouseEvent::getInitMousePosition() const noexcept {
        return m_initMousePosition;
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
      mouse::Direction
      MouseEvent::getDirection() const noexcept {
        if (m_wheel != nullptr) {
          if (getScroll().y() > 0) {
            return mouse::Direction::Up;
          }
          if (getScroll().y() < 0) {
            return mouse::Direction::Down;
          }
        }

        return mouse::Direction::NoScroll;
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
