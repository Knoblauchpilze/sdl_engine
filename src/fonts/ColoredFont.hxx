#ifndef    COLOREDFONT_HXX
# define   COLOREDFONT_HXX

# include "ColoredFont.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      ColoredFont::ColoredFont(FontShPtr font,
                               const int& size,
                               const Color& color):
        utils::CoreObject(font->getName()),
        m_font(font),
        m_size(size),
        m_color(color),
        m_dirty(true),

        m_texText(),
        m_text(nullptr)
      {
        setService(std::string("font"));
      }

      inline
      ColoredFont::~ColoredFont() {
        clean();
      }

      inline
      void
      ColoredFont::setSize(const int& size) noexcept {
        m_size = size;
        m_dirty = true;
      }

      inline
      const Color&
      ColoredFont::getColor() const noexcept {
        return m_color;
      }

      inline
      void
      ColoredFont::setColor(const Color& color) noexcept {
        m_color = color;
        m_dirty = true;
      }

      inline
      TextureShPtr
      ColoredFont::render(const std::string& text,
                          SDL_Renderer* renderer)
      {
        // Render the text only if the font has been modified in any way.
        if (m_dirty || m_texText.compare(text) != 0) {

          // Clean the texture if needed.
          clean();

          // Render the input text using the internal font.
          SDL_Texture* textTex = m_font->render(text, m_size, renderer, m_color);
          if (textTex == nullptr) {
            error(std::string("Could not render text \"") + text + "\"");
          }

          // Build a texture from this raw SDL texture pointer.
          m_text = std::make_shared<Texture>(textTex);

          // The texture has been cached for furhter usage.
          m_dirty = false;
          m_texText = text;
        }

        // Return the internal texture.
        return m_text;
      }

      inline
      void
      ColoredFont::clean() noexcept {
        if (m_text != nullptr) {
          m_text.reset();
        }
      }

    }
  }
}

#endif    /* COLOREDFONT_HXX */
