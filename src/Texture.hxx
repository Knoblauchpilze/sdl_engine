#ifndef    TEXTURE_HXX
# define   TEXTURE_HXX

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Texture::Texture(const UUID& uuid,
                       const utils::Sizei& size,
                        SDL_Renderer* renderer):
        utils::CoreObject(std::string("texture_") + std::to_string(uuid)),
        m_uuid(uuid),
        m_texture(nullptr)
      {
        setService(std::string("texture"));

        create(size, renderer);
      }

      inline
      Texture::~Texture() {
        clean();
      }

      inline
      const Texture::UUID&
      Texture::getUUID() const noexcept {
        return m_uuid;
      }

      inline
      void
      Texture::create(const utils::Sizei& size,
                      SDL_Renderer* renderer)
      {
        // Attempt to create the underlying SDL texture.
        m_texture = SDL_CreateTexture(
          renderer,
          SDL_PIXELFORMAT_RGBA8888,
          SDL_TEXTUREACCESS_TARGET,
          size.w(),
          size.h()
        );

        // Check whether the window could successfully be created.
        if (m_texture == nullptr) {
          error(
            std::string("Could not create SDL texture"),
            std::string("") + SDL_GetError()
          );
        }
      }

      inline
      void
      Texture::clean() {
        if (m_texture != nullptr) {
          SDL_DestroyTexture(m_texture);
        }
      }

    }
  }
}

#endif    /* TEXTURE_HXX */
