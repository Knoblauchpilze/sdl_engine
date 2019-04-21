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

          ~Texture();

          SDL_Texture*
          operator()();

          const Palette::ColorRole&
          getRole() const noexcept;

          void
          fill(const Palette& palette);

          void
          draw(utils::Boxf* box,
               SDL_Texture* on = nullptr);

          void
          setAlpha(const Color& color);

          void
          setRole(const Palette::ColorRole& role);

          utils::Sizei
          query();

        protected:

          enum class Type {
            Basic,
            Image,
            Surface
          };

          Texture(SDL_Renderer* renderer,
                  const Palette::ColorRole& role,
                  const Type& type);

          SDL_Renderer*
          getRenderer() const noexcept;

          bool
          valid() const noexcept;

          virtual SDL_Texture*
          create() = 0;

        private:

          void
          clean();

          /**
           * @brief - Used to automatically performs a check by calling `valid` and
           *          launch the texture's creation if the return value is false.
           *          Avoid to wrap `if (valid()) { create(); }` everywhere in the
           *          code.
           */
          void
          createOnce();

        private:

          SDL_Renderer* m_renderer;
          Palette::ColorRole m_role;
          Type m_type;
          SDL_Texture* m_texture;
      };

      using TextureShPtr = std::shared_ptr<Texture>;
    }
  }
}

# include "Texture.hxx"

#endif    /* TEXTURE_HH */
