
# include "Brush.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Brush::Brush(const std::string& name):
        utils::CoreObject(name)
      {
        setService("brush");
      }

      TextureShPtr
      Brush::render(SDL_Renderer* /*renderer*/) {
        return nullptr;
      }

    }
  }
}
