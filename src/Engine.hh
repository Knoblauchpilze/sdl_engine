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

namespace sdl {
  namespace core {
    namespace engine {

      class Engine {
        public:

          virtual utils::Uuid
          createWindow(const utils::Sizei& size,
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
                        const utils::Sizei& size) = 0;

          virtual utils::Uuid
          createTexture(const utils::Sizei& size) = 0;

          virtual utils::Uuid
          createTextureFromFile(const utils::Uuid& win,
                                const std::string& file) = 0;

          virtual utils::Uuid
          createTextureFromFile(const std::string& file) = 0;
          
          virtual utils::Uuid
          createTextureFromText(const utils::Uuid& win,
                                const std::string& text,
                                ColoredFontShPtr font) = 0;

          virtual utils::Uuid
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font) = 0;

          virtual void
          fillTexture(const utils::Uuid& uuid,
                      const Palette& palette) = 0;

          virtual void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color) = 0;

          virtual void
          drawTexture(const utils::Uuid& tex,
                      const utils::Uuid* on = nullptr,
                      utils::Boxf* where = nullptr) = 0;

          virtual utils::Sizei
          queryTexture(const utils::Uuid& uuid) = 0;

          virtual void
          destroyTexture(const utils::Uuid& uuid) = 0;

          virtual EventShPtr
          pollEvent(bool& moreEvents) = 0;

      };

      using EngineShPtr = std::shared_ptr<Engine>;
    }
  }
}

#endif    /* ENGINE_HH */
