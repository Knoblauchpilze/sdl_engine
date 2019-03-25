
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Font::Font(const std::string& name):
        utils::CoreObject(name),
        m_fonts()
      {
        setService(std::string("font"));
      }

      Font::Font(const Font& other):
        utils::CoreObject(other.getName()),
        m_fonts(other.m_fonts)
      {
        // Nothing to do.
      }

      SDL_Texture*
      Font::render(const std::string& text,
                   const int& size,
                   SDL_Renderer* renderer,
                   const Color& color)
      {
        // Load the font if needed.
        TTF_Font* font = loadForSize(size);
        if (font == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("Could not load font for size ") + std::to_string(size)
          );
        }

        // Proceed to rendering.
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color.toSDLColor());
        if (textSurface == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("") + TTF_GetError()
          );
        }

        // Now convert the surface to a valid texture.
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
        
        // Release the resources used by the surface.
        SDL_FreeSurface(textSurface);

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from surface for text \"") + text + "\"",
            std::string("") + SDL_GetError()
          );
        }

        return tex;
      }

    }
  }
}
