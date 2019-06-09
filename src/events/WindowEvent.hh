#ifndef    WINDOW_EVENT_HH
# define   WINDOW_EVENT_HH

# include "Event.hh"
# include <cstdint>
# include <SDL2/SDL.h>
# include <maths_utils/Size.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class WindowEvent: public Event {
        public:

          WindowEvent(const SDL_WindowEvent& event);

          ~WindowEvent();

          void
          populateFromEngineData(Engine& engine) override;

          utils::Sizef
          getSize() const noexcept;

          void
          setSize(const utils::Sizef& size) noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          void
          init();

        private:

          SDL_WindowEvent m_window;
          utils::Sizef m_size;

      };

    }
  }
}

# include "WindowEvent.hxx"

#endif    /* WINDOW_EVENT_HH */
