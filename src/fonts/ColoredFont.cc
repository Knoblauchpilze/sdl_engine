
# include "ColoredFont.hh"

namespace sdl {
  namespace core {
    namespace engine {

      ColoredFont::ColoredFont(FontShPtr font,
                               const Palette& palette,
                               int size):
        utils::CoreObject(font->getName()),
        m_font(font),
        m_size(size),
        m_palette(palette),
        m_text()
      {
        setService(std::string("font"));
      }

      TextureShPtr
      ColoredFont::render(const std::string& text,
                          SDL_Renderer* renderer,
                          const Palette::ColorRole& role)
      {
        // Use the internal font to render the input text.
        SDL_Surface* textSurface = m_font->render(
          text,
          getSize(),
          getPalette().getColorForRole(role)
        );

        // Check whether the font successfully rendered the input `text`.
        if (textSurface == nullptr) {
          error(std::string("Could not render text \"") + text + "\"");
        }

        // Build and return a texture from this raw SDL texture pointer.
        return std::make_shared<SurfaceTexture>(renderer, role, textSurface);
      }

    }
  }
}
