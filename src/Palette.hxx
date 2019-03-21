#ifndef    PALETTE_HXX
# define   PALETTE_HXX

# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Palette::Palette():
        m_backgroundColor(engine::Color::NamedColor::Purple),
        m_foregroundColor(engine::Color::NamedColor::Black),
        m_hoverColor(engine::Color::NamedColor::Silver),
        m_selectionColor(engine::Color::NamedColor::White),
        m_highlightColor(engine::Color::NamedColor::Navy)
      {}

      inline
      void
      Palette::setBackgroundColor(const Color& color) {
        m_backgroundColor = color;
      }

      inline
      void
      Palette::setForegroundColor(const Color& color) {
        m_foregroundColor = color;
      }

      inline
      void
      Palette::setHoverColor(const Color& color) {
        m_hoverColor = color;
      }

      inline
      void
      Palette::setSelectionColor(const Color& color) {
        m_selectionColor = color;
      }

      inline
      void
      Palette::setHighlightColor(const Color& color) {
        m_highlightColor = color;
      }

      inline
      Color
      Palette::getActiveColor() const noexcept {
        // TODO: Actually handle active color.
        return m_backgroundColor;
      }

    }
  }
}

#endif    /* PALETTE_HXX */
