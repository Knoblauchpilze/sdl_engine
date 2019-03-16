#ifndef    TEXTURE_HH
# define   TEXTURE_HH

# include <memory>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>

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

          ~Texture();

          const UUID&
          getUUID() const noexcept;

        private:

          void
          create(const utils::Sizei& size,
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
