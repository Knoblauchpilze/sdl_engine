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

        m_fontFactory(nullptr),

        m_windows(),
        m_winIDToWindows(),
        m_textures(),
        m_fonts(),

        m_lastClickPosition(nullptr)
      {
        setService(std::string("engine"));

        initializeSDLLib();

        m_fontFactory = std::make_shared<FontFactory>();
      }

      inline
      SdlEngine::~SdlEngine() {
        // We need to clear the elements instantiated with the libraries before
        // unloading the libraries.

        // First TTF related stuff.
        // Clean fonts.
        m_fonts.clear();
        // And then unload the TTF library.
        m_fontFactory.reset();

        // Clean windows, which will clear automatically the textures.
        m_windows.clear();
        // And then unload the SDL library.
        releaseSDLLib();
      }

      inline
      utils::Uuid
      SdlEngine::createTexture(const utils::Sizef& size,
                               const Palette::ColorRole& /*role*/)
      {
        // Not handled in here, we need a window ID.
        error(std::string("Cannot create texture zith size ") + size.toString() + " without an active window");

        // Return even though error will always throw.
        return utils::Uuid();
      }

      inline
      utils::Uuid
      SdlEngine::createTextureFromFile(const std::string& file,
                                       const Palette::ColorRole& /*role*/)
      {
        // Not handled in here, we need a window ID.
        error(std::string("Cannot create texture from file \"") + file + "\" without an active window");

        // Return even though error will always throw.
        return utils::Uuid();
      }

      inline
      utils::Uuid
      SdlEngine::createTextureFromText(const std::string& text,
                                       const utils::Uuid& /*font*/,
                                       const Palette::ColorRole& /*role*/)
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

      inline
      ColoredFontShPtr
      SdlEngine::getFontOrThrow(const utils::Uuid& uuid) const {
        const FontsMap::const_iterator font = m_fonts.find(uuid);

        if (font == m_fonts.cend()) {
          error(
            std::string("Could not find font ") + uuid.toString(),
            std::string("Font does not exist")
          );
        }

        return font->second;
      }

      inline
      utils::Uuid
      SdlEngine::getWindowUuidFromSDLWinID(const uint32_t& winID) const {
        const SDLWinToWindows::const_iterator win = m_winIDToWindows.find(winID);

        if (win == m_winIDToWindows.cend()) {
          error(
            std::string("Could not find window uuid from SDL id ") + std::to_string(winID),
            std::string("Window does not exist")
          );
        }

        return win->second;
      }

    }
  }
}

#endif    /* SDL_ENGINE_HXX */
