#ifndef    WINDOW_HH
# define   WINDOW_HH

# include <memory>
# include <string>
# include <cstdint>
# include <unordered_map>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <core_utils/Uuid.hh>
# include <maths_utils/Size.hh>
# include "Texture.hh"
# include "Image.hh"
# include "Palette.hh"
# include "ColoredFont.hh"
# include "Brush.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Window: public utils::CoreObject {
        public:

          Window(const utils::Sizei& size,
                 const bool resizable = true,
                 const std::string& title = std::string("Default SDL window"));

          ~Window();

          std::uint32_t
          getSDLID() const;

          utils::Sizef
          getSize() const;

          void
          setIcon(const std::string& icon);

          /**
           * @brief - Used to specify the new viewport size for the renderer associated to this
           *          window. THe size will be assigned only if the current rendering target is
           *          `null`. Otherwise an error is raised.
           * @param area - the new viewport size for the renderer of this window. Note that the
           *               input coordinates will be converted to integer values.
           */
          void
          updateViewport(const utils::Boxf& area);

          /**
           * @brief - Creates a children texture for this window with the specified dimensions and
           *          role. The SDL library that we're using to create the texture needs to parent
           *          each texture to a renderer and a renderer is linked to a window hence the fact
           *          fact that this method is defined in the `Window` class.
           * @param size - the size of the texture to create.
           * @param role - the role to assign to the texture: this will mostly be used to draw the
           *               texture and select an appropriate color.
           * @return - a unique identifier which can be used to refer to the created texture for
           *            subsequent operations.
           */
          utils::Uuid
          createTexture(const utils::Sizef& size,
                        const Palette::ColorRole& role);

          utils::Uuid
          createTextureFromFile(ImageShPtr img,
                                const Palette::ColorRole& role);

          utils::Uuid
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font,
                                const Palette::ColorRole& role);

          utils::Uuid
          createTextureFromBrush(BrushShPtr brush);

          void
          fill(const utils::Uuid& uuid,
               const Palette& palette,
               const utils::Boxf* area = nullptr);

          void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color);

          Palette::ColorRole
          getTextureRole(const utils::Uuid& uuid);

          void
          setTextureRole(const utils::Uuid& uuid,
                         const Palette::ColorRole& role);

          void
          drawTexture(const utils::Uuid& tex,
                      const utils::Boxf* from = nullptr,
                      const utils::Uuid* on = nullptr,
                      const utils::Boxf* where = nullptr);

          /**
           * @brief - Tries to find the texture corresponding to the input identifier within
           *          this window and retrieves its associated dimensions.
           *          Note that if no such texture can be found within this window an error
           *          is raised.
           * @param uuid - the identifier of the texture which should be queried.
           * @return - a size rperesenting the dimensions of the texture.
           */
          utils::Sizef
          queryTexture(const utils::Uuid& uuid);

          void
          destroyTexture(const utils::Uuid& uuid);

          void
          clear() noexcept;

          void
          render() noexcept;

        private:

          using TexturesMap = std::unordered_map<utils::Uuid, TextureShPtr>;

          void
          create(const utils::Sizei& size,
                 const bool resizable);

          void
          clean();

          utils::Uuid
          registerTexture(TextureShPtr tex);

          TextureShPtr
          getTextureOrThrow(const utils::Uuid& uuid) const;

        private:

          SDL_Window* m_window;
          SDL_Renderer* m_renderer;

          TexturesMap m_textures;
      };

      using WindowShPtr = std::shared_ptr<Window>;
    }
  }
}

# include "Window.hxx"

#endif    /* WINDOW_HH */
