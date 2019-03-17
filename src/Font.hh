#ifndef    FONT_HH
# define   FONT_HH

# include <memory>
# include <unordered_map>
# include <SDL2/SDL_ttf.h>
# include <core_utils/CoreObject.hh>
# include "Color.hh"
# include "Texture.hh"

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

          SDL_Texture*
          render(const std::string& text,
                 const int& size,
                 SDL_Renderer* renderer,
                 const Color& color = Color::NamedColor::Black);

        private:

          TTF_Font*
          loadForSize(const int& size);

          void
          unloadAll();

        private:

          std::string m_name;
          std::unordered_map<int, TTF_Font*> m_fonts;

      };

      using FontShPtr = std::shared_ptr<Font>;
    }
  }
}

# include "Font.hxx"

#endif    /* FONT_HH */
