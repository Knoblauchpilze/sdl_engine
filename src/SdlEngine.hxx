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
      utils::Uuid
      SdlEngine::createTexture(const utils::Sizei& size) {
        // Not handled in here, we need a window ID.
        error(std::string("Cannot create texture zith size ") + size.toString() + " without an active window");

        // Return even though error will always throw.
        return utils::Uuid();
      }

      inline
      utils::Uuid
      SdlEngine::createTextureFromFile(const std::string& file) {
        // Not handled in here, we need a window ID.
        error(std::string("Cannot create texture from file \"") + file + "\" without an active window");

        // Return even though error will always throw.
        return utils::Uuid();
      }

      inline
      utils::Uuid
      SdlEngine::createTextureFromText(const std::string& text,
                                       ColoredFontShPtr /*font*/)
      {
        // Not handled in here, we need a window ID.
        error(std::string("Cannot create texture from text \"") + text + "\" without an active window");

        // Return even though error will always throw.
        return utils::Uuid();
      }

      inline
      utils::Uuid
      SdlEngine::registerTextureForWindow(const utils::Uuid& tex,
                                          const utils::Uuid& win)
      {
        // Register it into the internal table.
        m_textures[tex] = win;

        // Return it.
        return tex;
      }

      inline
      utils::Uuid
      SdlEngine::getWindowUuidFromTextureOrThrow(const utils::Uuid& uuid) const {
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
      SdlEngine::getWindowFromTextureOrThrow(const utils::Uuid& uuid) const {
        return getWindowOrThrow(
          getWindowUuidFromTextureOrThrow(uuid)
        );
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
