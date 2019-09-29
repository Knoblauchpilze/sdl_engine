#ifndef    FONT_HH
# define   FONT_HH

# include <mutex>
# include <string>
# include <memory>
# include <unordered_map>
# include <SDL2/SDL_ttf.h>
# include <maths_utils/Size.hh>
# include <core_utils/CoreObject.hh>
# include "Color.hh"

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
           * @return - the size of the text if it were to be rendered with this
           *           font.
           */
          utils::Sizef
          querySize(const std::string& text,
                    const int size);

        private:

          TTF_Font*
          loadForSize(const int& size);

          void
          unloadAll();

        private:

          std::shared_ptr<std::mutex> m_cacheLocker;
          std::unordered_map<int, TTF_Font*> m_fonts;

      };

      using FontShPtr = std::shared_ptr<Font>;
    }
  }
}

# include "Font.hxx"

#endif    /* FONT_HH */
