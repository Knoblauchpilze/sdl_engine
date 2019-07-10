#ifndef    TEXTURE_HH
# define   TEXTURE_HH

# include <memory>
# include <string>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include <maths_utils/Box.hh>
# include "Color.hh"
# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Texture: public utils::CoreObject {
        public:

          ~Texture();

          SDL_Texture*
          operator()();

          const Palette::ColorRole&
          getRole() const noexcept;

          /**
           * @brief - Attempts to fill this texture with the palette provided based on
           *          the internal role for this texture.
           *          The palette is used to retrieve the associated color to apply to
           *          the texture. The `area` (if not null) specifies a rectangle of the
           *          texture which should be filled with the corresponding color.
           *          Note that if the `area` is null the whole texture is filled with
           *          the color corresponding to the current texture's role.
           * @param palette - the palette to use to retrieve the color corresponding to
           *                  the texture's role.
           * @param area - the area of the texture to fill. If this argument is null the
           *               whole texture will be filled.
           */
          void
          fill(const Palette& palette,
               const utils::Boxf* area = nullptr);

          /**
           * @brief - Perform the copy operation of `this` texture on the specified `on`
           *          texture or on the default rendering target if no texture is provided.
           *          The `from` indicates the area of `this` texture to copy and the
           *          `where` indicates the area where this texture should be copied.
           * @param from - a box representing the source area of `this` texture which should
           *               be copied. If this value is null the entire texture will be copied.
           * @param where - a box representing where `this` texture should be copied. If the
           *                value is null `this` texture will be copied so that it occupies
           *                the entire destination texture.
           * @param on - an optional texture which indicates the destination texture where
           *             `this` texture should be drawn. If this value is null `this` texture
           *             is copied on the default rendering target pf the renderer.
           */
          void
          draw(const utils::Boxf* from,
               const utils::Boxf* where,
               SDL_Texture* on = nullptr);

          void
          setAlpha(const Color& color);

          void
          setRole(const Palette::ColorRole& role);

          /**
           * @brief - Used to retrieve the dimensions of the texture. Note that this function
           *          returns the logical size of the texture as assigned when creating the
           *          texture and not the exact size of the underlying SDL texture.
           *          This allows for more flexibility when dealing with texture's size as we
           *          can account for half pixels for example.
           * @return - the size of the texture.
           */
          virtual utils::Sizef
          query();

        protected:

          enum class Type {
            Basic,
            Image,
            Surface
          };

          Texture(SDL_Renderer* renderer,
                  const Palette::ColorRole& role,
                  const Type& type);

          SDL_Renderer*
          getRenderer() const noexcept;

          bool
          valid() const noexcept;

          virtual SDL_Texture*
          create() = 0;

        private:

          void
          clean();

          /**
           * @brief - Used to automatically performs a check by calling `valid` and
           *          launch the texture's creation if the return value is false.
           *          Avoid to wrap `if (valid()) { create(); }` everywhere in the
           *          code.
           */
          void
          createOnce();

        private:

          SDL_Renderer* m_renderer;
          Palette::ColorRole m_role;
          Type m_type;
          SDL_Texture* m_texture;
      };

      using TextureShPtr = std::shared_ptr<Texture>;
    }
  }
}

# include "Texture.hxx"

#endif    /* TEXTURE_HH */
