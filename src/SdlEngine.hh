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

          void
          setWindowIcon(const Window::UUID& uuid,
                        const std::string& icon) override;

          void
          clearWindow(const Window::UUID& uuid) override;

          void
          renderWindow(const Window::UUID& uuid) override;

          void
          destroyWindow(const Window::UUID& uuid) override;

          utils::Uuid
          createTexture(const utils::Sizei& size) override;

          utils::Uuid
          createTextureFromFile(const std::string& file) override;

          utils::Uuid
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font) override;

          void
          fillTexture(const utils::Uuid& uuid,
                      const Palette& palette) override;

          void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color) override;

          void
          drawTexture(const utils::Uuid& tex,
                      const utils::Uuid* on = nullptr,
                      utils::Boxf* where = nullptr) override;

          utils::Sizei
          queryTexture(const utils::Uuid& uuid) override;

          void
          destroyTexture(const utils::Uuid& uuid) override;

        private:

          void
          initializeSDLLib();

          void
          releaseSDLLib();

          void
          checkActiveWindowOrThrow(const std::string& errorMessage) const;

          TextureShPtr
          getTextureOrThrow(const utils::Uuid& uuid) const;

          WindowShPtr
          getWindowOrThrow(const Window::UUID& uuid) const;

        private:

          using WindowsMap = std::unordered_map<Window::UUID, WindowShPtr>;
          using TexturesMap = std::unordered_map<utils::Uuid, TextureShPtr>;

          std::mutex m_locker;

          Window::UUID m_winID;
          WindowsMap m_windows;
          WindowShPtr m_activeWin;

          TexturesMap m_textures;
      };

    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
