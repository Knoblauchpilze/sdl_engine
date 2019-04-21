#ifndef    SDL_ENGINE_HH
# define   SDL_ENGINE_HH

# include <mutex>
# include <memory>
# include <cstdint>
# include <unordered_map>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "Engine.hh"
# include "Window.hh"
# include "Texture.hh"
# include "RendererState.hh"
# include "FontFactory.hh"

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
                        const utils::Sizei& size,
                        const Palette::ColorRole& role) override;

          utils::Uuid
          createTexture(const utils::Sizei& size,
                        const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromFile(const utils::Uuid& win,
                                const std::string& file,
                                const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromFile(const std::string& file,
                                const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromText(const utils::Uuid& win,
                                const std::string& text,
                                const utils::Uuid& font,
                                const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromText(const std::string& text,
                                const utils::Uuid& font,
                                const Palette::ColorRole& role) override;

          void
          fillTexture(const utils::Uuid& uuid,
                      const Palette& palette) override;

          void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color) override;

          void
          setTextureRole(const utils::Uuid& uuid,
                         const Palette::ColorRole& role) override;

          void
          drawTexture(const utils::Uuid& tex,
                      const utils::Uuid* on = nullptr,
                      utils::Boxf* where = nullptr) override;

          utils::Sizei
          queryTexture(const utils::Uuid& uuid) override;

          void
          destroyTexture(const utils::Uuid& uuid) override;

          utils::Uuid
          createColoredFont(const std::string& name,
                            const Palette& palette,
                            const int& size = 25) override;

          void
          destroyColoredFont(const utils::Uuid& uuid) override;

          EventShPtr
          pollEvent(bool& moreEvents) override;

          void
          populateEvent(WindowEvent& event) override;

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

          ColoredFontShPtr
          getFontOrThrow(const utils::Uuid& uuid) const;

          utils::Uuid
          getWindowUuidFromSDLWinID(const std::uint32_t& winID) const;

        private:

          using WindowsMap = std::unordered_map<utils::Uuid, WindowShPtr>;
          using SDLWinToWindows = std::unordered_map<std::uint32_t, utils::Uuid>;

          // Textures are associated to their related window identifier.
          using TexturesMap = std::unordered_map<utils::Uuid, utils::Uuid>;

          using FontsMap = std::unordered_map<utils::Uuid, ColoredFontShPtr>;

          std::mutex m_locker;

          FontFactoryShPtr m_fontFactory;

          WindowsMap m_windows;
          SDLWinToWindows m_winIDToWindows;
          TexturesMap m_textures;
          FontsMap m_fonts;
      };

      using SdlEngineShPtr = std::shared_ptr<SdlEngine>;
    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
