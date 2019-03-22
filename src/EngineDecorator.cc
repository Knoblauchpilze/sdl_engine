
# include "EngineDecorator.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EngineDecorator::EngineDecorator(core::engine::EngineShPtr engine,
                                      const std::string& name):
        utils::CoreObject(name),
        m_engine(nullptr)
      {
        setService(std::string("decorator"));

        setEngine(engine);
      }

      EngineDecorator::~EngineDecorator() {}

      void
      EngineDecorator::setEngine(EngineShPtr engine) {
        // Check for null engine.
        if (engine == nullptr) {
          error(std::string("Cannot assign null engine to decorator"));
        }

        // Set the new engine.
        m_engine = engine;
      }

    }
  }
}

