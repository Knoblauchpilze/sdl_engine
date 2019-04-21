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
      const int&
      ColoredFont::getSize() const noexcept {
        return m_size;
      }

      inline
      void
      ColoredFont::setSize(const int& size) noexcept {
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

    }
  }
}

#endif    /* COLOREDFONT_HXX */
