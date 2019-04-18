#ifndef    WINDOW_EVENT_HH
# define   WINDOW_EVENT_HH

# include "Event.hh"
# include <cstdint>
# include <SDL2/SDL.h>
# include <core_utils/Uuid.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class WindowEvent: public Event {
        public:

          WindowEvent(const SDL_WindowEvent& event);

          ~WindowEvent();

          void
          populateFromEngineData(Engine& engine) override;

          float
          getWidth() const noexcept;

          float
          getHeight() const noexcept;

          std::uint32_t
          getSDLWinID() const noexcept;

          const utils::Uuid&
          getWindID() const noexcept;

          void
          setWindowID(const utils::Uuid& uuid) noexcept;

        private:

          void
          init();

        private:

          SDL_WindowEvent m_window;
          utils::Uuid m_winID;

      };

    }
  }
}

# include "WindowEvent.hxx"

#endif    /* WINDOW_EVENT_HH */
