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
                       const std::string& title = std::string("Default SDL window"));

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
                                const utils::Uuid& font) override;

          utils::Uuid
          createTextureFromText(const std::string& text,
                                const utils::Uuid& font) override;

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
