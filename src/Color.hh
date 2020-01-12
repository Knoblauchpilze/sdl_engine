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
            Indigo,
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

          Color
          blend(const Color& color,
                float perc) const noexcept;

          /**
           * @brief - Generates a color from the input color channels values.
           *          Each value is expected to lie in the range `[0; 1]`. If
           *          this is not the case it will be clamped.
           *          A totally opaque alpha channel is assigned.
           * @param r - the value for the red channel.
           * @param g - the value for the greeb channel.
           * @param b - the value for the blue channel.
           * @return - a color with the specified RGB values and opaque alpha.
           */
          static
          Color
          fromRGB(float r,
                  float g,
                  float b) noexcept;

          /**
           * @brief - Similar to `fromRGB` but with user-defined alpha channel.
           *          The alpha channel is also supposed to lie within the range
           *          `[0; 1]`.
           * @param r - the value for the red channel.
           * @param g - the value for the green channel.
           * @param b - the value for the blue channel.
           * @param a - the value for the alpha channel.
           * @return - a color with the specified RGBA values.
           */
          static
          Color
          fromRGBA(float r,
                   float g,
                   float b,
                   float a) noexcept;

          /**
           * @brief - Transforms a color expressed in the `HSV` color space into
           *          a similar color in the `RGB` color space and opaque alpha.
           *          Each of the component is expected to lie within the range
           *          `[0; 1]`.
           *          If this is not the case they are clamped.
           * @param h - the value for the hue of the color.
           * @param s - the value for the saturation of the color.
           * @param v - the value for the `value` of the color.
           * @return - a color with the corresponding RGB values and opaque alpha.
           */
          static
          Color
          fromHSV(float h,
                  float s,
                  float v) noexcept;

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
