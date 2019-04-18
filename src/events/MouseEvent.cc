
# include "MouseEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      MouseEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
