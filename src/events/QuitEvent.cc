
# include "QuitEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      QuitEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
