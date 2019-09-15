
# include "MouseEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      MouseEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

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

      bool
      MouseEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const MouseEvent& usable = dynamic_cast<const MouseEvent&>(other);

        // Equalize internal fields.
        m_button = usable.m_button;
        m_motion = usable.m_motion;
        m_wheel = usable.m_wheel;

        m_mousePosition = usable.m_mousePosition;

        // Return the base handler's prescriptions.
        return canMerge;
      }

      void
      MouseEvent::initButton() {
        // Check whether the event concerns a mouse button at all.
        if (m_button == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_button->type != SDL_MOUSEBUTTONDOWN && m_button->type != SDL_MOUSEBUTTONUP) {
          error(
            std::string("Cannot create mouse event"),
            std::string("Button event has invalid type ") + std::to_string(static_cast<int>(m_button->type))
          );
        }

        Event::Type type = Event::Type::MouseButtonPress;
        if (m_button->type == SDL_MOUSEBUTTONUP) {
          type = Event::Type::MouseButtonRelease;
        }

        // We now need to handle double clicks. Basically the `SDL` indicates whether a
        // mouse button event corresponds to a double click through the `m_button->clicks`
        // variable: if its value is `1` it corresponds to a single click while if its
        // valud is `2` the event corresponds to a double click.
        // It has no influence regarding the type of the button action (i.e. pressed or
        // release): this means that we will actually receive to events indicating a double
        // click if we are not careful. One with a `SDL_MOUSEBUTTONDOWN` and one with a
        // valud of `SDL_MOUSEBUTTONUP`. We don't really want that and would rather create
        // a single `MouseDoubleClick` event upon releasing the button.
        // So at this point we will voluntarily set the type of the event to `None` if it
        // corresponds to a double click on `SDL_MOUSEBUTTONDOWN`.
        if (m_button->clicks > 1) {
          if (type == Event::Type::MouseButtonPress) {
            type = Event::Type::None;
          }
          else {
            type = Event::Type::MouseDoubleClick;
          }
        }

        setType(type);

        setSDLWinID(m_button->windowID);
      }

      void
      MouseEvent::initMotion() {
        // Check whether the event concerns a mouse motion at all.
        if (m_motion == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_motion->type != SDL_MOUSEMOTION) {
          error(
            std::string("Cannot create mouse event"),
            std::string("Motion event has invalid type ") + std::to_string(static_cast<int>(m_motion->type))
          );
        }

        // TODO: The `SDL_MouseMotionEvent` defines a `state` attribute which contains the
        // current buttons pressed. This allows to simply detect drag motion. We should also
        // probably assign the mouse button to detect which button is dragging.
        setType(Event::Type::MouseMove);

        setSDLWinID(m_motion->windowID);
      }

      void
      MouseEvent::initWheel() {
        // Check whether the event concerns a mouse wheel at all.
        if (m_wheel == nullptr) {
          return;
        }

        // Check whether the event has a right type.
        if (m_wheel->type != SDL_MOUSEWHEEL) {
          error(
            std::string("Cannot create mouse event"),
            std::string("Wheel event has invalid type ") + std::to_string(static_cast<int>(m_wheel->type))
          );
        }

        setType(Event::Type::MouseWheel);

        setSDLWinID(m_wheel->windowID);
      }

    }
  }
}
