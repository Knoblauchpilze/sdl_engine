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

          virtual ~ColoredFont();

          void
          setSize(const int& size) noexcept;

          const Palette&
          getPalette() const noexcept;

          void
          setPalette(const Palette& palette) noexcept;

          TextureShPtr
          render(const std::string& text,
                 SDL_Renderer* renderer);

        private:

          void
          clean() noexcept;

        private:

          FontShPtr m_font;
          int m_size;
          Palette m_palette;
          bool m_dirty;

          std::string m_texText;
          TextureShPtr m_text;

      };

      using ColoredFontShPtr = std::shared_ptr<ColoredFont>;
    }
  }
}

# include "ColoredFont.hxx"

#endif    /* COLOREDFONT_HH */
