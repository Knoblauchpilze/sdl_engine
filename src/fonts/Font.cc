
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Font::Font(const std::string& name):
        utils::CoreObject(name),
        m_cacheLocker(std::make_shared<std::mutex>()),
        m_fonts()
      {
        setService(std::string("font"));
      }

      Font::Font(const Font& other):
        utils::CoreObject(other.getName()),
        m_cacheLocker(other.m_cacheLocker),
        m_fonts(other.m_fonts)
      {
        setService(std::string("font"));
      }

      SDL_Surface*
      Font::render(const std::string& text,
                   const int& size,
                   const Color& color)
      {
        // Load the font if needed.
        TTF_Font* font = loadForSize(size);

        // Proceed to rendering.
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color.toSDLColor());
        if (textSurface == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            TTF_GetError()
          );
        }

        return textSurface;
      }

      utils::Sizef
      Font::querySize(const std::string& text,
                      int size,
                      bool exact)
      {
        // Retrieve the font with the specified size.
        TTF_Font* font = loadForSize(size);

        // Use the glyph size of each individual character of the input string
        // to determine the size of the text. Depending on the value of the
        // `exact` boolean we will either add only the size of the characters
        // encountered or the advance size in total.
        int gMinY = std::numeric_limits<int>::max();
        int gMaxY = std::numeric_limits<int>::lowest();

        int accumulatedW = 0;

        for (unsigned id = 0u ; id < text.size() ; ++id) {
          // Check whether this character is part of the font.
          if (!TTF_GlyphIsProvided(font, text[id])) {
            log(
              std::string("Could not determine size of glyph '") + text[id] + "' (not found in font \"" + getName() + "\"",
              utils::Level::Warning
            );

            // The size will probably be inaccurate but what can we do ?
            continue;
          }

          // Retrieve the needed metrics: the advance for this glyph and its height.
          int advance;
          int minX, maxX;
          int minY, maxY;
          int success = TTF_GlyphMetrics(font, text[id], &minX, &maxX, &minY, &maxY, &advance);

          if (success != 0) {
            log(
              std::string("Error while determining size of glyph ") + text[id] + " for font \"" + getName() + "\" " +
              "(err: \"" + TTF_GetError() + "\")",
              utils::Level::Warning
            );

            // Here as well we don't have other choice but to continue.
            continue;
          }

          // Accumulate the maximum extent in `y`.
          gMinY = std::min(gMinY, minY);
          gMaxY = std::max(gMaxY, maxY);

          // Accumulate the width of this glyph depending on whether the exact size
          // should be accumulated.
          accumulatedW += (exact ? maxX - minX : advance);
        }

        return utils::Sizef(1.0f * accumulatedW, 1.0f * (gMaxY - gMinY));
      }

      inline
      TTF_Font*
      Font::loadForSize(const int& size) {
        // Acquire the lock to prevent concurrent addition of fonts.
        std::lock_guard<std::mutex> guard(*m_cacheLocker);

        // Check whether the font for the input `size` already exists in the local cache.
        const std::unordered_map<int, TTF_Font*>::const_iterator font = m_fonts.find(size);
        if (font != m_fonts.cend()) {
          return font->second;
        }

        // The font for this `size` is not loaded yet: create it.
        TTF_Font* newFont = TTF_OpenFont(getName().c_str(), size);

        // Check that we could effectively load the font.
        if (newFont == nullptr) {
          error(
            std::string("Could not load font \"") + getName() + "\" with size " + std::to_string(size),
            TTF_GetError()
          );
        }

        // Disable kerning.
        TTF_SetFontKerning(newFont, 0);

        // Add this font to the cache.
        m_fonts[size] = newFont;

        // Return the loaded font.
        return newFont;
      }

    }
  }
}
