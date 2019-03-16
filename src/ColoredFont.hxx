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

        m_text(nullptr)
      {
        setService(std::string("font"));
      }

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
      void
      ColoredFont::setColor(const Color& color) noexcept {
        m_color = color;
        m_dirty = true;
      }

      inline
      SDL_Texture*
      ColoredFont::render(SDL_Renderer* renderer, const std::string& text) {
        // Render the text only if the font has been modified in any way.
        // TODO: Note that we do not check that the rendered texture has
        // been rendered for the input text, so we might reuse a cached
        // texture for a different text.
        if (m_dirty) {

          // Clean the texture if needed.
          clean();

          // Render the input text for the 
          SDL_Surface* textAsSurface = m_font->render(text, m_size, m_color);
          if (textAsSurface == nullptr) {
            error(std::string("Could not render text \"") + text + "\"");
          }

          // Create a texture from this surface.
          m_text = SDL_CreateTextureFromSurface(renderer, textAsSurface);
          SDL_FreeSurface(textAsSurface);
          if (m_text == nullptr) {
            error(std::string("Could not create texture from surface for text \"") + text + "\"");
          }

          // Apply alpha value for the texture.
          SDL_SetTextureAlphaMod(m_text, m_color.a());

          // The texture has been cached for furhter usage.
          m_dirty = false;
        }

        // Return the internal texture.
        return m_text;
      }

      inline
      void
      ColoredFont::clean() noexcept {
        if (m_text != nullptr) {
          SDL_DestroyTexture(m_text);
        }
      }

    }
  }
}

#endif    /* COLOREDFONT_HXX */
