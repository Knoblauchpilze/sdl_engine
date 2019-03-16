#ifndef    ENGINE_LOCATOR_HXX
# define   ENGINE_LOCATOR_HXX

# include "EngineLocator.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      void
      EngineLocator::initialize() {
        m_engine = &sk_nullEngine;
      }

      inline
      Engine&
      EngineLocator::getEngine() {
        return *m_engine;
      }

      inline
      void
      EngineLocator::provide(Engine* engine) {
        if (engine == nullptr) {
          // Revert to null service.
          m_engine = &sk_nullEngine;
        }
        else {
          m_engine = engine;
        }
      }

    }
  }
}

#endif    /* ENGINE_LOCATOR_HXX */
