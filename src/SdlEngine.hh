#ifndef    SDL_ENGINE_HH
# define   SDL_ENGINE_HH

# include <mutex>
# include <unordered_map>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "Engine.hh"
# include "Window.hh"
# include "Texture.hh"
# include "RendererState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class SdlEngine : public Engine, public utils::CoreObject {
        public:

          SdlEngine();

          virtual ~SdlEngine();

          Window::UUID
          createWindow(const utils::Sizei& size,
                       const std::string& title = std::string("Default SDL window")) override;

          void
          setActiveWindow(const Window::UUID& uuid) override;

          Texture::UUID
          createTexture(const utils::Sizei& size) override;

          Texture::UUID
          createTextureFromFile(const std::string& file) override;

          Texture::UUID
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font) override;

          void
          fillTexture(const Texture::UUID& uuid,
                      const Palette& palette) override;

          void
          setTextureAlpha(const Texture::UUID& uuid,
                          const Color& color) override;

          void
          drawTexture(const Texture::UUID& tex,
                      const Texture::UUID& on,
                      utils::Boxf* where = nullptr) override;

          utils::Sizei
          queryTexture(const Texture::UUID& uuid) override;

          void
          destroyTexture(const Texture::UUID& uuid) override;

        private:

          void
          initializeSDLLib();

          void
          releaseSDLLib();

          void
          checkActiveWindowOrThrow(const std::string& errorMessage) const;

          TextureShPtr
          getTextureOrThrow(const Texture::UUID& uuid) const;

        private:

          using WindowsMap = std::unordered_map<Window::UUID, WindowShPtr>;
          using TexturesMap = std::unordered_map<Texture::UUID, TextureShPtr>;

          std::mutex m_locker;

          Window::UUID m_winID;
          WindowsMap m_windows;
          WindowShPtr m_activeWin;

          Texture::UUID m_texID;
          TexturesMap m_textures;
      };

    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
