#ifndef    COLOREDFONT_HH
# define   COLOREDFONT_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include "Font.hh"
# include "Palette.hh"
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class ColoredFont: public utils::CoreObject {
        public:

          explicit
          ColoredFont(FontShPtr font,
                      const Palette& palette,
                      const int& size);

          ~ColoredFont();

          const int&
          getSize() const noexcept;

          void
          setSize(const int& size) noexcept;

          const Palette&
          getPalette() const noexcept;

          void
          setPalette(const Palette& palette) noexcept;

          TextureShPtr
          render(const std::string& text,
                 SDL_Renderer* renderer,
                 const Palette::ColorRole& role);

          /**
           * @brief - Used to retrieve the text that the input `text` would have
           *          if it was to be rendered with `this` font Note that no
           *          actual rendering is performed by this method.
           * @param text - the text to be rendered with this font.
           * @param exact - specifies whether the glyph metric should be used to
           *                determine the exact size of the text or if we can do
           *                as if the text was rendered instead.
           * @return - the size of the text if it were to be rendered with this
           *           font.
           */
          utils::Sizef
          querySize(const std::string& text,
                    bool exact);

        private:

        private:

          FontShPtr m_font;
          int m_size;
          Palette m_palette;

          std::string m_text;

      };

      using ColoredFontShPtr = std::shared_ptr<ColoredFont>;
    }
  }
}

# include "ColoredFont.hxx"

#endif    /* COLOREDFONT_HH */
