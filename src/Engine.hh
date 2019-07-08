#ifndef    ENGINE_HH
# define   ENGINE_HH

# include <memory>
# include <maths_utils/Size.hh>
# include <maths_utils/Box.hh>
# include <core_utils/Uuid.hh>
# include "Window.hh"
# include "Texture.hh"
# include "Palette.hh"
# include "Color.hh"
# include "ColoredFont.hh"
# include "Event.hh"
# include "EnterEvent.hh"
# include "KeyEvent.hh"
# include "MouseEvent.hh"
# include "PaintEvent.hh"
# include "QuitEvent.hh"
# include "ResizeEvent.hh"
# include "WindowEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Engine {
        public:

          virtual utils::Uuid
          createWindow(const utils::Sizei& size,
                       const bool resizable = true,
                       const std::string& title = std::string("Default SDL window")) = 0;

          virtual void
          setWindowIcon(const utils::Uuid& uuid,
                        const std::string& icon) = 0;

          virtual void
          clearWindow(const utils::Uuid& uuid) = 0;

          virtual void
          renderWindow(const utils::Uuid& uuid) = 0;

          virtual void
          destroyWindow(const utils::Uuid& uuid) = 0;

          virtual utils::Uuid
          createTexture(const utils::Uuid& win,
                        const utils::Sizei& size,
                        const Palette::ColorRole& role) = 0;

          // TODO: Should probably be a Sizef so that we can keep the real size as long as possible.
          virtual utils::Uuid
          createTexture(const utils::Sizei& size,
                        const Palette::ColorRole& role) = 0;

          virtual utils::Uuid
          createTextureFromFile(const utils::Uuid& win,
                                const std::string& file,
                                const Palette::ColorRole& role) = 0;

          virtual utils::Uuid
          createTextureFromFile(const std::string& file,
                                const Palette::ColorRole& role) = 0;

          virtual utils::Uuid
          createTextureFromText(const utils::Uuid& win,
                                const std::string& text,
                                const utils::Uuid& font,
                                const Palette::ColorRole& role) = 0;

          virtual utils::Uuid
          createTextureFromText(const std::string& text,
                                const utils::Uuid& font,
                                const Palette::ColorRole& role) = 0;

          virtual void
          fillTexture(const utils::Uuid& uuid,
                      const Palette& palette,
                      const utils::Boxf* area = nullptr) = 0;

          virtual void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color) = 0;

          virtual Palette::ColorRole
          getTextureRole(const utils::Uuid& uuid) = 0;

          virtual void
          setTextureRole(const utils::Uuid& uuid,
                         const Palette::ColorRole& role) = 0;

          virtual void
          drawTexture(const utils::Uuid& tex,
                      const utils::Boxf* from = nullptr,
                      const utils::Uuid* on = nullptr,
                      const utils::Boxf* where = nullptr) = 0;

          virtual utils::Sizei
          queryTexture(const utils::Uuid& uuid) = 0;

          virtual void
          destroyTexture(const utils::Uuid& uuid) = 0;

          virtual utils::Uuid
          createColoredFont(const std::string& name,
                            const Palette& palette,
                            const int& size = 25) = 0;

          virtual void
          destroyColoredFont(const utils::Uuid& uuid) = 0;

          virtual EventShPtr
          pollEvent(bool& moreEvents) = 0;

          virtual void
          populateEvent(Event& event);

          virtual void
          populateEvent(EnterEvent& event);

          virtual void
          populateEvent(KeyEvent& event);

          virtual void
          populateEvent(MouseEvent& event);

          virtual void
          populateEvent(PaintEvent& event);

          virtual void
          populateEvent(QuitEvent& event);

          virtual void
          populateEvent(ResizeEvent& event);

          virtual void
          populateEvent(WindowEvent& event);
      };

      using EngineShPtr = std::shared_ptr<Engine>;
    }
  }
}

# include "Engine.hxx"

#endif    /* ENGINE_HH */
