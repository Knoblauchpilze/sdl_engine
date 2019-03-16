#ifndef    FONT_HXX
# define   FONT_HXX

# include <algorithm>
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Font::~Font() {
        unloadAll();
      }

      inline
      SDL_Surface*
      Font::render(const std::string& text,
                   const int& size,
                   const Color& color)
      {
        // Load the font if needed.
        TTF_Font* font = loadForSize(size);
        if (font == nullptr) {
          error(std::string("Could not render text \"") + text + "\", could not load font for size " + std::to_string(size));
        }

        // Proceed to rendering.

        // TODO: Transform to color ?
        SDL_Color sdlColor = SDL_Color{
          static_cast<uint8_t>(color.r() * 255.0f),
          static_cast<uint8_t>(color.g() * 255.0f),
          static_cast<uint8_t>(color.b() * 255.0f),
          static_cast<uint8_t>(color.a() * 255.0f)
        };

        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), sdlColor);
        if (textSurface == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("") + TTF_GetError()
          );
        }

        return textSurface;
      }

      inline
      TTF_Font*
      Font::loadForSize(const int& size) {
        // Check for already loaded font.
        const std::unordered_map<int, TTF_Font*>::const_iterator font = m_fonts.find(size);
        if (font != m_fonts.cend()) {
          return font->second;
        }

        // The font is not loaded yet.
        TTF_Font* newFont = TTF_OpenFont(getName().c_str(), size);

        // Check that we could effectively load the font.
        if (newFont == nullptr) {
          error(
            std::string("Could not load font with size ") + std::to_string(size),
            std::string("") + TTF_GetError()
          );
        }

        m_fonts[size] = newFont;

        return newFont;
      }

      inline
      void
      Font::unloadAll() {
        for (std::unordered_map<int, TTF_Font*>::iterator font = m_fonts.begin() ; font != m_fonts.end() ; ++font) {
          if (font->second != nullptr) {
            TTF_CloseFont(font->second);
          }
        }
        m_fonts.clear();
      }

    }
  }
}

#endif    /* FONT_HXX */
