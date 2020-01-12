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
      Color::Color(float r,
                   float g,
                   float b,
                   float a):
        m_r(std::min(1.0f, std::max(0.0f, r))),
        m_g(std::min(1.0f, std::max(0.0f, g))),
        m_b(std::min(1.0f, std::max(0.0f, b))),
        m_a(std::min(1.0f, std::max(0.0f, a)))
      {}

      inline
      bool
      Color::operator==(const Color& rhs) const noexcept {
        return
          std::abs(m_r - rhs.m_r) < std::numeric_limits<float>::min() &&
          std::abs(m_g - rhs.m_g) < std::numeric_limits<float>::min() &&
          std::abs(m_b - rhs.m_b) < std::numeric_limits<float>::min() &&
          std::abs(m_a - rhs.m_a) < std::numeric_limits<float>::min()
        ;
      }

      inline
      bool
      Color::operator!=(const Color& rhs) const noexcept {
        return !operator==(rhs);
      }

      inline
      float
      Color::r() const noexcept {
        return m_r;
      }

      inline
      float&
      Color::r() noexcept {
        return m_r;
      }

      inline
      float
      Color::rU() const noexcept {
        return static_cast<uint8_t>(std::min(std::max(m_r, 0.0f), 1.0f) * 255.0f);
      }

      inline
      float
      Color::g() const noexcept {
        return m_g;
      }

      inline
      float&
      Color::g() noexcept {
        return m_g;
      }

      inline
      float
      Color::gU() const noexcept {
        return static_cast<uint8_t>(std::min(std::max(m_g, 0.0f), 1.0f) * 255.0f);
      }

      inline
      float
      Color::b() const noexcept {
        return m_b;
      }

      inline
      float&
      Color::b() noexcept {
        return m_b;
      }

      inline
      float
      Color::bU() const noexcept {
        return static_cast<uint8_t>(std::min(std::max(m_b, 0.0f), 1.0f) * 255.0f);
      }

      inline
      float
      Color::a() const noexcept {
        return m_a;
      }

      inline
      float&
      Color::a() noexcept {
        return m_a;
      }

      inline
      float
      Color::aU() const noexcept {
        return static_cast<uint8_t>(std::min(std::max(m_a, 0.0f), 1.0f) * 255.0f);
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
      Color::brighten(float factor) noexcept {
        return fromRGBA(
          std::min(1.0f, m_r * std::abs(factor)),
          std::min(1.0f, m_g * std::abs(factor)),
          std::min(1.0f, m_b * std::abs(factor)),
          m_a
        );
      }

      inline
      Color
      Color::darken(float factor) noexcept {
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
      Color::blend(const Color& color,
                   float perc) const noexcept {
        return Color(
          perc * r() + (1.0f - perc) * color.r(),
          perc * g() + (1.0f - perc) * color.g(),
          perc * b() + (1.0f - perc) * color.b(),
          a()
        );
      }

      inline
      Color
      Color::fromRGB(float r,
                     float g,
                     float b) noexcept
      {
        return Color(r, g, b, sk_opaqueAlpha);
      }

      inline
      Color
      Color::fromRGBA(float r,
                      float g,
                      float b,
                      float a) noexcept
      {
        return Color(r, g, b, a);
      }

    }
  }
}

inline
std::ostream&
operator<<(std::ostream& out, const sdl::core::engine::Color& color) noexcept {
  out << color.toString();
  return out;
}

inline
std::ostream&
operator<<(const sdl::core::engine::Color& color, std::ostream& out) noexcept {
  return operator<<(out, color);
}

#endif    /* COLOR_HXX */
