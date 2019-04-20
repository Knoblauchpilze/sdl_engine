
# include "ResizeEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      ResizeEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
