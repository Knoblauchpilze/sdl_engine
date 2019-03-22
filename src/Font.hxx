#ifndef    FONT_HXX
# define   FONT_HXX

# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Font::~Font() {
        unloadAll();
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
