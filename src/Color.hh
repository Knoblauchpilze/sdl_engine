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
            Pink,
            Purple,
            Teal,
            Navy,
            CorneFlowerBlue
          };

        public:

          Color(const NamedColor& color = NamedColor::Black);

          ~Color() = default;

          bool
          operator==(const Color& rhs) const noexcept;

          bool
          operator!=(const Color& rhs) const noexcept;

          float
          r() const noexcept;

          float&
          r() noexcept;

          float
          rU() const noexcept;

          float
          g() const noexcept;

          float&
          g() noexcept;

          float
          gU() const noexcept;

          float
          b() const noexcept;

          float&
          b() noexcept;

          float
          bU() const noexcept;

          float
          a() const noexcept;

          float&
          a() noexcept;

          float
          aU() const noexcept;

          bool
          isOpaque() const noexcept;

          bool
          isTransparent() const noexcept;

          float
          brightness() const noexcept;

          Color
          brighten(float factor) noexcept;

          Color
          darken(float factor) noexcept;

          SDL_Color
          toSDLColor() const noexcept;

          std::string
          toString() const noexcept;

          Color
          mix(const Color& color) const noexcept;

          static
          Color
          fromRGB(float r,
                  float g,
                  float b) noexcept;

          static
          Color
          fromRGBA(float r,
                   float g,
                   float b,
                   float a) noexcept;

        protected:

          Color(float r,
                float g,
                float b,
                float a = SDL_ALPHA_OPAQUE);

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

std::ostream&
operator<<(std::ostream& out, const sdl::core::engine::Color& color) noexcept;

std::ostream&
operator<<(const sdl::core::engine::Color& color, std::ostream& out) noexcept;

# include "Color.hxx"

#endif    /* COLOR_HH */
