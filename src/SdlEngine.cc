
# include "SdlEngine.hh"

namespace sdl {
  namespace core {
    namespace engine {

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

      void
      SdlEngine::setWindowIcon(const Window::UUID& uuid,
                               const std::string& icon)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Assign the icon to this window.
        win->setIcon(icon);
      }

      void
      SdlEngine::clearWindow(const Window::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Clear its content.
        win->clear();
      }

      void
      SdlEngine::renderWindow(const Window::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Render its content.
        win->render();
      }


      void
      SdlEngine::destroyWindow(const Window::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Erase the window from the internal map.
        const std::size_t erased = m_windows.erase(uuid);

        // Warn the user if the texture could not be removed.
        if (erased != 1) {
          log(
            std::string("Could not erase inexisting texture ") + std::to_string(uuid),
            utils::Level::Warning
          );
        }

        // Also remove the active window if it corresponds to the id.
        if (m_activeWin != nullptr && m_activeWin->getUUID() == uuid) {
          m_activeWin.reset();
        }
      }

      utils::Uuid
      SdlEngine::createTexture(const utils::Sizei& size) {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Check whether an active window is set: if this is not the case we
        // cannot create a texture as a texture must have a window parent so
        // that we can use the associated renderer.
        checkActiveWindowOrThrow(
          std::string("Cannot create texture with dimensions ") + size.toString()
        );

        // Attempt to create a texture with the specified dimensions.
        TextureShPtr texture = std::make_shared<Texture>(size, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_textures[uuid] = texture;

        return uuid;
      }

      utils::Uuid
      SdlEngine::createTextureFromFile(const std::string& file) {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);


        // Check whether an active window is set: we need a renderer to perform
        // the conversion from surface to texture and thus a valid window to
        // use the underlying renderer.
        checkActiveWindowOrThrow(
          std::string("Cannot create texture from file ") + file
        );

        // Attempt to create a texture with the specified file name.
        TextureShPtr texture = std::make_shared<Texture>(file, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_textures[uuid] = texture;

        return uuid;
      }

      utils::Uuid
      SdlEngine::createTextureFromText(const std::string& text,
                                       ColoredFontShPtr font)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // In order to render a text; we need to use the renderer provided
        // by any active window. We thus need to make sure that we effectively
        // have a valid active window.
        checkActiveWindowOrThrow(
          std::string("Cannot create texture from text \"") + text + "\""
        );

        // Use the underlying renderer to perform the rendering of the text.
        TextureShPtr texture = font->render(text, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_textures[uuid] = texture;

        // Apply alpha value for the texture.
        texture->setAlpha(font->getColor());

        return uuid;
      }

      void
      SdlEngine::fillTexture(const utils::Uuid& uuid,
                             const Palette& palette)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the texture to fill.
        TextureShPtr tex = getTextureOrThrow(uuid);

        // We need to fill the texture with the color provided by the
        // input palette.
        // Based on the active window, we will use the underlying renderer
        // to perform the painting operation.
        checkActiveWindowOrThrow(
          std::string("Cannot fill texture ") + uuid.toString() + " with color"
        );

        // Retrieve the renderer associated to the active window and pass it
        // through to the texture along with the palette so that the texture
        // can automatically handle the filling operation.
        SDL_Renderer* renderer = m_activeWin->getRenderer();
        tex->fill(renderer, palette);
      }

      void
      SdlEngine::setTextureAlpha(const utils::Uuid& uuid,
                                 const Color& color)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the texture to fill.
        TextureShPtr tex = getTextureOrThrow(uuid);

        tex->setAlpha(color);
      }

      void
      SdlEngine::drawTexture(const utils::Uuid& tex,
                             const utils::Uuid* on,
                             utils::Boxf* where)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // We have two main cases: either the `on` argument is valid,
        // in which cas we have a regular blit onto a texture or it
        // is null, in which case we will use the default target of
        // the renderer which is the window itself.

        // Check whether we want to draw on the window.
        if (on == nullptr) {
          // Retrieve the texture to draw.
          TextureShPtr layer = getTextureOrThrow(tex);

          // Check that an active window is available, otherwise
          // we cannot use the underlying renderer.
          checkActiveWindowOrThrow(
            std::string("Cannot draw texture ") + tex.toString() + " window"
          );

          // Render thr texture on the window.
          m_activeWin->draw(layer, where);

          return;
        }
        
        // Retrieve the texture to draw and the texture onto
        // which the drawing should operate.
        TextureShPtr layer = getTextureOrThrow(tex);
        TextureShPtr base = getTextureOrThrow(*on);

        // Check that an active window is available, otherwise
        // we cannot use the underlying renderer.
        checkActiveWindowOrThrow(
          std::string("Cannot draw texture ") + tex.toString() + " onto " + on->toString()
        );

        // Perform the drawing.
        base->draw(layer, where, m_activeWin->getRenderer());
      }

      utils::Sizei
      SdlEngine::queryTexture(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the texture to query.
        TextureShPtr tex = getTextureOrThrow(uuid);

        int w, h;
        SDL_QueryTexture((*tex)(), nullptr, nullptr, &w, &h);

        return utils::Sizei(w, h);
      }

      void
      SdlEngine::destroyTexture(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Erase the texture from the internal map.
        const std::size_t erased = m_textures.erase(uuid);

        // Warn the user if the texture could not be removed.
        if (erased != 1) {
          log(
            std::string("Could not erase inexisting texture ") + uuid.toString(),
            utils::Level::Warning
          );
        }
      }

      void
      SdlEngine::initializeSDLLib() {
        // Initialize the SDL lib.
        if (!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
          error(
            std::string("Caught error while initializing SDL lib"),
            std::string("") + SDL_GetError()
          );
        }
      }

      void
      SdlEngine::releaseSDLLib() {
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
          SDL_Quit();
        }
      }

    }
  }
}
