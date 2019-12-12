
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
        m_rawData(nullptr),
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
                           std::vector<Color>& colors)
      {
        // Erase any existing canvas.
        destroy();

        // Do not create a surface right away: rather keep the data
        // internally so that we can use it to create the surface
        // when needed.
        m_rawData = SurfaceTexture::createFromData(dims, colors);

        if (m_rawData == nullptr) {
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
        // Check for a valid canvas.
        if (hasCanvas()) {
          // If this brush owns the texture we shouldn't be transferring the
          // ownership to the texture and conversely.
          return std::make_shared<SurfaceTexture>(
            renderer,
            m_canvas,
            getDefaultTextureRole(),
            !m_ownsCanvas
          );
        }

        // Check for raw data.
        if (hasRawData()) {
          // The texture has the ownership of the data from now on.
          return std::make_shared<SurfaceTexture>(
            renderer,
            m_rawData
          );
        }

        // No known data, return an empty texture.
        log(
          std::string("Could not determine type of data held by brush"),
          utils::Level::Warning
        );

        return nullptr;
      }

    }
  }
}
