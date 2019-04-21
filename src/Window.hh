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
# include "Palette.hh"
# include "ColoredFont.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Window: public utils::CoreObject {
        public:

          Window(const utils::Sizei& size,
                 const std::string& title = std::string("Default SDL window"));

          ~Window();

          std::uint32_t
          getSDLID() const;

          void
          setIcon(const std::string& icon);

          utils::Uuid
          createTexture(const utils::Sizei& size,
                        const Palette::ColorRole& role);

          utils::Uuid
          createTextureFromFile(const std::string& file,
                                const Palette::ColorRole& role);

          utils::Uuid
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font,
                                const Palette::ColorRole& role);

          void
          fill(const utils::Uuid& uuid,
               const Palette& palette);

          void
          setTextureAlpha(const utils::Uuid& uuid,
                          const Color& color);

          void
          setTextureRole(const utils::Uuid& uuid,
                         const Palette::ColorRole& role);

          void
          drawTexture(const utils::Uuid& tex,
                      const utils::Uuid* on = nullptr,
                      utils::Boxf* where = nullptr);

          utils::Sizei
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
          create(const utils::Sizei& size);

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
