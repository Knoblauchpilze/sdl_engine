
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Font::Font(const std::string& name):
        utils::CoreObject(name),
        m_cacheLocker(std::make_shared<std::mutex>()),
        m_fonts()
      {
        setService(std::string("font"));
      }

      Font::Font(const Font& other):
        utils::CoreObject(other.getName()),
        m_cacheLocker(other.m_cacheLocker),
        m_fonts(other.m_fonts)
      {
        setService(std::string("font"));
      }

      SDL_Surface*
      Font::render(const std::string& text,
                   const int& size,
                   const Color& color)
      {
        // Load the font if needed.
        TTF_Font* font = loadForSize(size);
        if (font == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            std::string("Could not load font \"") + getName() + "\" for size " + std::to_string(size)
          );
        }

        // Proceed to rendering.
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color.toSDLColor());
        if (textSurface == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\"",
            TTF_GetError()
          );
        }

        return textSurface;
      }

      utils::Sizef
      Font::querySize(const std::string& text,
                      const int size)
      {
        // Retrieve the font with the specified size.
        TTF_Font* font = loadForSize(size);
        if (font == nullptr) {
          error(
            std::string("Could not query size for text \"") + text + "\"",
            std::string("Could not load font \"") + getName() + "\" for size " + std::to_string(size)
          );
        }

        int wTxt = 0, hTxt = 0;
        int status = TTF_SizeText(font, text.c_str(), &wTxt, &hTxt);

        if (status != 0) {
          error(
            std::string("Caught error while querying size of text \"") + text + "\" with font \"" + getName() + "\"",
            TTF_GetError()
          );
        }

        return utils::Sizef(1.0f * wTxt, 1.0f * hTxt);
      }

      inline
      TTF_Font*
      Font::loadForSize(const int& size) {
        // Acquire the lock to prevent concurrent addition of fonts.
        std::lock_guard<std::mutex> guard(*m_cacheLocker);

        // Check whether the font for the input `size` already exists in the local cache.
        const std::unordered_map<int, TTF_Font*>::const_iterator font = m_fonts.find(size);
        if (font != m_fonts.cend()) {
          return font->second;
        }

        // The font for this `size` is not loaded yet: create it.
        TTF_Font* newFont = TTF_OpenFont(getName().c_str(), size);

        // Check that we could effectively load the font.
        if (newFont == nullptr) {
          error(
            std::string("Could not load font \"") + getName() + "\" with size " + std::to_string(size),
            TTF_GetError()
          );
        }

        // Add this font to the cache.
        m_fonts[size] = newFont;

        // Return the loaded font.
        return newFont;
      }

    }
  }
}
