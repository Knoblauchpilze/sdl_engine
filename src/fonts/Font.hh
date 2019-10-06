#ifndef    FONT_HH
# define   FONT_HH

# include <mutex>
# include <string>
# include <memory>
# include <unordered_map>
# include <SDL2/SDL.h>
# include <maths_utils/Size.hh>
# include <core_utils/CoreObject.hh>
# include "Color.hh"
# include "FontCache.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Font: public utils::CoreObject {
        public:

          explicit
          Font(const std::string& name);

          explicit
          Font(const Font& other);

          virtual ~Font();

          SDL_Surface*
          render(const std::string& text,
                 const int& size,
                 const Color& color = Color::NamedColor::Black);

          /**
           * @brief - Used to retrieve the text that the input `text` would have
           *          if it was to be rendered with `this` font. Note that no
           *          actual rendering is performed by this method.
           * @param text - the text to be rendered with this font.
           * @param size - the size of the font to use.
           * @param exact - specifies whether the glyph metric should be used to
           *                determine the exact size of the text or if we can do
           *                as if the text was rendered instead.
           * @return - the size of the text if it were to be rendered with this
           *           font.
           */
          utils::Sizef
          querySize(const std::string& text,
                    int size,
                    bool exact);

        private:

          /**
           * @brief - Used to perform the loading of this font using the specified
           *          size. In case the font already exists we return it otherwise
           *          it is loaded from memory.
           *          Note that the font is loaded as a `FontCache` object which
           *          allows efficient management of the glyphs produced by the
           *          font.
           * @param size - the size with which the font should be loaded.
           */
          FontCacheShPtr
          loadForSize(const int& size);

          void
          unloadAll();

        private:

          std::shared_ptr<std::mutex> m_cacheLocker;
          std::unordered_map<int, FontCacheShPtr> m_fonts;

      };

      using FontShPtr = std::shared_ptr<Font>;
    }
  }
}

# include "Font.hxx"

#endif    /* FONT_HH */
