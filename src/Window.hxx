#ifndef    WINDOW_HXX
# define   WINDOW_HXX

# include "Window.hh"
# include "BasicTexture.hh"
# include "FileTexture.hh"
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline  
      Window::Window(const utils::Sizei& size,
                     const std::string& title):
        utils::CoreObject(title),
        m_window(nullptr),
        m_renderer(nullptr),
        m_textures()
      {
        setService(std::string("window"));

        create(size);
      }

      inline
      Window::~Window() {
        // Clear textures.
        m_textures.clear();

        // Clear resoruces used by the renderer.
        clean();
      }

      inline
      utils::Uuid
      Window::createTexture(const utils::Sizei& size,
                            const Palette::ColorRole& role)
      {
        // Create the texture.
        TextureShPtr tex = std::make_shared<BasicTexture>(m_renderer, role, size);

        // Register and return it.
        return registerTexture(tex);
      }

      inline
      utils::Uuid
      Window::createTextureFromFile(const std::string& file,
                                    const Palette::ColorRole& role)
      {
        // Create the texture.
        TextureShPtr tex = std::make_shared<FileTexture>(m_renderer, role, file);

        // Register and return it.
        return registerTexture(tex);
      }

      inline
      utils::Uuid
      Window::createTextureFromText(const std::string& text,
                                    ColoredFontShPtr font,
                                    const Palette::ColorRole& role)
      {
        // Create the texture.
        TextureShPtr tex = font->render(text, m_renderer, role);

        // Register and return it.
        return registerTexture(tex);
      }

      inline
      void
      Window::fill(const utils::Uuid& uuid,
                   const Palette& palette)
      {
        // Try to retrieve the corresponding texture.
        TextureShPtr tex = getTextureOrThrow(uuid);

        // Fill it using the internal renderer.
        tex->fill(palette);
      }

      inline
      void
      Window::setTextureAlpha(const utils::Uuid& uuid,
                               const Color& color)
      {
        // Try to retrieve the corresponding texture.
        TextureShPtr tex = getTextureOrThrow(uuid);

        // Set its alpha channel from the input color.
        tex->setAlpha(color);
      }

      inline
      void
      Window::setTextureRole(const utils::Uuid& uuid,
                             const Palette::ColorRole& role)
      {
        // Try to retrieve the corresponding texture.
        TextureShPtr tex = getTextureOrThrow(uuid);

        // Update the role from the input argument.
        tex->setRole(role);
      }

      inline
      utils::Sizei
      Window::queryTexture(const utils::Uuid& uuid) {
        // Try to retrieve the corresponding texture.
        TextureShPtr tex = getTextureOrThrow(uuid);

        // Return the result of the query.
        return tex->query();
      }

      inline
      void
      Window::destroyTexture(const utils::Uuid& uuid) {
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

      inline
      void
      Window::Window::clear() noexcept {
        SDL_RenderClear(m_renderer);
      }

      inline
      void
      Window::render() noexcept {
        SDL_RenderPresent(m_renderer);
      }

      inline
      void
      Window::clean() {
        // Destrroy the renderer for this window.
        if (m_renderer != nullptr) {
          SDL_DestroyRenderer(m_renderer);
        }

        // Destroy the window.
        if (m_window != nullptr) {
          SDL_DestroyWindow(m_window);
        }
      }

      inline
      utils::Uuid
      Window::registerTexture(TextureShPtr tex) {
        // Register this texture in the internal list.
        utils::Uuid uuid = utils::Uuid::create();
        m_textures[uuid] = tex;

        // Return the texture.
        return uuid;
      }

      inline
      TextureShPtr
      Window::getTextureOrThrow(const utils::Uuid& uuid) const {
        const TexturesMap::const_iterator tex = m_textures.find(uuid);

        if (tex == m_textures.cend()) {
          error(
            std::string("Could not find texture ") + uuid.toString() + " in window",
            std::string("Texture does not exist")
          );
        }

        return tex->second;
      }

    }
  }
}

#endif    /* WINDOW_HXX */
