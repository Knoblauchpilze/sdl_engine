#ifndef    SDL_ENGINE_HH
# define   SDL_ENGINE_HH

# include <mutex>
# include <memory>
# include <cstdint>
# include <unordered_map>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include <maths_utils/Vector2.hh>
# include "Engine.hh"
# include "Window.hh"
# include "Texture.hh"
# include "FontFactory.hh"
# include "MouseState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class SdlEngine : public Engine, public utils::CoreObject {
        public:

          SdlEngine();

          virtual ~SdlEngine();

          utils::Uuid
          createWindow(const utils::Sizei& size,
                       const bool resizable = true,
                       const std::string& title = std::string("Default SDL window")) override;

          void
          setWindowIcon(const utils::Uuid& uuid,
                        const std::string& icon) override;

          void
          clearWindow(const utils::Uuid& uuid) override;

          void
          renderWindow(const utils::Uuid& uuid) override;

          void
          updateViewport(const utils::Uuid& uuid,
                         const utils::Boxf& area) override;

          void
          destroyWindow(const utils::Uuid& uuid) override;

          /**
           * @brief - Implementation of the interface method in order to create a texture using the
           *          SDL library.
           * @param win - the window for which the texture should be created.
           * @param size - the size of the texture to create.
           * @param role - the role to assign to the texture, mostly used to determine the drawing
           *               color for the texture.
           * @return - an identifier allowing to refer to the texture in subsequent operations.
           */
          utils::Uuid
          createTexture(const utils::Uuid& win,
                        const utils::Sizef& size,
                        const Palette::ColorRole& role) override;

          /**
           * @brief - Specialization of the interface method to provide the creation of a texture with
           *          no associated window. Within the SDL library this scenario is not allowed and
           *          thus this method always throws.
           *          The user is encouraged to use the other variant method.
           * @param size - ignored parameter.
           * @param role - ignored parameter.
           * @return - nothing, always raise an error before returning any value.
           */
          utils::Uuid
          createTexture(const utils::Sizef& size,
                        const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromFile(const utils::Uuid& win,
                                ImageShPtr img,
                                const Palette::ColorRole& role) override;

          utils::Uuid
          createTextureFromFile(ImageShPtr img,
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

          utils::Uuid
          createTextureFromBrush(BrushShPtr brush) override;

          utils::Uuid
          createTextureFromBrush(const utils::Uuid& win,
                                 BrushShPtr brush) override;

          void
          fillTexture(const utils::Uuid& uuid,
                      const Palette& palette,
                      const utils::Boxf* area = nullptr) override;

          void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color) override;

          Palette::ColorRole
          getTextureRole(const utils::Uuid& uuid) override;

          void
          setTextureRole(const utils::Uuid& uuid,
                         const Palette::ColorRole& role) override;

          void
          drawTexture(const utils::Uuid& tex,
                      const utils::Boxf* from = nullptr,
                      const utils::Uuid* on = nullptr,
                      const utils::Boxf* where = nullptr) override;

          /**
           * @brief - Reimplementation of the base `Engine` method. Ultimately queries
           *          the SDL library to obtain the size of the texture referenced by
           *          the input identifier.
           *          If no such texture can be found in the engine an error is raised.
           *          Note that the returned size is composed of floating point values
           *          which is not always supported by underlying engine.
           *          The goal is to ensure consistencies with textures' creation where the
           *          user can specify floating point dimensions.
           * @param uuid - the index of the texture which dimensions should be queried.
           * @return - a size rperesenting the dimensions of the texture.
           */
          utils::Sizef
          queryTexture(const utils::Uuid& uuid) override;

          utils::Sizef
          getTextSize(const std::string& text,
                      const utils::Uuid& font,
                      bool exact) override;

          void
          destroyTexture(const utils::Uuid& uuid) override;

          utils::Uuid
          createColoredFont(const std::string& name,
                            const Palette& palette,
                            int size = 25) override;

          void
          destroyColoredFont(const utils::Uuid& uuid) override;

          std::vector<EventShPtr>
          pollEvents() override;

          void
          populateEvent(Event& event) override;

          void
          populateEvent(DropEvent& event) override;

          void
          populateEvent(EnterEvent& event) override;

          void
          populateEvent(FocusEvent& event) override;

          void
          populateEvent(HideEvent& event) override;

          void
          populateEvent(KeyEvent& event) override;

          void
          populateEvent(MouseEvent& event) override;

          void
          populateEvent(PaintEvent& event) override;

          void
          populateEvent(QuitEvent& event) override;

          void
          populateEvent(ResizeEvent& event) override;

          void
          populateEvent(WindowEvent& event) override;

        private:

          void
          initializeSDLLib();

          void
          releaseSDLLib();

          /**
           * @brief - Used to populate the window's internal uuid from the
           *          window uuid provided by the SDL.
           * @param event - the event for which the id should be populated.
           * @return - the window id if any. Note that if the window if
           *           does not exist for some reason an invalid uuid is
           *           returned.
           */
          utils::Uuid
          populateWindowIDEvent(Event& event);

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

          /**
           * @brief - Used to retrieve the logical window identifier associated to the
           *          input `SDL` window identifier.
           *          Note that if no valid logical window matching the input identifier
           *          can be found an invalid identifier is returned. It is up to the
           *          caller to know what to do about it.
           * @param winID - the underlying `SDL` identifier.
           * @return - the logical window identifier associated to the input raw `API`
           *           data.
           */
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

          /**
           * @brief - Holds the current mouse state as computed from the events
           *          retrieved so far from the underlying `API`. This state is
           *          updated upon finding some events in order to keep a value
           *          up-to-date relatively to the real state of the mouse.
           */
          MouseState m_mouseState;
      };

      using SdlEngineShPtr = std::shared_ptr<SdlEngine>;
    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
