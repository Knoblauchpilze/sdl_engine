
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      SDL_Texture*
      SurfaceTexture::create() {
        // Declare the support for the texture if we need to create it.
        // Indeed we need to keep it available at least until we create
        // the texture from the surface.
        std::vector<std::uint8_t> raw;

        if (m_surface == nullptr) {
          // Check whether we should create the texture from its raw data.
          if (m_rawData == nullptr) {
            error(
              std::string("Could not create texture from surface"),
              std::string("Invalid null surface")
            );
          }

          // Assume 4 channels (fair assumption as the raw data is composed of
          // `Color` objects.
          const unsigned channelCount = 4u;
          const unsigned depth = channelCount * sizeof(std::uint8_t) * 8u;
          const unsigned pitch = m_rawData->dims.w() * channelCount;
          const unsigned total = m_rawData->dims.w() * m_rawData->dims.h();
          const std::uint32_t format = SDL_PIXELFORMAT_RGBA32;

          raw.resize(channelCount * total, 0u);

          for (unsigned id = 0u ; id < total ; ++id) {
            raw[channelCount * id + 0u] = m_rawData->colors[id].rU();
            raw[channelCount * id + 1u] = m_rawData->colors[id].gU();
            raw[channelCount * id + 2u] = m_rawData->colors[id].bU();
            raw[channelCount * id + 3u] = m_rawData->colors[id].aU();
          }

          // Create the canvas with the requested dimensions. We
          // use a dedicated method allowing to create the surface
          // directly from the raw data.
          m_surface = SDL_CreateRGBSurfaceWithFormatFrom(
            raw.data(),
            m_rawData->dims.w(),
            m_rawData->dims.h(),
            depth,
            pitch,
            format
          );

          if (m_surface == nullptr) {
            error(
              std::string("Could not create texture from surface"),
              SDL_GetError()
            );
          }
        }

        // Convert the surface to a valid texture.
        SDL_Texture* tex = SDL_CreateTextureFromSurface(getRenderer(), m_surface);

        // Check whether the texture could successfully be created from the surface.
        if (tex == nullptr) {
          error(
            std::string("Unable to create texture from surface"),
            SDL_GetError()
          );
        }

        // Return the created texture.
        return tex;
      }

    }
  }
}
