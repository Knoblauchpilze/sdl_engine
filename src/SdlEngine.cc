
# include "SdlEngine.hh"
# include "EventFactory.hh"

namespace sdl {
  namespace core {
    namespace engine {

      utils::Uuid
      SdlEngine::createWindow(const utils::Sizei& size,
                              const std::string& title)
      {
        // Acquire the lock so that we do not create multiple windows at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Attempt to create a window with the specified dimensions.
        WindowShPtr window = std::make_shared<Window>(size, title);

        // Register this window in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_windows[uuid] = window;

        m_winIDToWindows[window->getSDLID()] = uuid;

        return uuid;
      }

      void
      SdlEngine::setWindowIcon(const utils::Uuid& uuid,
                               const std::string& icon)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Assign the icon to this window.
        win->setIcon(icon);
      }

      void
      SdlEngine::clearWindow(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Clear its content.
        win->clear();
      }

      void
      SdlEngine::renderWindow(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Render its content.
        win->render();
      }


      void
      SdlEngine::destroyWindow(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Erase the window from the internal map.
        const std::size_t erased = m_windows.erase(uuid);

        // Warn the user if the window could not be removed.
        if (erased != 1) {
          log(
            std::string("Could not erase inexisting window ") + uuid.toString(),
            utils::Level::Warning
          );
        }
      }

      utils::Uuid
      SdlEngine::createTexture(const utils::Uuid& win,
                               const utils::Sizei& size,
                               const Palette::ColorRole& role)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTexture(size, role);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      utils::Uuid
      SdlEngine::createTextureFromFile(const utils::Uuid& win,
                                       const std::string& file,
                                       const Palette::ColorRole& role)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTextureFromFile(file, role);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      utils::Uuid
      SdlEngine::createTextureFromText(const utils::Uuid& win,
                                       const std::string& text,
                                       const utils::Uuid& font,
                                       const Palette::ColorRole& role)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        std::lock_guard<std::mutex> guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Try to retrieve the font corresponding to the input uuid.
        ColoredFontShPtr coloredFont = getFontOrThrow(font);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTextureFromText(text, coloredFont, role);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      void
      SdlEngine::fillTexture(const utils::Uuid& uuid,
                             const Palette& palette)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the window associated to the texture to fill.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the fill operation to the window object.
        win->fill(uuid, palette);
      }

      void
      SdlEngine::setTextureAlpha(const utils::Uuid& uuid,
                                 const Color& color)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the window associated to the texture for which alpha
        // should be set.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the alpha channel update to the window object.
        win->setTextureAlpha(uuid, color);
      }

      void
      SdlEngine::setTextureRole(const utils::Uuid& uuid,
                                const Palette::ColorRole& role)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the window associated to the texture for which the
        // role should be set.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the alpha channel update to the window object.
        win->setTextureRole(uuid, role);
      }

      void
      SdlEngine::drawTexture(const utils::Uuid& tex,
                             const utils::Uuid* on,
                             utils::Boxf* where)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // We can only blit both textures from the same window.
        // Of course this does not apply if the `on` argument is
        // empty, in which case we should be able to blit the
        // input `tex` no matter what.

        if (on == nullptr) {
          // Retrieve the window associated to the `tex` argument.
          WindowShPtr win = getWindowFromTextureOrThrow(tex);

          // Perform the blit operation.
          win->drawTexture(tex, on, where);

          // All set.
          return;
        }

        // Try to retrieve both identifiers for the input textures.
        utils::Uuid win1 = getWindowUuidFromTextureOrThrow(tex);
        utils::Uuid win2 = getWindowUuidFromTextureOrThrow(*on);

        // Check whether both textures belong to the same window.
        if (win1 != win2) {
          error(
            std::string("Cannot draw texture ") + tex.toString() + " on " + on->toString(),
            std::string("Texture do not belong to the same window")
          );
        }

        // Both texture belong to the same window, pass on to the
        // window pointer associated to any of the texture.
        WindowShPtr win = getWindowOrThrow(win1);
        win->drawTexture(tex, on, where);
      }

      utils::Sizei
      SdlEngine::queryTexture(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the window associated to the texture which
        // should be queried.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Return the result of the query.
        return win->queryTexture(uuid);
      }

      void
      SdlEngine::destroyTexture(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the window associated to the texture which
        // should be erased.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Erase this texture from the window.
        win->destroyTexture(uuid);

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

      utils::Uuid
      SdlEngine::createColoredFont(const std::string& name,
                                   const Palette& palette,
                                   const int& size)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Create the font using the internal factory.
        ColoredFontShPtr font = m_fontFactory->createColoredFont(name, palette, size);

        // Register this window in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_fonts[uuid] = font;

        return uuid;
      }

      void
      SdlEngine::destroyColoredFont(const utils::Uuid& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Erase the font from the internal map.
        const std::size_t erased = m_fonts.erase(uuid);

        // Warn the user if the font could not be removed.
        if (erased != 1) {
          log(
            std::string("Could not erase inexisting font ") + uuid.toString(),
            utils::Level::Warning
          );
        }
      }

      EventShPtr
      SdlEngine::pollEvent(bool& moreEvents) {
        // Poll the next event in the queue.
        SDL_Event sdlEvent;
        moreEvents = SDL_PollEvent(&sdlEvent);

        // Return an event from the retrieved event if any.
        if (moreEvents) {
          // Create this event.
          EventShPtr event = EventFactory::create(sdlEvent);

          // Check whether the event could be created.
          if (event != nullptr) {
            // Populate additional data for this event if needed.
            event->populateFromEngineData(*this);
          }

          // Return this event.
          return event;
        }

        // Return null as there's no event available right now.
        return nullptr;
      }

      void
      SdlEngine::populateEvent(WindowEvent& event) {
        // We need to assign the window event from the SDL window ID of the event.
        event.setWindowID(getWindowUuidFromSDLWinID(event.getSDLWinID()));
      }

      void
      SdlEngine::initializeSDLLib() {
        // Initialize the SDL lib.
        if (!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO) != 0) {
          error(
            std::string("Caught error while initializing SDL lib"),
            SDL_GetError()
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
