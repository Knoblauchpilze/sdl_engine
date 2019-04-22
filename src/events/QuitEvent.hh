#ifndef    QUIT_EVENT_HH
# define   QUIT_EVENT_HH

# include "Event.hh"
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      class QuitEvent: public Event {
        public:

          QuitEvent();

          QuitEvent(const SDL_QuitEvent& event);

          ~QuitEvent();

          void
          populateFromEngineData(Engine& engine) override;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          void
          init();

        private:

          SDL_QuitEvent m_quit;

      };

    }
  }
}

# include "QuitEvent.hxx"

#endif    /* QUIT_EVENT_HH */
