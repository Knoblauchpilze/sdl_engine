
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
                   int size,
                   const Color& color)
      {
        // Load the font if needed.
        FontCacheShPtr font = loadForSize(size);

        // Proceed to rendering.
        return font->render(text, color);
      }

      utils::Sizef
      Font::querySize(const std::string& text,
                      int size,
                      bool exact)
      {
        // Retrieve the font with the specified size.
        FontCacheShPtr font = loadForSize(size);

        // Use it to determine the size of the text.
        return font->querySize(text, exact);
      }

      inline
      FontCacheShPtr
      Font::loadForSize(int size) {
        // Acquire the lock to prevent concurrent addition of fonts.
        std::lock_guard<std::mutex> guard(*m_cacheLocker);

        // Check whether the font for the input `size` already exists in the local cache.
        const std::unordered_map<int, FontCacheShPtr>::const_iterator fontIt = m_fonts.find(size);
        if (fontIt != m_fonts.cend()) {
          return fontIt->second;
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

        // Disable kerning.
        TTF_SetFontKerning(newFont, 0);

        // Create the font cache associated with this font.
        FontCacheShPtr font = std::make_shared<FontCache>(getName(), newFont);

        // Add this font to the cache.
        m_fonts[size] = font;

        // Return the loaded font.
        return font;
      }

    }
  }
}
