#ifndef    NULL_ENGINE_HH
# define   NULL_ENGINE_HH

# include <string>

# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class NullEngine : public Engine {
        public:
      };

    }
  }
}

# include "NullEngine.hxx"

#endif    /* NULL_ENGINE_HH */
