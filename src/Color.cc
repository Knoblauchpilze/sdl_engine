
# include "Color.hh"

namespace sdl {
  namespace core {
    namespace engine {

      const float Color::sk_opaqueAlpha = 1.0f;
      const float Color::sk_transparentAlpha = 0.0f;

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
          case NamedColor::Purple:
            r = 0.5f; g = 0.0f; b = 0.5f;
            break;
          case NamedColor::Teal:
            r = 0.0f; g = 0.5f; b = 0.5f;
            break;
          case NamedColor::Navy:
            r = 0.0f; g = 0.0f; b = 0.5f;
            break;
          case NamedColor::CorneFlowerBlue:
            r = 0.3922f; g = 0.0f; b = 0.0f;
            break;
          case NamedColor::Black:
            r = 0.0f; g = 0.0f; b = 0.0f;
            break;
          default:
            r = 0.0f; g = 0.5843f; b = 0.9294f;
            break;
        }
      }

    }
  }
}
