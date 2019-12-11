
# include "Brush.hh"
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Brush::Brush(const std::string& name,
                   bool ownsTexture):
        utils::CoreObject(name),

        m_color(Color::NamedColor::Black),
        m_clearColor(Color::NamedColor::White),

        m_canvas(nullptr),
        m_ownsCanvas(ownsTexture)
      {
        setService("brush");
      }

      Brush::Brush(const std::string& name,
                   const utils::Sizef& size,
                   bool ownsTexture):
        Brush(name, ownsTexture)
      {
        create(size, false);
      }

      void
      Brush::createFromRaw(const utils::Sizei& dims,
                           const std::vector<Color>& colors)
      {
        // Erase any existing canvas.
        destroy();

        // Transform the input colors array into a raw array.
        // The input array is composed of 4 channels each one
        // having 4 bytes.
        const unsigned channelCount = 4u;
        const unsigned depth = channelCount * sizeof(std::uint8_t) * 8u;
        const unsigned pitch = dims.w() * channelCount;
        const unsigned total = dims.w() * dims.h();
        const std::uint32_t format = SDL_PIXELFORMAT_RGBA32;

        std::vector<std::uint8_t> raw(channelCount * total, 0u);

        for (unsigned id = 0u ; id < total ; ++id) {
          raw[channelCount * id + 0u] = colors[id].rU();
          raw[channelCount * id + 1u] = colors[id].gU();
          raw[channelCount * id + 2u] = colors[id].bU();
          raw[channelCount * id + 3u] = colors[id].aU();
        }

        // Create the canvas with the requested dimensions. We
        // use a dedicated method allowing to create the surface
        // directly from the raw data.
        m_canvas = SDL_CreateRGBSurfaceWithFormatFrom(raw.data(), dims.w(), dims.h(), depth, pitch, format);

        if (m_canvas == nullptr) {
          error(
            std::string("Could not create canvas with from raw data with size ") + dims.toString(),
            SDL_GetError()
          );
        }
      }

      void
      Brush::drawLine(const Direction& dir,
                      float coord)
      {
        // Check consistency.
        if (!hasCanvas()) {
          error(
            std::string("Cannot draw line at ") + std::to_string(coord),
            std::string("No active canvas")
          );
        }

        // Create the surface to draw.
        int w = m_canvas->w, h = m_canvas->h;
        switch (dir) {
          case Direction::Horizontal:
            w = m_canvas->w;
            h = 1;
            break;
          case Direction::Vertical:
            w = 1;
            h = m_canvas->h;
            break;
          default:
            error(
              std::string("Cannot draw line at ") + std::to_string(coord),
              std::string("Invalid direction ") + std::to_string(static_cast<int>(dir))
            );
            break;
        }

        SDL_Surface* line = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        if (line == nullptr) {
          error(
            std::string("Cannot draw line at ") + std::to_string(coord),
            SDL_GetError()
          );
        }

        // Fill the surface with the adequate color.
        SDL_Color c = m_color.toSDLColor();
        SDL_FillRect(line, nullptr, SDL_MapRGBA(m_canvas->format, c.r, c.g, c.b, c.a));

        // Display the line at the correct coordinates.
        int x, y;
        switch (dir) {
          case Direction::Horizontal:
            x = 0;
            // Account for a `-1` as the `y` axis is inverted and the rows of the
            // surface range from `[0 ; m_canvas->h - 1]` and not `[1; m_canvas->h]`.
            y = static_cast<int>(m_canvas->h / 2.0f - coord) - 1;
            break;
          case Direction::Vertical:
          default:
            // This is not needed here because the `x` axis is not inverted.
            x = static_cast<int>(coord + m_canvas->w / 2.0f);
            y = 0;
            break;
        }
        SDL_Rect dst{x, y, w, h};

        SDL_BlitSurface(line, nullptr, m_canvas, &dst);

        // Release resources.
        SDL_FreeSurface(line);
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

        // Sample the gradient with as many samples as the width of
        // the canvas.
        for (int id = 0 ; id < m_canvas->w ; ++id) {
          float perc = 1.0f * id / m_canvas->w;
          float coord = 1.0f * id - m_canvas->w / 2.0f;

          setColor(grad.getColorAt(perc));
          drawLine(Direction::Vertical, coord);
        }
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
          !m_ownsCanvas
        );
      }

    }
  }
}
