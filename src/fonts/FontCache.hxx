#ifndef    FONT_CACHE_HXX
# define   FONT_CACHE_HXX

# include "FontCache.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FontCache::~FontCache() {
        // Clear the content of the cache.
        clear();
      }

      inline
      void
      FontCache::clear() {
        // Clear all existing glyphs.
        while (!m_glyphs.empty()) {
          Glyphs::const_iterator glyph = m_glyphs.cbegin();

          // Clear the glyph.
          clearGlyph(glyph->second.tex);

          // Erase this iterator.
          m_glyphs.erase(glyph);
        }
      }

      inline
      void
      FontCache::clearGlyph(GlyphPtr glyph) const {
        // Release the memory used by the texture representing this glyph.
        SDL_FreeSurface(glyph);
      }

      inline
      bool
      FontCache::exists(char c) const noexcept {
        return TTF_GlyphIsProvided(m_font, c);
      }

      inline
      FontCache::FontMetrics
      FontCache::getMetrics() const noexcept {
        FontMetrics m{0, 0, 0};

        m.ascent = TTF_FontAscent(m_font);
        m.descent = TTF_FontDescent(m_font);

        m.height = TTF_FontHeight(m_font);

        return m;
      }

      inline
      FontCache::GlyphMetrics
      FontCache::getMetrics(char c) const noexcept {
        GlyphMetrics m{0, 0, 0, 0, 0};

        if (!exists(c)) {
          // The glyph does not exist, return default metrics.
          return m;
        }

        // Retrieve the metrics for this glyph.
        int failure = TTF_GlyphMetrics(m_font, c, &m.minX, &m.maxX, &m.minY, &m.maxY, &m.advance);

        // Check success.
        if (failure) {
          log(
            std::string("Error while determining size of glyph ") + c + " for font \"" + getName() + "\" " +
            "(err: \"" + TTF_GetError() + "\", status: " + std::to_string(failure) + ")",
            utils::Level::Warning
          );

          // Reset metrics.
          m = GlyphMetrics{0, 0, 0, 0, 0};
        }

        // Return the metrics.
        return m;
      }

      inline
      std::string
      FontCache::makeKey(char c,
                         const Color& color) noexcept
      {
        return std::string() +
          c +
          std::to_string(color.r()) +
          std::to_string(color.g()) +
          std::to_string(color.b()) +
          std::to_string(color.a())
        ;
      }

    }
  }
}

#endif    /* FONT_CACHE_HXX */
