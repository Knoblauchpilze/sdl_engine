
# include "Color.hh"

namespace sdl {
  namespace core {
    namespace engine {

      const float Color::sk_opaqueAlpha = 1.0f;
      const float Color::sk_transparentAlpha = 0.0f;

      Color
      Color::fromHSV(float h,
                     float s,
                     float v) noexcept
      {
        // Clamp input values.
        h = std::min(1.0f, std::max(0.0f, h));
        s = std::min(1.0f, std::max(0.0f, s));
        v = std::min(1.0f, std::max(0.0f, v));

        // We will use this article: https://en.wikipedia.org/wiki/HSL_and_HSV#HSL_to_RGB
        // which describes the conversion to apply to transform a `HSV` color to a `RGB`
        // one.
        // Compared to the article our only specificity is that `h` belongs to `[0; 1]`
        // and not `[0; 360]` as expected. This was accounted for in the transformation
        // process.
        float hA = 360.0f * h;

        float c = v * s;
        float hp = hA / 60.0f;
        float x = c * (1.0f - std::abs(std::fmod(hp, 2.0f) - 1.0f));

        float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f;

        if (hp <= 1.0f) {
          r1 = c;
          g1 = x;
          b1 = 0.0f;
        }
        else if (hp < 2.0f) {
          r1 = x;
          g1 = c;
          b1 = 0.0f;
        }
        else if (hp <  3.0f) {
          r1 = 0.0f;
          g1 = c;
          b1 = x;
        }
        else if (hp < 4.0f) {
          r1 = 0.0f;
          g1 = x;
          b1 = c;
        }
        else if (hp < 5.0f) {
          r1 = x;
          g1 = 0.0f;
          b1 = c;
        }
        else {
          r1 = c;
          g1 = 0.0f;
          b1 = x;
        }

        float m = v - c;

        // Return the converted color.
        return sdl::core::engine::Color::fromRGB(r1 + m, g1 + m, b1 + m);
      }

      void
      Color::fromNamedColor(const NamedColor& color,
                            float& r,
                            float& g,
                            float& b) const noexcept
      {
        switch (color) {
          case NamedColor::White:
            r = 1.0f; g = 1.0f; b = 1.0f;
            break;
          case NamedColor::Red:
            r = 1.0f; g = 0.0f; b = 0.0f;
            break;
          case NamedColor::Green:
            r = 0.0f; g = 1.0f; b = 0.0f;
            break;
          case NamedColor::Blue:
            r = 0.0f; g = 0.0f; b = 1.0f;
            break;
          case NamedColor::Yellow:
            r = 1.0f; g = 1.0f; b = 0.0f;
            break;
          case NamedColor::Orange:
            r = 1.0f; g = 0.5f; b = 0.0f;
            break;
          case NamedColor::Cyan:
            r = 0.0f; g = 1.0f; b = 1.0f;
            break;
          case NamedColor::Magenta:
            r = 1.0f; g = 0.0f; b = 1.0f;
            break;
          case NamedColor::Silver:
            r = 0.7529f; g = 0.7529f; b = 0.7529f;
            break;
          case NamedColor::Gray:
            r = 0.5f; g = 0.5f; b = 0.5f;
            break;
          case NamedColor::Maroon:
            r = 0.5f; g = 0.0f; b = 0.0f;
            break;
          case NamedColor::Olive:
            r = 0.5f; g = 0.5f; b = 0.0f;
            break;
          case NamedColor::Pink:
            r = 1.0f; g = 0.7529f; b = 0.7961f;
            break;
          case NamedColor::Purple:
            r = 0.5f; g = 0.0f; b = 0.5f;
            break;
          case NamedColor::Teal:
            r = 0.0f; g = 0.5f; b = 0.5f;
            break;
          case NamedColor::Navy:
            r = 0.0f; g = 0.0f; b = 0.5f;
            break;
          case NamedColor::Black:
            r = 0.0f; g = 0.0f; b = 0.0f;
            break;
          case NamedColor::CorneFlowerBlue:
          default:
            r = 0.3922f; g = 0.5843f; b = 0.9294f;
            break;
        }
      }

    }
  }
}
