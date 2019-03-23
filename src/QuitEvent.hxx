#ifndef    QUIT_EVENT_HXX
# define   QUIT_EVENT_HXX

# include "QuitEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      QuitEvent::QuitEvent(const SDL_QuitEvent& event):
        Event(Event::Type::None, std::string("quit_event")),
        m_quit(event)
      {
        init();
      }

      inline
      QuitEvent::~QuitEvent() {}

      inline
      void
      QuitEvent::init() {
        // Check whether the event has a right type.
        if (m_quit.type != SDL_QUIT) {
          error(std::string("Cannot create quit event from invalid type ") + std::to_string(static_cast<int>(m_quit.type)));
        }

        setType(Event::Type::Quit);
      }

    }
  }
}

#endif    /* QUIT_EVENT_HXX */
