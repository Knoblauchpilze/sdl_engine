
# include "Event.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      Event::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
