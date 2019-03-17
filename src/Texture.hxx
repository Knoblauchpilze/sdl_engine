#ifndef    TEXTURE_HXX
# define   TEXTURE_HXX

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "BoxUtils.hh"
# include "RendererState.hh"

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
      Texture::Texture(const UUID& uuid,
                       const std::string& file,
                       SDL_Renderer* renderer):
        utils::CoreObject(std::string("texture_") + std::to_string(uuid)),
        m_uuid(uuid),
        m_texture(nullptr)
      {
        setService(std::string("texture"));

        create(file, renderer);
      }

      inline
      Texture::Texture(const UUID& uuid,
                       SDL_Texture* tex):
        utils::CoreObject(std::string("texture_") + std::to_string(uuid)),
        m_uuid(uuid),
        m_texture(tex)
      {
        setService(std::string("texture"));
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
      SDL_Texture*
      Texture::operator()() const noexcept {
        return m_texture;
      }

      inline
      void
      Texture::fill(SDL_Renderer* renderer,
                    const Palette& palette)
      {
        // Retrieve the color to use to fill the texture from the palette.
        SDL_Color color = palette.getActiveColor().toSDLColor();

        // Save the current state of the renderer: this will automatically handle restoring
        // the state upon destroying this object.
        RendererState state(renderer);

        // Configure the renderer to draw on the texture, apply the color and perform
        // the filling.
        SDL_SetRenderTarget(renderer, m_texture);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
      }

      inline
      void
      Texture::draw(std::shared_ptr<Texture> tex,
                    utils::Boxf* box,
                    SDL_Renderer* renderer)
      {
        // Save the renderer state so that we can restore the
        // initial rendering target and properties (color, etc.).
        RendererState state(renderer);

        // Set this texture as rendering target.
        SDL_SetRenderTarget(renderer, m_texture);

        // Draw the input texture at the corresponding location.
        if (box == nullptr) {
          SDL_RenderCopy(renderer, (*tex)(), nullptr, nullptr);
        } 
        else {
          SDL_Rect dstArea = utils::toSDLRect(*box);
          SDL_RenderCopy(renderer, (*tex)(), nullptr, &dstArea);
        }
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
      Texture::create(const std::string& file,
                      SDL_Renderer* renderer)
      {
        // First; load the image as a surface using regular SDL function.
        SDL_Surface* imageAsSurface = SDL_LoadBMP(file.c_str());
        if (imageAsSurface == nullptr) {
          error(
            std::string("Unable to create picture widget using file \"") + file + "\"",
            std::string("") + SDL_GetError()
          );
        }

        // Transform the surface into a valid texture.
        m_texture  = SDL_CreateTextureFromSurface(renderer, imageAsSurface);
        
        // Release the resources used by the surface.
        SDL_FreeSurface(imageAsSurface);

        // Check whether the texture could successfully be created from the surface.
        if (m_texture == nullptr) {
          error(
            std::string("Unable to create picture widget using file \"") + file + "\"",
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
