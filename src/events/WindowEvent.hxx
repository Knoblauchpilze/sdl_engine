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

    }
  }
}

#endif    /* WINDOW_EVENT_HXX */
