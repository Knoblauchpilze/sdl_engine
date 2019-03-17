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
      SDL_Texture*
      Font::render(const std::string& text,
                   const int& size,
                   SDL_Renderer* renderer,
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

        // Now convert the surface to a valid texture.
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
        
        // Release the resources used by the surface.
        SDL_FreeSurface(textSurface);

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from surface for text \"") + text + "\"",
            std::string("") + SDL_GetError()
          );
        }

        return tex;
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
