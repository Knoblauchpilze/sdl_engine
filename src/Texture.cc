
# include "Texture.hh"
# include "RendererState.hh"

namespace {
  /**
   * @brief - Builds a top left SDL_Rect object from the input box.
   * @return - a sdl rect object based on the input description of the box.
   */
  template <typename CoordinateType>
  inline
  SDL_Rect
  toSDLRect(const utils::Box<CoordinateType>& box) noexcept {
    return SDL_Rect{
      static_cast<int>(box.getLeftBound()),
      static_cast<int>(box.getBottomBound()),
      static_cast<int>(box.w()),
      static_cast<int>(box.h())
    };
  }
}

namespace sdl {
  namespace core {
    namespace engine {

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

      void
      Texture::draw(utils::Boxf* box,
                    SDL_Renderer* renderer)
      {
        // Draw the input texture at the corresponding location.
        if (box == nullptr) {
          SDL_RenderCopy(renderer, m_texture, nullptr, nullptr);
        } 
        else {
          SDL_Rect dstArea = toSDLRect(*box);
          SDL_RenderCopy(renderer, m_texture, nullptr, &dstArea);
        }
      }

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

        // Let's assign a custom blend mode for the texture. It plays nicely with what we want most
        // of the time.
        // This custom blend mode is mainly used to be able to have additive alpha blending in children widget.
        // Basically if a widget has a transparency of 128 and one of its children has also a transparency of 128,
        // we would want the final pixel to have a transparency of 64 (i.e. one fourth of totally opaque).
        // This cannot be achieved using any of the proposed blend modes so we have to rely on custom blend mode.
        // The custom blend mode can be composed as follows:
        // dstRGB = colorOperation(srcRGB * srcColorFactor, dstRGB * dstColorFactor)
        // dstA = alphaOperation(srcA * srcAlphaFactor, dstA * dstAlphaFactor)
        SDL_BlendMode mode = SDL_ComposeCustomBlendMode(
          SDL_BLENDFACTOR_SRC_ALPHA,           // srcColorFactor
          SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA, // dstColorFactor
          SDL_BLENDOPERATION_ADD,              // colorOperation
          SDL_BLENDFACTOR_ZERO,                // srcAlphaFactor
          SDL_BLENDFACTOR_ONE,                 // dstAlphaFactor
          SDL_BLENDOPERATION_ADD               // alphaOperation
        );

        // Assign the custom blend mode.
        int retCode = SDL_SetTextureBlendMode(m_texture, mode);
        if (retCode != 0) {
          error(
            std::string("Cannot set blend mode to ") + std::to_string(mode),
            std::string("") + SDL_GetError()
          );
        }
      }

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

    }
  }
}
