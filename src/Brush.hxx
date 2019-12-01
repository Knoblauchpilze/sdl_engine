#ifndef    BRUSH_HXX
# define   BRUSH_HXX

# include "Brush.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Brush::~Brush() {
        destroy();
      }

      inline
      void
      Brush::setColor(const Color& color) noexcept {
        m_color = color;
      }

      inline
      void
      Brush::setClearColor(const Color& color) noexcept {
        m_clearColor = color;
      }

      inline
      void
      Brush::create(const utils::Sizef& size,
                    bool fill)
      {
        // Erase any existing canvas.
        destroy();

        // Create the canvas with the requested dimensions.
        int w = static_cast<int>(size.w());
        int h = static_cast<int>(size.h());

        m_canvas = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        if (m_canvas == nullptr) {
          error(
            std::string("Could not create canvas with size ") + size.toString(),
            SDL_GetError()
          );
        }

        // Perform a clear operation if needed.
        if (fill) {
          clear();
        }
      }

      inline
      void
      Brush::clear() noexcept {
        if (!hasCanvas()) {
          log(std::string("Trying to clear canvas without active one"), utils::Level::Warning);
          return;
        }

        SDL_Color c = m_clearColor.toSDLColor();
        SDL_FillRect(m_canvas, nullptr, SDL_MapRGBA(m_canvas->format, c.r, c.g, c.b, c.a));
      }

      inline
      Palette::ColorRole
      Brush::getDefaultTextureRole() noexcept {
        return Palette::ColorRole::Background;
      }

      inline
      bool
      Brush::hasCanvas() const noexcept {
        return m_canvas != nullptr;
      }

      inline
      void
      Brush::destroy() noexcept {
        if (hasCanvas()) {
          SDL_FreeSurface(m_canvas);
          m_canvas = nullptr;
        }
      }

    }
  }
}

#endif    /* BRUSH_HXX */
