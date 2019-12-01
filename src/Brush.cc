
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

      void
      Brush::drawLine(const Direction& /*dir*/,
                      float coord)
      {
        // Check consistency.
        if (!hasCanvas()) {
          error(
            std::string("Cannot draw line at ") + std::to_string(coord),
            std::string("No active canvas")
          );
        }

        // TODO: Draw the line.
      }

      void
      Brush::drawGradient(const Gradient& grad) {
        // Check consistency.
        if (!hasCanvas()) {
          error(
            std::string("Cannot draw gradient ") + grad.getName(),
            std::string("No active canvas")
          );
        }

        // TODO: Draw gradient.
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
