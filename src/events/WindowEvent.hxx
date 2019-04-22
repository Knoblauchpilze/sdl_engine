#ifndef    WINDOW_EVENT_HXX
# define   WINDOW_EVENT_HXX

# include "WindowEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      WindowEvent::WindowEvent(const SDL_WindowEvent& event):
        Event(Event::Type::None, nullptr, std::string("window_event_") + std::to_string(event.windowID)),
        m_window(event),
        m_winID()
      {
        init();
      }

      inline
      WindowEvent::~WindowEvent() {}

      inline
      float
      WindowEvent::getWidth() const noexcept {
        if (getType() == Event::Type::WindowResize) {
          return 1.0f * m_window.data1;
        }

        return 0.0f;
      }

      inline
      float
      WindowEvent::getHeight() const noexcept {
        if (getType() == Event::Type::WindowResize) {
          return 1.0f * m_window.data2;
        }

        return 0.0f;
      }

      inline
      std::uint32_t
      WindowEvent::getSDLWinID() const noexcept {
        return m_window.windowID;
      }

      inline
      const utils::Uuid&
      WindowEvent::getWindID() const noexcept {
        return m_winID;
      }

      inline
      void
      WindowEvent::setWindowID(const utils::Uuid& uuid) noexcept {
        m_winID = uuid;
      }

      inline
      bool
      WindowEvent::equal(const Event& other) const noexcept {
        const WindowEvent& e = dynamic_cast<const WindowEvent&>(other);
        return Event::equal(other) && getWindID() == e.getWindID() && getSDLWinID() == e.getSDLWinID();
      }

      inline
      void
      WindowEvent::init() {
        // Check whether the event has a right type.
        if (m_window.type != SDL_WINDOWEVENT) {
          error(std::string("Cannot create window event from invalid type ") + std::to_string(static_cast<int>(m_window.type)));
        }

        Event::Type type = Event::Type::None;
        switch (m_window.event) {
          case SDL_WINDOWEVENT_LEAVE:
            type = Event::Type::WindowEnter;
            break;
          case SDL_WINDOWEVENT_ENTER:
            type = Event::Type::WindowLeave;
            break;
          case SDL_WINDOWEVENT_RESIZED:
            type = Event::Type::WindowResize;
            break;
          default:
            // Not handled event for now.
            break;
        }

        setType(type);
      }

    }
  }
}

#endif    /* WINDOW_EVENT_HXX */
