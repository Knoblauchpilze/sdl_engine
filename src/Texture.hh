#ifndef    TEXTURE_HH
# define   TEXTURE_HH

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include <maths_utils/Box.hh>
# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Texture: public utils::CoreObject {
        public:

          using UUID = uint32_t;

        public:

          Texture(const UUID& uuid,
                  const utils::Sizei& size,
                  SDL_Renderer* renderer);

          Texture(const UUID& uuid,
                  const std::string& file,
                  SDL_Renderer* renderer);

          Texture(const UUID& uuid,
                  SDL_Texture* tex);

          ~Texture();

          const UUID&
          getUUID() const noexcept;

          SDL_Texture*
          operator()() const noexcept;

          void
          fill(SDL_Renderer* renderer,
               const Palette& palette);

          void
          draw(std::shared_ptr<Texture> tex,
               utils::Boxf* box,
               SDL_Renderer* renderer);

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

          UUID m_uuid;

          SDL_Texture* m_texture;
      };

      using TextureShPtr = std::shared_ptr<Texture>;
    }
  }
}

# include "Texture.hxx"

#endif    /* TEXTURE_HH */
