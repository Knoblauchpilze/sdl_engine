
# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

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

