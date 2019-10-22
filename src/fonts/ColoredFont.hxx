#ifndef    COLOREDFONT_HXX
# define   COLOREDFONT_HXX

# include "ColoredFont.hh"
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      ColoredFont::~ColoredFont() {}

      inline
      int
      ColoredFont::getSize() const noexcept {
        return m_size;
      }

      inline
      void
      ColoredFont::setSize(int size) noexcept {
        m_size = size;
      }

      inline
      const Palette&
      ColoredFont::getPalette() const noexcept {
        return m_palette;
      }

      inline
      void
      ColoredFont::setPalette(const Palette& palette) noexcept {
        m_palette = palette;
      }

      inline
      utils::Sizef
      ColoredFont::querySize(const std::string& text,
                             bool exact)
      {
        return m_font->querySize(text, getSize(), exact);
      }

    }
  }
}

#endif    /* COLOREDFONT_HXX */
