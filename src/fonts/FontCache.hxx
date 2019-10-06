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
          clearGlyph(glyph->second);

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

    }
  }
}

#endif    /* FONT_CACHE_HXX */
