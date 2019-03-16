
# include "EngineLocator.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Engine* EngineLocator::m_engine = nullptr;
      NullEngine EngineLocator::sk_nullEngine;

    }
  }
}
