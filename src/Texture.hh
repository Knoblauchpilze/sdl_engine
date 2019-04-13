#ifndef    TEXTURE_HH
# define   TEXTURE_HH

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include <maths_utils/Box.hh>
# include "Color.hh"
# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Texture: public utils::CoreObject {
        public:

          Texture(const utils::Sizei& size,
                  const Palette::ColorRole& role,
                  SDL_Renderer* renderer);

          Texture(const std::string& file,
                  const Palette::ColorRole& role,
                  SDL_Renderer* renderer);

          Texture(SDL_Texture* tex);

          ~Texture();

          SDL_Texture*
          operator()() const noexcept;

          void
          fill(SDL_Renderer* renderer,
               const Palette& palette);

          void
          draw(utils::Boxf* box,
               SDL_Renderer* renderer);

          void
          setAlpha(const Color& color);

          utils::Sizei
          query();

        private:

          void
          create(const utils::Sizei& size,
                 SDL_Renderer* renderer);

          void
          create(const std::string& file,
                 SDL_Renderer* renderer);

          void
          clean();

        private:

          Palette::ColorRole m_role;
          SDL_Texture* m_texture;
      };

      using TextureShPtr = std::shared_ptr<Texture>;
    }
  }
}

# include "Texture.hxx"

#endif    /* TEXTURE_HH */
