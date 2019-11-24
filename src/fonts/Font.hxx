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
      void
      Font::unloadAll() {
        // Acquire the lock to prevent concurrent addition of fonts.
        Guard guard(*m_cacheLocker);

        // Release resources used by the internal cache table.
        for (std::unordered_map<int, FontCacheShPtr>::iterator font = m_fonts.begin() ; font != m_fonts.end() ; ++font) {
          if (font->second != nullptr) {
            font->second->clear();
          }
        }

        // Clear the internal table.
        m_fonts.clear();
      }

    }
  }
}

#endif    /* FONT_HXX */
