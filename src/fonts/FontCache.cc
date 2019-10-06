
# include "FontCache.hh"

namespace sdl {
  namespace core {
    namespace engine {

      FontCache::FontCache(TTF_Font* font):
        utils::CoreObject("font_cache"),

        m_font(font),
        m_glyphs()
      {
        // Check that the font is valid.
        if (m_font == nullptr) {
          error(
            std::string("Cannot create font cache from font"),
            std::string("Invalid null font")
          );
        }
      }

      SDL_Surface*
      FontCache::render(const std::string& text,
                        const Color& color)
      {
        // TODO: To fix some issues with positionning we should probably use some sort
        // of custom rendering where we only render a glyph rather than the full text
        // and then perform the blit of each individual glyph surface to the general
        // canvas. This is much less simple but could maybe solve the issues with the
        // position of the text.

        // Traverse the input text and render each needed glyph while advancing on the
        // output surface which allows to position the glyphs next to each other.
        
      }

      utils::Sizef
      FontCache::querySize(const std::string& text,
                           bool exact)
      {

        // Use the glyph size of each individual character of the input string
        // to determine the size of the text. Depending on the value of the
        // `exact` boolean we will either add only the size of the characters
        // encountered or the advance size in total.
        int gMinY = std::numeric_limits<int>::max();
        int gMaxY = std::numeric_limits<int>::lowest();

        int accumulatedW = 0;

        for (unsigned id = 0u ; id < text.size() ; ++id) {
          // Check whether this character is part of the font.
          if (!TTF_GlyphIsProvided(m_font, text[id])) {
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
          int success = TTF_GlyphMetrics(m_font, text[id], &minX, &maxX, &minY, &maxY, &advance);

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

      FontCache::GlyphPtr
      FontCache::renderGlyph(char c,
                             const Color& color)
      {
        // Check whether the input character has already been loaded in the cache.
        Glyphs::const_iterator it = m_glyphs.cend();

        if (it != m_glyphs.cend()) {
          // Return the cached version of the glyph.
          return it->second;
        }

        // The glyph does not exist yet, create it and register it to the cache.
        SDL_Surface* glyph = TTF_RenderGlyph_Blended(m_font, c, color.toSDLColor());
        if (glyph == nullptr) {
          error(
            std::string("Could not render glyph \"") + c + "\"",
            TTF_GetError()
          );
        }

        m_glyphs[c] = glyph;

        return glyph;
      }

    }
  }
}
