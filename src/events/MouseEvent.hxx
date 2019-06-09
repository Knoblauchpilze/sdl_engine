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
        return getType() == Event::Type::MouseButtonRelease;
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
      MouseEvent::transformForWindow(const utils::Sizef& size) noexcept {
        // Can only do that if the event is related to a mouse position at all.
        // This excludes _de facto_ the mouse wheel event.
        //
        // The center of the coordinate frame to use in the window is given by
        // the center of the rectangle defined by the input `size`. We then
        // compute the offset to reach the mouse position defined by the event
        // and this constitutes the final position to use.

        const utils::Vector2f center(size.w() / 2.0f, size.h() / 2.0f);

        if (m_button != nullptr) {
          m_mousePosition = utils::Vector2f(
            static_cast<float>(m_button->x) - center.x(),
            center.y() - static_cast<float>(m_button->y)
          );
        }
        else if (m_motion != nullptr) {
          m_mousePosition = utils::Vector2f(
            static_cast<float>(m_motion->x) - center.x(),
            center.y() - static_cast<float>(m_motion->y)
          );
        }
        else {
          // Default position.
          m_mousePosition = utils::Vector2f();
        }
      }

      inline
      bool
      MouseEvent::equal(const Event& other) const noexcept {
        const MouseEvent& e = dynamic_cast<const MouseEvent&>(other);
        return
          Event::equal(other) &&
          getButton() == e.getButton() &&
          getMousePosition() == e.getMousePosition() &&
          getMove() == e.getMove() &&
          getDirection() == e.getDirection() &&
          getScroll() == e.getScroll()
        ;
      }

      inline
      void
      MouseEvent::init() {
        initButton();
        initMotion();
        initWheel();
      }

      inline
      void
      MouseEvent::initButton() {
        // Check whether the event concerns a mouse button at all.
        if (m_button == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_button->type != SDL_MOUSEBUTTONDOWN && m_button->type != SDL_MOUSEBUTTONUP) {
          error(std::string("Cannot create mouse event from invalid type ") + std::to_string(static_cast<int>(m_button->type)));
        }

        Event::Type type = Event::Type::MouseButtonPress;
        if (m_button->type == SDL_MOUSEBUTTONUP) {
          type = Event::Type::MouseButtonRelease;
        }

        setType(type);

        setSDLWinID(m_button->windowID);
      }

      inline
      void
      MouseEvent::initMotion() {
        // Check whether the event concerns a mouse motion at all.
        if (m_motion == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_motion->type != SDL_MOUSEMOTION) {
          error(std::string("Cannot create mouse event from invalid type ") + std::to_string(static_cast<int>(m_motion->type)));
        }

        setType(Event::Type::MouseMove);

        setSDLWinID(m_motion->windowID);
      }

      inline
      void
      MouseEvent::initWheel() {
        // Check whether the event concerns a mouse wheel at all.
        if (m_wheel == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_wheel->type != SDL_MOUSEWHEEL) {
          error(std::string("Cannot create mouse event from invalid type ") + std::to_string(static_cast<int>(m_wheel->type)));
        }

        setType(Event::Type::MouseWheel);

        setSDLWinID(m_wheel->windowID);
      }

    }
  }
}

#endif    /* MOUSE_EVENT_HXX */
