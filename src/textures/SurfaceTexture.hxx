#ifndef    SURFACE_TEXTURE_HXX
# define   SURFACE_TEXTURE_HXX

# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      SurfaceTexture::RawSurfaceDataShPtr
      SurfaceTexture::createFromData(const utils::Sizei& dims,
                                     std::vector<Color>& colors)
      {
        RawSurfaceDataShPtr data = std::make_shared<RawSurfaceData>(
          RawSurfaceData{utils::Sizei(), std::vector<Color>()}
        );

        data->dims = dims;
        data->colors.swap(colors);

        return data;
      }

      inline
      SurfaceTexture::SurfaceTexture(SDL_Renderer* renderer,
                                     SDL_Surface* surface,
                                     const Palette::ColorRole& role,
                                     bool takeOwnership):
        Texture(renderer, role, Type::Surface),

        m_surface(surface),
        m_rawData(nullptr),

        m_owner(takeOwnership)
      {}

      inline
      SurfaceTexture::SurfaceTexture(SDL_Renderer* renderer,
                                     RawSurfaceDataShPtr surface):
        Texture(renderer, Palette::ColorRole::Background, Type::Surface),

        m_surface(nullptr),
        m_rawData(surface),

        m_owner(true)
      {}

      inline
      SurfaceTexture::~SurfaceTexture() {
        // Release the raw data if needed.
        if (m_surface != nullptr && m_owner) {
          SDL_FreeSurface(m_surface);
        }
      }

    }
  }
}

#endif    /* SURFACE_TEXTURE_HXX */
