#ifndef    SDL_ENGINE_HH
# define   SDL_ENGINE_HH

# include <mutex>
# include <memory>
# include <unordered_map>
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

          utils::Uuid
          createWindow(const utils::Sizei& size,
                       const std::string& title = std::string("Default SDL window")) override;

          void
          setWindowIcon(const utils::Uuid& uuid,
                        const std::string& icon) override;

          void
          clearWindow(const utils::Uuid& uuid) override;

          void
          renderWindow(const utils::Uuid& uuid) override;

          void
          destroyWindow(const utils::Uuid& uuid) override;

          utils::Uuid
          createTexture(const utils::Uuid& win,
                        const utils::Sizei& size) override;

          utils::Uuid
          createTexture(const utils::Sizei& size) override;

          utils::Uuid
          createTextureFromFile(const utils::Uuid& win,
                                const std::string& file) override;

          utils::Uuid
          createTextureFromFile(const std::string& file) override;

          utils::Uuid
          createTextureFromText(const utils::Uuid& win,
                                const std::string& text,
                                ColoredFontShPtr font) override;

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

          EventShPtr
          pollEvent(bool& moreEvents) override;

        private:

          void
          initializeSDLLib();

          void
          releaseSDLLib();

          utils::Uuid
          registerTextureForWindow(const utils::Uuid& tex,
                                   const utils::Uuid& win);

          utils::Uuid
          getWindowUuidFromTextureOrThrow(const utils::Uuid& uuid) const;

          WindowShPtr
          getWindowFromTextureOrThrow(const utils::Uuid& uuid) const;

          WindowShPtr
          getWindowOrThrow(const utils::Uuid& uuid) const;

        private:

          using WindowsMap = std::unordered_map<utils::Uuid, WindowShPtr>;
          // Textures are associated to their related window identifier.
          using TexturesMap = std::unordered_map<utils::Uuid, utils::Uuid>;

          std::mutex m_locker;

          WindowsMap m_windows;
          TexturesMap m_textures;
      };

      using SdlEngineShPtr = std::shared_ptr<SdlEngine>;
    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
