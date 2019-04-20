
# include "PaintEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      PaintEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
