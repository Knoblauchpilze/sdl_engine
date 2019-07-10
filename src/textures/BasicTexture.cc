
# include "BasicTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      BasicTexture::create() {
        // Attempt to create the underlying SDL texture.
        SDL_Texture* tex = SDL_CreateTexture(
          getRenderer(),
          SDL_PIXELFORMAT_RGBA8888,
          SDL_TEXTUREACCESS_TARGET,
          static_cast<int>(m_size.w()),
          static_cast<int>(m_size.h())
        );

        // Check whether the window could successfully be created.
        if (tex == nullptr) {
          error(
            std::string("Could not create texture from size"),
            SDL_GetError()
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
        int retCode = SDL_SetTextureBlendMode(tex, mode);
        if (retCode != 0) {
          error(
            std::string("Cannot create texture from size, failed to set blend mode to ") + std::to_string(mode),
            SDL_GetError()
          );
        }

        // Return the created texture.
        return tex;
      }

    }
  }
}
