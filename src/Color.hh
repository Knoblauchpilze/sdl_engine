#ifndef    COLOR_HH
# define   COLOR_HH

# include <memory>
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      

      class Color {
        public:

          enum class NamedColor {
            White,
            Black,
            Red,
            Green,
            Blue,
            Yellow,
            Orange,
            Cyan,
            Magenta,
            Silver,
            Gray,
            Maroon,
            Olive,
            Purple,
            Teal,
            Navy,
            CorneFlowerBlue
          };

        public:

          Color(const NamedColor& color = NamedColor::Black);

          ~Color() = default;

          const float&
          r() const noexcept;

          float&
          r() noexcept;

          const float&
          g() const noexcept;

          float&
          g() noexcept;

          const float&
          b() const noexcept;

          float&
          b() noexcept;

          const float&
          a() const noexcept;

          float&
          a() noexcept;

          bool
          isOpaque() const noexcept;

          bool
          isTransparent() const noexcept;

          float
          brightness() const noexcept;

          Color
          brighten(const float& factor) noexcept;

          Color
          darken(const float& factor) noexcept;

          static
          Color
          fromRGB(const float& r,
                  const float& g,
                  const float& b) noexcept;

          static
          Color
          fromRGBA(const float& r,
                   const float& g,
                   const float& b,
                   const float& a) noexcept;

        protected:

          Color(const float& r,
                const float& g,
                const float& b,
                const float& a = SDL_ALPHA_OPAQUE);

          void
          fromNamedColor(const NamedColor& color,
                         float& r,
                         float& g,
                         float& b) const noexcept;

        private:

          static const float sk_opaqueAlpha;
          static const float sk_transparentAlpha;

          float m_r;
          float m_g;
          float m_b;
          float m_a;

      };

      using ColorShPtr = std::shared_ptr<Color>;
    }
  }
}

# include "Color.hxx"

#endif    /* COLOR_HH */
