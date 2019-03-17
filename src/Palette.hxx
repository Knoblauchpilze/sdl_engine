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

      inline
      Palette
      Palette::fromBackgroundColor(const engine::Color& color) noexcept {
        Palette palette;

        // Assign the background color as desired by the input argument.
        palette.m_backgroundColor = color;

        // The foreground color is white if the brightness of the background
        // color is small enough, or black otherwise.
        palette.m_foregroundColor = Color::NamedColor::White;
        if (palette.m_backgroundColor.brightness() > 0.5f) {
          palette.m_foregroundColor = Color::NamedColor::Black;
        }

        // The highlight color is hard-coded for now whatever the background
        // color which might lead to some aberrations.
        // TODO: Fix this.
        palette.m_hoverColor = Color::NamedColor::CorneFlowerBlue;

        // The selection color is equal to the hover color.
        palette.m_selectionColor = palette.m_hoverColor;

        // The highlight color is hard-coded for now whatever the background
        // color which might lead to some aberrations.
        // TODO: Fix this.
        palette.m_highlightColor = Color::NamedColor::Purple;

        // Return the built-in palette.
        return palette;
      }

    }
  }
}

#endif    /* PALETTE_HXX */
