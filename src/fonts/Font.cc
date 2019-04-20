
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Font::Font(const std::string& name):
        utils::CoreObject(name),
        m_fonts()
      {
        setService(std::string("font"));
      }

      Font::Font(const Font& other):
        utils::CoreObject(other.getName()),
        m_fonts(other.m_fonts)
      {
        // Nothing to do.
      }

      SDL_Surface*
      Font::render(const std::string& text,
                   const int& size,
                   const Color& color)
      {
        // Load the font if needed.
        TTF_Font* font = loadForSize(size);
        if (font == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("Could not load font for size ") + std::to_string(size)
          );
        }

        // Proceed to rendering.
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color.toSDLColor());
        if (textSurface == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("") + TTF_GetError()
          );
        }

        return textSurface;
      }

    }
  }
}
