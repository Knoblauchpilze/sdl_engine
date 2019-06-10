
# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Palette
      Palette::fromButtonColor(const engine::Color& color) noexcept {
        Palette palette;

        // Initialize the palette from the input button color.
        palette.initFromButtonColor(color);

        // Return the built-in palette.
        return palette;
      }

      void
      Palette::initFromButtonColor(const Color& color) {
        // The `Background` color is identical to the input button's color.
        Color bg = color;

        // The `Button` color is obviously equal to the input color.
        Color button = color;

        // The `WindowText` and `Base` color are set to `Black` and `White`
        // based on the luminance of the input `color`.
        const float brightness = color.brightness();

        Color windowText;
        Color base;
        if (brightness >= 0.5f) {
          windowText = Color::NamedColor::Black;
          base = Color::NamedColor::White;
        }
        else {
          windowText = Color::NamedColor::White;
          base = Color::NamedColor::Black;
        }

        // The alternate base is a mix between the `Base` and the `Button` color.
        Color alternateBase = base.mix(button);

        // Assign each color group from the computed colors.
        setColorGroupFromColors(
          ColorGroup::Disabled,
          bg,
          button.darken(0.5f),
          bg,
          alternateBase,
          button.darken(0.5f),
          button,
          bg,
          Color::NamedColor::White,
          button.darken(0.66f),
          button.darken(0.5f),
          button.darken(0.66f),
          Color::NamedColor::Black,
          Color::NamedColor::Navy,
          Color::NamedColor::White
        );

        setColorGroupFromColors(
          ColorGroup::Active,
          bg,
          windowText,
          base,
          alternateBase,
          windowText,
          button,
          windowText,
          Color::NamedColor::White,
          button.brighten(1.5f),
          button.darken(0.5f),
          button.darken(0.66f),
          Color::NamedColor::Black,
          Color::NamedColor::Navy,
          Color::NamedColor::White
        );

        copyInactiveFromActiveColorGroup();
      }

      void
      Palette::setColorGroupFromColors(const ColorGroup& group,
                                       const Color& background,
                                       const Color& windowText,
                                       const Color& base,
                                       const Color& alternateBase,
                                       const Color& text,
                                       const Color& button,
                                       const Color& buttonText,
                                       const Color& brightText,
                                       const Color& light,
                                       const Color& dark,
                                       const Color& mid,
                                       const Color& shadow,
                                       const Color& highlight,
                                       const Color& highlightedText)
      {
        std::unordered_map<ColorRole, Color>* colors = nullptr;

        switch (group) {
          case ColorGroup::Disabled:
            colors = &m_disabledColors;
            break;
          case ColorGroup::Inactive:
            colors = &m_inactiveColors;
            break;
          case ColorGroup::Active:
            colors = &m_activeColors;
            break;
          default:
            break;
        }

        // Check whether the input color group is valid.
        if (colors == nullptr) {
          error(
            std::string("Cannot assign color role from input color group ") + std::to_string(static_cast<int>(group)),
            std::string("Unknown color group")
          );
        }

        setColorForRoleAndGroup(*colors, ColorRole::Background, background);
        setColorForRoleAndGroup(*colors, ColorRole::WindowText, windowText);
        setColorForRoleAndGroup(*colors, ColorRole::Base, base);
        setColorForRoleAndGroup(*colors, ColorRole::AlternateBase, alternateBase);
        setColorForRoleAndGroup(*colors, ColorRole::Text, text);
        setColorForRoleAndGroup(*colors, ColorRole::Button, button);
        setColorForRoleAndGroup(*colors, ColorRole::ButtonText, buttonText);

        setColorForRoleAndGroup(*colors, ColorRole::BrightText, brightText);
        setColorForRoleAndGroup(*colors, ColorRole::Light, light);
        setColorForRoleAndGroup(*colors, ColorRole::Dark, dark);
        setColorForRoleAndGroup(*colors, ColorRole::Mid, mid);
        setColorForRoleAndGroup(*colors, ColorRole::Shadow, shadow);
        setColorForRoleAndGroup(*colors, ColorRole::Highlight, highlight);
        setColorForRoleAndGroup(*colors, ColorRole::HighlightedText, highlightedText);
      }

    }
  }
}

