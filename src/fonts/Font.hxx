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
        std::lock_guard<std::mutex> guard(*m_cacheLocker);

        // Release resources used by the internal cache table.
        for (std::unordered_map<int, TTF_Font*>::iterator font = m_fonts.begin() ; font != m_fonts.end() ; ++font) {
          if (font->second != nullptr) {
            TTF_CloseFont(font->second);
          }
        }

        // Clear the internal table.
        m_fonts.clear();
      }

    }
  }
}

#endif    /* FONT_HXX */
