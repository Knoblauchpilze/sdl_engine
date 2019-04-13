#ifndef    COLOR_HXX
# define   COLOR_HXX

# include "Color.hh"
# include <maths_utils/ComparisonUtils.hh>

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Color::Color(const NamedColor& color):
        m_r(),
        m_g(),
        m_b(),
        m_a(sk_opaqueAlpha)
      {
        fromNamedColor(color, m_r, m_g, m_b);
      }

      inline
      Color::Color(const float& r,
                   const float& g,
                   const float& b,
                   const float& a):
        m_r(r),
        m_g(g),
        m_b(b),
        m_a(a)
      {}

      inline
      const float&
      Color::r() const noexcept {
        return m_r;
      }

      inline
      float&
      Color::r() noexcept {
        return m_r;
      }

      inline
      const float&
      Color::g() const noexcept {
        return m_g;
      }

      inline
      float&
      Color::g() noexcept {
        return m_g;
      }

      inline
      const float&
      Color::b() const noexcept {
        return m_b;
      }

      inline
      float&
      Color::b() noexcept {
        return m_b;
      }

      inline
      const float&
      Color::a() const noexcept {
        return m_a;
      }

      inline
      float&
      Color::a() noexcept {
        return m_a;
      }

      inline
      bool
      Color::isOpaque() const noexcept {
        return utils::fuzzyEqual(m_a, sk_opaqueAlpha);
      }

      inline
      bool
      Color::isTransparent() const noexcept {
        return utils::fuzzyEqual(m_a, sk_transparentAlpha);
      }

      inline
      float
      Color::brightness() const noexcept {
        return 0.299f * m_r + 0.587f * m_g + 0.114f * m_b;
      }

      inline
      Color
      Color::brighten(const float& factor) noexcept {
        return fromRGBA(
          std::min(1.0f, m_r * std::abs(factor)),
          std::min(1.0f, m_g * std::abs(factor)),
          std::min(1.0f, m_b * std::abs(factor)),
          m_a
        );
      }

      inline
      Color
      Color::darken(const float& factor) noexcept {
        return fromRGBA(
          std::min(1.0f, m_r * std::abs(factor)),
          std::min(1.0f, m_g * std::abs(factor)),
          std::min(1.0f, m_b * std::abs(factor)),
          m_a
        );
      }

      inline
      SDL_Color
      Color::toSDLColor() const noexcept {
        return SDL_Color{
          static_cast<uint8_t>(std::min(std::max(m_r, 0.0f), 1.0f) * 255.0f),
          static_cast<uint8_t>(std::min(std::max(m_g, 0.0f), 1.0f) * 255.0f),
          static_cast<uint8_t>(std::min(std::max(m_b, 0.0f), 1.0f) * 255.0f),
          static_cast<uint8_t>(std::min(std::max(m_a, 0.0f), 1.0f) * 255.0f),
        };
      }

      inline
      std::string
      Color::toString() const noexcept {
        return
          std::string("[Color: ") +
          "r: " + std::to_string(static_cast<int>(255.0f * r())) + ", " +
          "g: " + std::to_string(static_cast<int>(255.0f * g())) + ", " +
          "b: " + std::to_string(static_cast<int>(255.0f * b())) + ", " +
          "a: " + std::to_string(static_cast<int>(255.0f * a())) + "]";
      }

      inline
      Color
      Color::mix(const Color& color) const noexcept {
        return Color(
          std::min(1.0f, (r() + color.r()) / 2.0f),
          std::min(1.0f, (g() + color.g()) / 2.0f),
          std::min(1.0f, (b() + color.b()) / 2.0f),
          std::min(1.0f, (a() + color.a()) / 2.0f)
        );
      }

      inline
      Color
      Color::fromRGB(const float& r,
                     const float& g,
                     const float& b) noexcept
      {
        return Color(r, g, b, sk_opaqueAlpha);
      }

      inline
      Color
      Color::fromRGBA(const float& r,
                      const float& g,
                      const float& b,
                      const float& a) noexcept
      {
        return Color(r, g, b, a);
      }

    }
  }
}

inline
std::ostream&
operator<<(const sdl::core::engine::Color& color, std::ostream& out) noexcept {
  return operator<<(out, color);
}

inline
std::ostream&
operator<<(std::ostream& out, const sdl::core::engine::Color& color) noexcept {
  out << color.toString();
  return out;
}

#endif    /* COLOR_HXX */
