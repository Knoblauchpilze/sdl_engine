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

      inline
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

      inline
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

      inline
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

      inline
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

      inline
      Texture::UUID
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
        TextureShPtr texture = std::make_shared<Texture>(m_texID, size, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        m_textures[m_texID] = texture;
        ++m_texID;

        return texture->getUUID();
      }

      inline
      Texture::UUID
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
        TextureShPtr texture = std::make_shared<Texture>(m_texID, file, m_activeWin->getRenderer());

        // Register this texture in the internal tables.
        m_textures[m_texID] = texture;
        ++m_texID;

        return texture->getUUID();
      }

      inline
      Texture::UUID
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
        TextureShPtr texture = font->render(
          text,
          m_texID,
          m_activeWin->getRenderer()
        );

        // Register this texture in the internal tables.
        m_textures[m_texID] = texture;
        ++m_texID;

        // Apply alpha value for the texture.
        setTextureAlpha(texture->getUUID(), font->getColor());

        return texture->getUUID();
      }

      inline
      void
      SdlEngine::fillTexture(const Texture::UUID& uuid,
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
          std::string("Cannot fill texture ") + std::to_string(uuid) + " with color"
        );

        // Retrieve the renderer associated to the active window and pass it
        // through to the texture along with the palette so that the texture
        // can automatically handle the filling operation.
        SDL_Renderer* renderer = m_activeWin->getRenderer();
        tex->fill(renderer, palette);
      }

      inline
      void
      SdlEngine::setTextureAlpha(const Texture::UUID& uuid,
                                 const Color& color)
      {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the texture to fill.
        TextureShPtr tex = getTextureOrThrow(uuid);

        SDL_SetTextureAlphaMod((*tex)(), color.toSDLColor().a);
      }

      inline
      void
      SdlEngine::drawTexture(const Texture::UUID& tex,
                             const Texture::UUID* on,
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
            std::string("Cannot draw texture ") + std::to_string(tex) + " window"
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
          std::string("Cannot draw texture ") + std::to_string(tex) + " onto " + std::to_string(*on)
        );

        // Perform the drawing.
        base->draw(layer, where, m_activeWin->getRenderer());
      }

      inline
      utils::Sizei
      SdlEngine::queryTexture(const Texture::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Retrieve the texture to query.
        TextureShPtr tex = getTextureOrThrow(uuid);

        int w, h;
        SDL_QueryTexture((*tex)(), nullptr, nullptr, &w, &h);

        return utils::Sizei(w, h);
      }

      inline
      void
      SdlEngine::destroyTexture(const Texture::UUID& uuid) {
        std::lock_guard<std::mutex> guard(m_locker);

        // Erase the texture from the internal map.
        const std::size_t erased = m_textures.erase(uuid);

        // Warn the user if the texture could not be removed.
        if (erased != 1) {
          log(
            std::string("Could not erase inexisting texture ") + std::to_string(uuid),
            utils::Level::Warning
          );
        }
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
      SdlEngine::getTextureOrThrow(const Texture::UUID& uuid) const {
        const TexturesMap::const_iterator tex = m_textures.find(uuid);

        if (tex == m_textures.cend()) {
          error(
            std::string("Could not find texture ") + std::to_string(uuid),
            std::string("Texture does not exist")
          );
        }

        return tex->second;
      }

      inline
      WindowShPtr
      SdlEngine::getWindowOrThrow(const Window::UUID& uuid) const {
        const WindowsMap::const_iterator win = m_windows.find(uuid);

        if (win == m_windows.cend()) {
          error(
            std::string("Could not find window ") + std::to_string(uuid),
            std::string("Window does not exist")
          );
        }

        return win->second;
      }

    }
  }
}

#endif    /* SDL_ENGINE_HXX */
