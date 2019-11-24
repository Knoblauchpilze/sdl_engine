#ifndef    ENGINE_DECORATOR_HH
# define   ENGINE_DECORATOR_HH

# include <memory>
# include <string>
# include <core_utils/CoreObject.hh>
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EngineDecorator: public Engine, public utils::CoreObject {
        public:

          EngineDecorator(EngineShPtr engine,
                          const std::string& name = std::string("engine_decorator"));

          virtual ~EngineDecorator();

          utils::Uuid
          createWindow(const utils::Sizei& size,
                       const bool resizable = true,
                       const std::string& title = std::string("Default SDL window"));

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
           * @brief - Reimplementation of the base `Engine` class method. Uses the internal
           *          wrapped engine to perform the creation of the texture.
           * @param win - the identifier of the window for which the texture should be created.
           * @param size - the size of the texture to create.
           * @param role - the role to assign to the texture.
           * @return - an identifier allowing to reference the created texture in subsequent
           *           operations.
           */
          utils::Uuid
          createTexture(const utils::Uuid& win,
                        const utils::Sizef& size,
                        const Palette::ColorRole& role) override;

          /**
           * @brief - Reimplementation of the base `Engine` class method. Uses the internal
           *          wrapped engine to perform the creation of the texture.
           * @param size - the dimensions of the texture to create.
           * @param role - the role to assign to the texture.
           * @return - an identifier allowing to reference the texture in subsequent operations.
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
           * @brief - Reimplementation of the base class. Uses the internal engine
           *          to perform the query.
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

        protected:

          void
          setEngine(EngineShPtr engine);

        private:

          EngineShPtr m_engine;
      };

      using EngineDecoratorShPtr = std::shared_ptr<EngineDecorator>;
    }
  }
}

# include "EngineDecorator.hxx"

#endif    /* ENGINE_DECORATOR_HH */
