
# include "EventListener.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EventListener::EventListener(const std::string& name):
        utils::CoreObject(name),
        m_filters()
      {}

    }
  }
}
