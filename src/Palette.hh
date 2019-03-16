#ifndef    PALETTE_HH
# define   PALETTE_HH

# include <memory>
# include <sdl_engine/Color.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Palette {
        public:

          Palette();

          ~Palette() = default;

          void
          setBackgroundColor(const Color& color);

          void
          setForegroundColor(const Color& color);

          void
          setHoverColor(const Color& color);

          void
          setSelectionColor(const Color& color);

          void
          setHighlightColor(const Color& color);

          static
          Palette
          fromBackgroundColor(const Color& color) noexcept;

        private:

          // A color to represent an elements in its default state.
          Color m_backgroundColor;

          // A color to represent an element and distinguigh it from the
          // `m_backgroundColor`.
          Color m_foregroundColor;

          // A color to use when an element is hovered.
          Color m_hoverColor;

          // A color to use when an element is selected.
          Color m_selectionColor;

          // A color used to represent an element and distinguish it from the
          // `m_hoverColor` or `m_selectionColor`.
          Color m_highlightColor;

      };

      using PaletteShPtr = std::shared_ptr<Palette>;
    }
  }
}

# include "Palette.hxx"

#endif    /* PALETTE_HH */
