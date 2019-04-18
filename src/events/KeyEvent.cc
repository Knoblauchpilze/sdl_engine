
# include "KeyEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      KeyEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
