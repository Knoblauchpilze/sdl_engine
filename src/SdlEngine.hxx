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

        m_winID(Window::UUID()),
        m_windows(),
        m_activeWin(nullptr),

        m_texID(Texture::UUID()),
        m_textures()
      {
        setService(std::string("engine"));

        initializeSDLLib();
      }

      inline
      SdlEngine::~SdlEngine() {
        releaseSDLLib();
      }

      Window::UUID
      SdlEngine::createWindow(const utils::Sizei& size,
                              const std::string& title)
      {
        // Acquire the lock so that we do not create multiple windows at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Attempt to create a window with the specified dimensions.
        WindowShPtr window = std::make_shared<Window>(m_winID, size,title);

        // Register this window in the internal tables.
        m_windows[m_winID] = window;
        ++m_winID;

        return window->getUUID();
      }

      Texture::UUID
      SdlEngine::createTexture(const utils::Sizei& size) {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Check whether an active window is set: if this is not the case we
        // cannot create a texture as a texture must have a window parent so
        // that we can use the associated renderer.
        if (m_activeWin == nullptr) {
          error(
            std::string("Cannot create texture with dimensions ") + size.toString(),
            std::string("No active window set")
          );
        }

        // Attempt to create a texture with the specified dimensions.
        TextureShPtr texture = std::make_shared<Texture>(m_texID, size, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        m_textures[m_texID] = texture;
        ++m_texID;

        return texture->getUUID();
      }

      void
      SdlEngine::setActiveWindow(const Window::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Check whether this window actually exist.
        const WindowsMap::const_iterator win = m_windows.find(uuid);
        if (win == m_windows.cend()) {
          error(
            std::string("Could not set active window to ") + std::to_string(uuid),
            std::string("Window does not exist")
          );
        }

        m_activeWin = win->second;
      }

    }
  }
}

#endif    /* SDL_ENGINE_HXX */
