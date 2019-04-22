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
        m_wheel(nullptr)
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseMotionEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_motion_") + std::to_string(event.state)),
        m_button(nullptr),
        m_motion(std::make_shared<SDL_MouseMotionEvent>(event)),
        m_wheel(nullptr)
      {
        init();
      }

      inline
      MouseEvent::MouseEvent(const SDL_MouseWheelEvent& event):
        Event(Event::Type::None, nullptr, std::string("mouse_wheel_") + std::to_string(event.direction)),
        m_button(nullptr),
        m_motion(nullptr),
        m_wheel(std::make_shared<SDL_MouseWheelEvent>(event))
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
        if (m_motion != nullptr) {
          return utils::Vector2f(m_motion->x, m_motion->y);
        }

        if (m_button != nullptr) {
          return utils::Vector2f(m_button->x, m_button->y);
        }

        return utils::Vector2f(0.0f, 0.0f);
      }

      inline
      int
      MouseEvent::getXRel() const noexcept {
        if (m_motion != nullptr) {
          return m_motion->xrel;
        }

        return 0;
      }

      inline
      int
      MouseEvent::getYRel() const noexcept {
        if (m_motion != nullptr) {
          return m_motion->yrel;
        }

        return 0;
      }

      inline
      MouseEvent::Direction
      MouseEvent::getDirection() const noexcept {
        if (m_wheel != nullptr) {
          if (getYScroll() > 0) {
            return Direction::Up;
          }
          if (getYScroll() < 0) {
            return Direction::Down;
          }
        }

        return Direction::NoScroll;
      }

      inline
      int
      MouseEvent::getXScroll() const noexcept {
        if (m_wheel != nullptr) {
          return m_wheel->x;
        }

        return 0;
      }

      inline
      int
      MouseEvent::getYScroll() const noexcept {
        if (m_wheel != nullptr) {
          return m_wheel->y;
        }

        return 0;
      }

      inline
      bool
      MouseEvent::equal(const Event& other) const noexcept {
        const MouseEvent& e = dynamic_cast<const MouseEvent&>(other);
        return
          Event::equal(other) &&
          getButton() == e.getButton() &&
          getMousePosition() == e.getMousePosition() &&
          getXRel() == e.getXRel() &&
          getYRel() == e.getYRel() &&
          getDirection() == e.getDirection() &&
          getXScroll() == e.getXScroll() &&
          getYScroll() == e.getYScroll()
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
      }

    }
  }
}

#endif    /* MOUSE_EVENT_HXX */
