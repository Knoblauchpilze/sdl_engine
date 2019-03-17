#ifndef    COLOREDFONT_HH
# define   COLOREDFONT_HH

# include <memory>
# include <core_utils/CoreObject.hh>
# include "Font.hh"
# include "Color.hh"
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class ColoredFont: public utils::CoreObject {
        public:

          explicit
          ColoredFont(FontShPtr font,
                      const int& size,
                      const Color& color = Color::NamedColor::Black);

          virtual ~ColoredFont();

          void
          setSize(const int& size) noexcept;

          const Color&
          getColor() const noexcept;

          void
          setColor(const Color& color) noexcept;

          TextureShPtr
          render(const std::string& text,
                 const Texture::UUID& uuid,
                 SDL_Renderer* renderer);

        private:

          void
          clean() noexcept;

        private:

          FontShPtr m_font;
          int m_size;
          Color m_color;
          bool m_dirty;

          TextureShPtr m_text;

      };

      using ColoredFontShPtr = std::shared_ptr<ColoredFont>;
    }
  }
}

# include "ColoredFont.hxx"

#endif    /* COLOREDFONT_HH */
