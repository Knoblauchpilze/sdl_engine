#ifndef    PALETTE_HH
# define   PALETTE_HH

# include <memory>
# include <unordered_map>
# include <core_utils/CoreObject.hh>
# include "Color.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Palette: public utils::CoreObject {
        public:

          enum class ColorRole {
            Background,      //<! - A general background color.
            WindowText,      //<! - A general foreground color.
            Base,            //<! - Used mostly as the background color for text entry widgets.
            AlternateBase,   //<! - Used as the alternate background color in viwes with alternating rows.
            Text,            //<! - The foreground color used with `Base`. This is usually the same as the `WindowText`.
            Button,          //<! - The general button background color.
            ButtonText,      //<! - A foreground color used with the `Button` color.
            BrightText,      //<! - A text color that is very different from `WindowText`.

            Light,           //<! - Lighter than `Button` color.
            Dark,            //<! - Darker than `Button`.
            Mid,             //<! - Between `Button` and `Dark`.
            Shadow,          //<! - A very dark color. `Black` by default.
            Highlight,       //<! - A color to indicate a selected item or the current item. `CorneFlowerBlue` by default.
            HighlightedText  //<! - A text color that contrasts with `Highlight`. `White` by default.
          };

          enum class ColorGroup {
            Disabled,  //<! - Used for elements which cannot receive focus ("greyed out").
            Active,    //<! - Used for elements with keyboard focus.
            Inactive   //<! - Used for active widgets with no focus.
          };

        public:

          ~Palette() = default;

          Color
          getBackgroundColor() const;

          Color
          getWindowTextColor() const;

          Color
          getBaseColor() const;

          Color
          getAlternateBaseColor() const;

          Color
          getTextColor() const;

          Color
          getButtonColor() const;

          Color
          getButtonTextColor() const;

          Color
          getBrightTextColor() const;

          Color
          getLightColor() const;

          Color
          getDarkColor() const;

          Color
          getMidColor() const;

          Color
          getShadowColor() const;

          Color
          getHighlightColor() const;

          Color
          getHighlightedTextColor() const;

          ColorGroup
          getActiveGroup() const noexcept;

          void
          setActiveGroup(const ColorGroup& group) noexcept;

          Color
          getColorForRole(const ColorRole& role) const;

          Color
          getColorForRole(const ColorGroup& group,
                          const ColorRole& role) const;

          static
          Palette
          fromButtonColor(const Color& color) noexcept;

          /**
           * @brief - Defines a new color for the input role. The color
           *          is assumed to refer to the active group. A suited
           *          color is deduced for the other color groups.
           * @param role - the role for which the color should be set.
           * @param color - the color to associate to the role.
           */
          void
          setColorForRole(const ColorRole& role,
                          const Color& color);

        private:

          Palette(const std::string& name = std::string("Palette"));

          Color
          getDisabledColorFromRole(const ColorRole& role) const;

          Color
          getInactiveColorFromRole(const ColorRole& role) const;

          Color
          getActiveColorFromRole(const ColorRole& role) const;

          Color
          getColorFromRole(const std::unordered_map<ColorRole, Color>& colors,
                           const ColorRole& role) const;

          void
          initFromButtonColor(const Color& color);

          void
          setDisabledColor(const ColorRole& role,
                           const Color& color) noexcept;

          void
          setInactiveColor(const ColorRole& role,
                           const Color& color) noexcept;

          void
          setActiveColor(const ColorRole& role,
                         const Color& color) noexcept;

          void
          setColorForRoleAndGroup(std::unordered_map<ColorRole, Color>& colorGroup,
                                  const ColorRole& role,
                                  const Color& color) noexcept;

          void
          setColorGroupFromColors(const ColorGroup& group,
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
                                  const Color& highlightedText);

          void
          copyInactiveFromActiveColorGroup() noexcept;

        private:

          ColorGroup m_activeGroup;
          std::unordered_map<ColorRole, Color> m_disabledColors;
          std::unordered_map<ColorRole, Color> m_inactiveColors;
          std::unordered_map<ColorRole, Color> m_activeColors;

      };

      using PaletteShPtr = std::shared_ptr<Palette>;
    }
  }
}

# include "Palette.hxx"

#endif    /* PALETTE_HH */
