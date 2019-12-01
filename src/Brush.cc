
# include "Brush.hh"
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Brush::Brush(const std::string& name):
        utils::CoreObject(name),

        m_color(Color::NamedColor::Black),
        m_clearColor(Color::NamedColor::White),

        m_canvas(nullptr)
      {
        setService("brush");
      }

      Brush::Brush(const std::string& name,
                   const utils::Sizef& size):
        Brush(name)
      {
        create(size, false);
      }

      TextureShPtr
      Brush::render(SDL_Renderer* renderer) {
        // In case no canvas is associated to this brush, nothing to do.
        if (!hasCanvas()) {
          return nullptr;
        }

        // Create a texture from the internal canvas using the provided renderer.
        return std::make_shared<SurfaceTexture>(
          renderer,
          m_canvas,
          getDefaultTextureRole(),
          false
        );
      }

    }
  }
}
