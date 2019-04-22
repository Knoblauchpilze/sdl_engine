#ifndef    KEY_EVENT_HH
# define   KEY_EVENT_HH

# include "Event.hh"
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      class KeyEvent: public Event {
        public:

          KeyEvent(const SDL_KeyboardEvent& event);

          ~KeyEvent();

          void
          populateFromEngineData(Engine& engine) override;

          int
          getKey() const noexcept;

          bool
          isPress() const noexcept;

          bool
          isRelease() const noexcept;

          bool
          isEscape() const noexcept;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          void
          init();

        private:

          SDL_KeyboardEvent m_key;

      };

    }
  }
}

# include "KeyEvent.hxx"

#endif    /* KEY_EVENT_HH */
