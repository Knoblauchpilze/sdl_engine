#ifndef    ENGINE_HXX
# define   ENGINE_HXX

# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      void
      Engine::populateEvent(Event& /*event*/) {
        // Empty implementation.
      }

      inline
      void
      Engine::populateEvent(EnterEvent& /*event*/) {
        // Empty implementation.
      }

      inline
      void
      Engine::populateEvent(KeyEvent& /*event*/) {
        // Empty implementation.
      }

      inline
      void
      Engine::populateEvent(MouseEvent& /*event*/) {
        // Empty implementation.
      }

      inline
      void
      Engine::populateEvent(QuitEvent& /*event*/) {
        // Empty implementation.
      }

      inline
      void
      Engine::populateEvent(WindowEvent& /*event*/) {
        // Empty implementation.
      }

    }
  }
}

#endif    /* ENGINE_HXX */
