#ifndef    ENGINE_LOCATOR_HH
# define   ENGINE_LOCATOR_HH

# include <string>
# include "Engine.hh"
# include "NullEngine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Engine;

      class EngineLocator {
        public:

          static
          void
          initialize();

          static
          Engine&
          getEngine();

          static
          void
          provide(Engine* engine);

        private:
      
          static Engine* m_engine;
          static NullEngine sk_nullEngine;
      };

    }
  }
}

# include "EngineLocator.hxx"

#endif    /* ENGINE_LOCATOR_HH */
