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
# include "DropEvent.hh"
# include "EnterEvent.hh"
# include "FocusEvent.hh"
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

          /**
           * @brief - Similar in behavior to the `createTexture` with no windows identifier but this
           *          method creates the texture as a child of the input window.
           *          Failure to create the texture or to provide a valid window identifier will raise
           *          an error.
           *          The user can specify the role of the texture to create. This role will mostly be
           *          used to determine the color to assign to the texture when drawing it.
           * @param win - an identifier of the window into which the texture should be created.
           * @param size - the size of the texture to create.
           * @param role - the role of the texture to create, mostly used to determine the color to use
           *               when drawing the texture.
           * @return - the identifier of the created texture.
           */
          virtual utils::Uuid
          createTexture(const utils::Uuid& win,
                        const utils::Sizef& size,
                        const Palette::ColorRole& role) = 0;

          /**
           * @brief - Creates a texture with the specified size and role. The size is provided with
           *          floating point dimensions in order to allow more flexibility. Most of the times
           *          the underlying texture will have integer dimensions though.
           *          The return value corresponds to a unique identifier which can then be used to
           *          reference the texture in the engine.
           * @param size - the size of the texture to create.
           * @param role - the role to associate to the texture.
           * @return - the identifier of the created texture.
           */
          virtual utils::Uuid
          createTexture(const utils::Sizef& size,
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

          /**
           * @brief - Used to perform the copy of the texture referenced by `tex` onto
           *          the texture referenced by `where`. The area of the input `tex`
           *          which should be drawn is specified by the `from` area, which should
           *          correspond to an area in local texture coordinate frame describing
           *          the area to draw.
           *          The precise position where the source texture should be drawn is
           *          specified by `where`. If `where is `null` the source area is mapped
           *          on the entire destination texture.
           *          If no `on` texture is provided the input `tex` is drawn on the default
           *          rendering target.
           *          Note that if both textures do not refer to the same window an error
           *          is raised. An error is raised as well if one of the texture cannot
           *          be found.
           * @param tex - an identifier representing the texture to draw.
           * @param from - a position describing the source area to draw. Should be expressed
           *               in local texture frame. A `null` value indicates that the whole
           *               `tex` should be drawn.
           * @param on - an identifier representing the texture to draw on. If this identifer
           *             corresponds to a texture in a different window an error is raised.
           *             If this value is null the `tex` is drawn on the default rendering
           *             target for its window.
           * @param where - a position describing where on the `on` texture the `tex` should
           *                be drawn. If the `on` parameter is `null` this value is ignored.
           *                If this value is `null` the source area will be mapped to the
           *                entire `on` texture. Should be expressed in local `on` texture
           *                coordinate frame.
           */
          virtual void
          drawTexture(const utils::Uuid& tex,
                      const utils::Boxf* from = nullptr,
                      const utils::Uuid* on = nullptr,
                      const utils::Boxf* where = nullptr) = 0;

          /**
           * @brief - Queries the underlying engine to find the dimensions of the texture
           *          referenced by the input identifier.
           *          If no such texture can be found in the engine an error is raised.
           *          Note that the returned size is composed of floating point values
           *          which is not always supported by underlying engine.
           *          The goal is to ensure consistencies with textures' creation where the
           *          user can specify floating point dimensions.
           * @param uuid - the index of the texture which dimensions should be queried.
           * @return - a size rperesenting the dimensions of the texture.
           */
          virtual utils::Sizef
          queryTexture(const utils::Uuid& uuid) = 0;

          virtual void
          destroyTexture(const utils::Uuid& uuid) = 0;

          virtual utils::Uuid
          createColoredFont(const std::string& name,
                            const Palette& palette,
                            const int& size = 25) = 0;

          virtual void
          destroyColoredFont(const utils::Uuid& uuid) = 0;

          virtual std::vector<EventShPtr>
          pollEvents() = 0;

          virtual void
          populateEvent(Event& event);

          virtual void
          populateEvent(DropEvent& event);

          virtual void
          populateEvent(EnterEvent& event);

          virtual void
          populateEvent(FocusEvent& event);

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
