#ifndef    SDL_ENGINE_HXX
# define   SDL_ENGINE_HXX

# include "SdlEngine.hh"
# include <core_utils/CoreException.hh>

namespace sdl {
  namespace core {
    namespace engine {

      inline
      SdlEngine::SdlEngine():
        Engine(),
        utils::CoreObject(std::string("sdl")),

        m_locker(),

        m_windows(),
        m_activeWin(nullptr),

        m_textures()
      {
        setService(std::string("engine"));

        initializeSDLLib();
      }

      inline
      SdlEngine::~SdlEngine() {
        releaseSDLLib();
      }

      inline
      void
      SdlEngine::checkActiveWindowOrThrow(const std::string& errorMessage) const {
        if (m_activeWin == nullptr) {
          error(
            errorMessage,
            std::string("No active window set")
          );
        }
      }

      inline
      TextureShPtr
      SdlEngine::getTextureOrThrow(const utils::Uuid& uuid) const {
        const TexturesMap::const_iterator tex = m_textures.find(uuid);

        if (tex == m_textures.cend()) {
          error(
            std::string("Could not find texture ") + uuid.toString(),
            std::string("Texture does not exist")
          );
        }

        return tex->second;
      }

      inline
      WindowShPtr
      SdlEngine::getWindowOrThrow(const utils::Uuid& uuid) const {
        const WindowsMap::const_iterator win = m_windows.find(uuid);

        if (win == m_windows.cend()) {
          error(
            std::string("Could not find window ") + uuid.toString(),
            std::string("Window does not exist")
          );
        }

        return win->second;
      }

    }
  }
}

#endif    /* SDL_ENGINE_HXX */
