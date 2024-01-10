
# include "SdlEngine.hh"
# include "EventFactory.hh"

namespace sdl {
  namespace core {
    namespace engine {

      utils::Uuid
      SdlEngine::createWindow(const utils::Sizei& size,
                              const bool resizable,
                              const std::string& title)
      {
        // Acquire the lock so that we do not create multiple windows at the
        // same time.
        const std::lock_guard guard(m_locker);

        // Attempt to create a window with the specified dimensions.
        WindowShPtr window = std::make_shared<Window>(size, resizable, title);

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
        const std::lock_guard guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Assign the icon to this window.
        win->setIcon(icon);
      }

      void
      SdlEngine::clearWindow(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Clear its content.
        win->clear();
      }

      void
      SdlEngine::renderWindow(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Render its content.
        win->render();
      }

      void
      SdlEngine::updateViewport(const utils::Uuid& uuid,
                                const utils::Boxf& area)
      {
        const std::lock_guard guard(m_locker);

        // Retrieve the required window.
        WindowShPtr win = getWindowOrThrow(uuid);

        // Update its viewport.
        win->updateViewport(area);
      }

      void
      SdlEngine::destroyWindow(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Erase the window from the internal map.
        const std::size_t erased = m_windows.erase(uuid);

        // Warn the user if the window could not be removed.
        if (erased != 1) {
          warn("Could not erase inexisting window " + uuid.toString());
        }
      }

      utils::Uuid
      SdlEngine::createTexture(const utils::Uuid& win,
                               const utils::Sizef& size,
                               const Palette::ColorRole& role)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        const std::lock_guard guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTexture(size, role);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      utils::Uuid
      SdlEngine::createTextureFromFile(const utils::Uuid& win,
                                       ImageShPtr img,
                                       const Palette::ColorRole& role)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        const std::lock_guard guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTextureFromFile(img, role);

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
        const std::lock_guard guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Try to retrieve the font corresponding to the input uuid.
        ColoredFontShPtr coloredFont = getFontOrThrow(font);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTextureFromText(text, coloredFont, role);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      utils::Uuid
      SdlEngine::createTextureFromBrush(const utils::Uuid& win,
                                        BrushShPtr brush)
      {
        // Acquire the lock so that we do not create multiple textures at the
        // same time.
        const std::lock_guard guard(m_locker);

        // Try to retrieve the desired window from which the texture should be created.
        WindowShPtr parentWin = getWindowOrThrow(win);

        // Create the desired texture.
        utils::Uuid tex = parentWin->createTextureFromBrush(brush);

        // Register it into the internal table and return it.
        return registerTextureForWindow(tex, win);
      }

      void
      SdlEngine::fillTexture(const utils::Uuid& uuid,
                             const Palette& palette,
                             const utils::Boxf* area)
      {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture to fill.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the fill operation to the window object.
        win->fill(uuid, palette, area);
      }

      void
      SdlEngine::setTextureAlpha(const utils::Uuid& uuid,
                                 const Color& color)
      {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture for which alpha
        // should be set.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the alpha channel update to the window object.
        win->setTextureAlpha(uuid, color);
      }

      Palette::ColorRole
      SdlEngine::getTextureRole(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture for which the
        // role should be set.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the alpha channel update to the window object.
        return win->getTextureRole(uuid);
      }

      void
      SdlEngine::setTextureRole(const utils::Uuid& uuid,
                                const Palette::ColorRole& role)
      {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture for which the
        // role should be set.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Delegate the alpha channel update to the window object.
        win->setTextureRole(uuid, role);
      }

      void
      SdlEngine::drawTexture(const utils::Uuid& tex,
                             const utils::Boxf* from,
                             const utils::Uuid* on,
                             const utils::Boxf* where)
      {
        const std::lock_guard guard(m_locker);

        // We can only blit both textures from the same window.
        // Of course this does not apply if the `on` argument is
        // empty, in which case we should be able to blit the
        // input `tex` no matter what.

        if (on == nullptr) {
          // Retrieve the window associated to the `tex` argument.
          WindowShPtr win = getWindowFromTextureOrThrow(tex);

          // Perform the blit operation.
          win->drawTexture(tex, from, on, where);

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
        win->drawTexture(tex, from, on, where);
      }

      utils::Sizef
      SdlEngine::queryTexture(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture which
        // should be queried.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Return the result of the query.
        return win->queryTexture(uuid);
      }

      utils::Sizef
      SdlEngine::getTextSize(const std::string& text,
                             const utils::Uuid& font,
                             bool exact)
      {
        const std::lock_guard guard(m_locker);

        // Retrieve the font associated to the input identifier.
        ColoredFontShPtr fontImpl = getFontOrThrow(font);

        // Use the dedicated handler of the font to return the size
        // of the input text should it be rendered with this font.
        return fontImpl->querySize(text, exact);
      }

      void
      SdlEngine::destroyTexture(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Retrieve the window associated to the texture which
        // should be erased.
        WindowShPtr win = getWindowFromTextureOrThrow(uuid);

        // Erase this texture from the window.
        win->destroyTexture(uuid);

        // Erase the texture from the internal map.
        const std::size_t erased = m_textures.erase(uuid);

        // Warn the user if the texture could not be removed.
        if (erased != 1) {
          warn("Could not erase inexisting texture " + uuid.toString());
        }
      }

      utils::Uuid
      SdlEngine::createColoredFont(const std::string& name,
                                   const Palette& palette,
                                   int size)
      {
        const std::lock_guard guard(m_locker);

        // Create the font using the internal factory.
        ColoredFontShPtr font = m_fontFactory->createColoredFont(name, palette, size);

        // Register this window in the internal tables.
        utils::Uuid uuid = utils::Uuid::create();
        m_fonts[uuid] = font;

        return uuid;
      }

      void
      SdlEngine::destroyColoredFont(const utils::Uuid& uuid) {
        const std::lock_guard guard(m_locker);

        // Erase the font from the internal map.
        const std::size_t erased = m_fonts.erase(uuid);

        // Warn the user if the font could not be removed.
        if (erased != 1) {
          warn("Could not erase inexisting font " + uuid.toString());
        }
      }

      std::vector<EventShPtr>
      SdlEngine::pollEvents() {
        // Poll all events available in the queue.
        SDL_Event sdlEvent;
        bool moreEvents = true;

        std::vector<EventShPtr> events;

        while (moreEvents) {
          // Poll the next event in the queue.
          moreEvents = SDL_PollEvent(&sdlEvent);

          // If an event is available store it in the return array.
          if (moreEvents) {
            // Create this event.
            EventShPtr event = EventFactory::create(sdlEvent);

            // Check whether the event could be created.
            if (event != nullptr) {
              // Populate additional data for this event if needed.
              event->populateFromEngineData(*this);

              events.push_back(event);

              // Also in the case of a mouse event we want to update the
              // internal mouse state.
              if (event->isMouseEvent()) {
                std::vector<EventShPtr> newEvents = m_mouseState.updateEvent(
                  *std::dynamic_pointer_cast<MouseEvent>(event)
                );

                // Insert all produced events to the list of events fetched
                // from the underlying `API`.
                events.insert(events.end(), newEvents.cbegin(), newEvents.cend());
              }
            }
          }
        }

        // Return the list of events accumulated from the underlying `API`.
        return events;
      }

      void
      SdlEngine::populateEvent(Event& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(DropEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(EnterEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(FocusEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(HideEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(KeyEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(MouseEvent& event) {
        // Populate the window id.
        utils::Uuid winID = populateWindowIDEvent(event);

        // The window identifier might be invalid: indeed in the case of a user first clicking
        // on the application and then dragging the mouse outside of the window, an event will
        // be generated when the mouse button is released. In this case we have a default win
        // identifier assigned to the underlying `API` event because indeed the event did not
        // take place in any window (as it is outside of the application).
        // We could use two strategies: either discard the event or try to make sense of it.
        // The second solution seems like a better plan because otherwise it means that the
        // drag and drop event which has started will never be terminated. It will then be the
        // responsability of anyone handling drag event to detect when the mouse leaves the
        // application abd react accordingly. This would probably involve a lot of duplicated
        // code and need to not forget it each time we want to handle a drag and drop event.
        // Instead correctly handling the event in the engine will not require additional
        // processes anywhere else.
        //
        // That being said, we need to be able to correctly transform the position of the
        // mouse using a window. As we're not certain which window was initially involved
        // in the drag and drop event we should rely on the `m_mouseState` to provide a valid
        // window to work with.
        if (!winID.valid()) {
          winID = m_mouseState.updateWithBestSuitedWindow(event);
        }

        // Check consistency.
        if (!winID.valid()) {
          error(
            std::string("Could not interpret ") + Event::getNameFromEvent(event),
            std::string("No valid associated window")
          );
        }

        // We need to convert the coordinates of the mouse event based on the dimensions
        // of the window it's related to.
        // Basically the coordinates of the mouse are provided using a coordinate frame
        // like below:
        //
        //   O            x
        //    +---------->
        //    |
        //    |
        //    |
        //    |
        //  y v
        //
        // Where `x` ranges from `[0; window_width]` and `y` ranges from `[0; window_height]`.
        //
        // But we want to express the coordinates in a coordinate frame similar to the
        // following:
        //
        //            y ^
        //              |
        //              |
        //              |
        //              |
        //            O +---------->
        //                         x
        //
        // With `x` ranging from `[-window_width / 2, window_width / 2]` and `y` ranging from
        // `[-window_height / 2; window_height / 2]`.
        //
        // To do so we first need to retrieve the dimensions of the window which generated the
        // event and transform the coordinates.

        // Retrieve the window object from its uuid and transform the coordinates of the event.
        WindowShPtr win = getWindowOrThrow(winID);

        const utils::Sizef size = win->getSize();

        event.transformForWindow(size);
      }

      void
      SdlEngine::populateEvent(PaintEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(QuitEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(ResizeEvent& event) {
        // Populate the window id.
        populateWindowIDEvent(event);
      }

      void
      SdlEngine::populateEvent(WindowEvent& event) {
        // Populate the window id.
        utils::Uuid winID = populateWindowIDEvent(event);

        if (!winID.valid()) {
          error(
            std::string("Could not populate data for window event"),
            std::string("Cannot find corresponding internal window id")
          );
        }

        // Also we can assign the size of the window by retrieving it directly
        // from the underlying object: this helps in case of a maximize event
        // where the new maximum size is not specified in the event.

        // Retrieve the window object from its uuid.
        WindowShPtr win = getWindowOrThrow(winID);

        // Assign the corresponding size.
        event.setSize(win->getSize());

        // Finally update the mouse state with this event.
        m_mouseState.updateFromWindowEvent(event);
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

      utils::Uuid
      SdlEngine::populateWindowIDEvent(Event& event) {
        // We need to assign the window uuid from the SDL window ID of the event.
        // This can only be done if the window id provided by the event itself is
        // valid.
        if (!event.hasSDLWinID()) {
          // Return early.
          return utils::Uuid();
        }

        // Retrieve the internal window uuid from the corresponding SDL uuid.
        utils::Uuid winID = getWindowUuidFromSDLWinID(event.getSDLWinID());

        // Assign it to the event if it is valid: otherwise clear the window
        // identifier.
        if (winID.valid()) {
          event.setWindowID(winID);
        }
        else {
          event.clearSDLWindID();
        }

        return winID;
      }

    }
  }
}
