#ifndef    WINDOW_EVENT_HXX
# define   WINDOW_EVENT_HXX

# include "WindowEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      WindowEvent::WindowEvent(const SDL_WindowEvent& event):
        Event(Event::Type::None, nullptr, std::string("window_event_") + std::to_string(event.windowID)),
        m_window(event)
      {
        init();
      }

      inline
      WindowEvent::~WindowEvent() {}

      inline
      utils::Sizef
      WindowEvent::getSize() const noexcept {
        return m_size;
      }

      inline
      void
      WindowEvent::setSize(const utils::Sizef& size) noexcept {
        m_size = size;
      }

      inline
      bool
      WindowEvent::equal(const Event& other) const noexcept {
        return Event::equal(other);
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
            type = Event::Type::WindowLeave;
            break;
          case SDL_WINDOWEVENT_ENTER:
            type = Event::Type::WindowEnter;
            break;
          case SDL_WINDOWEVENT_RESIZED:
            type = Event::Type::WindowResize;
            break;
          case SDL_WINDOWEVENT_MAXIMIZED:
            type = Event::Type::WindowResize;
            break;
          default:
            // Not handled event for now.
            break;
        }

        // Assign the size from the input event if any.
        if (type == Event::Type::WindowResize) {
          m_size = utils::Sizef(
            m_window.data1,
            m_window.data2
          );
        }

        setType(type);

        setSDLWinID(m_window.windowID);
      }

    }
  }
}

#endif    /* WINDOW_EVENT_HXX */
