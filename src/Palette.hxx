#ifndef    PALETTE_HXX
# define   PALETTE_HXX

# include "Palette.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Palette::Palette(const std::string& name):
        utils::CoreObject(name),
        m_activeGroup(ColorGroup::Active),
        m_disabledColors(),
        m_inactiveColors(),
        m_activeColors()
      {
        setService(std::string("palette"));
      }

      inline
      Color
      Palette::getBackgroundColor() const {
        return getColorForRole(ColorRole::Background);
      }

      inline
      Color
      Palette::getWindowTextColor() const {
        return getColorForRole(ColorRole::WindowText);
      }

      inline
      Color
      Palette::getBaseColor() const {
        return getColorForRole(ColorRole::Base);
      }

      inline
      Color
      Palette::getAlternateBaseColor() const {
        return getColorForRole(ColorRole::AlternateBase);
      }

      inline
      Color
      Palette::getTextColor() const {
        return getColorForRole(ColorRole::Text);
      }

      inline
      Color
      Palette::getButtonColor() const {
        return getColorForRole(ColorRole::Button);
      }

      inline
      Color
      Palette::getButtonTextColor() const {
        return getColorForRole(ColorRole::ButtonText);
      }

      inline
      Color
      Palette::getBrightTextColor() const {
        return getColorForRole(ColorRole::BrightText);
      }

      inline
      Color
      Palette::getLightColor() const {
        return getColorForRole(ColorRole::Light);
      }

      inline
      Color
      Palette::getDarkColor() const {
        return getColorForRole(ColorRole::Dark);
      }

      inline
      Color
      Palette::getMidColor() const {
        return getColorForRole(ColorRole::Mid);
      }

      inline
      Color
      Palette::getShadowColor() const {
        return getColorForRole(ColorRole::Shadow);
      }

      inline
      Color
      Palette::getHighlightColor() const {
        return getColorForRole(ColorRole::Highlight);
      }

      inline
      Color
      Palette::getHighlightedTextColor() const {
        return getColorForRole(ColorRole::HighlightedText);
      }

      inline
      Palette::ColorGroup
      Palette::getActiveGroup() const noexcept {
        return m_activeGroup;
      }

      inline
      void
      Palette::setActiveGroup(const ColorGroup& group) noexcept {
        m_activeGroup = group;
      }

      inline
      Color
      Palette::getColorForRole(const ColorRole& role) const {
        // Use the active group to retrieve the corresponding color.
        return getColorForRole(getActiveGroup(), role);
      }

      inline
      Color
      Palette::getColorForRole(const ColorGroup& group,
                               const ColorRole& role) const
      {
        // Retrieve the correct color based on the group.
        switch (group) {
          case ColorGroup::Disabled:
            return getDisabledColorFromRole(role);
          case ColorGroup::Inactive:
            return getInactiveColorFromRole(role);
          case ColorGroup::Active:
            return getActiveColorFromRole(role);
          default:
            break;
        }

        // This is a problem.
        error(
          std::string("Cannot retrieve color for role ") + std::to_string(static_cast<int>(role)) + " in group " + std::to_string(static_cast<int>(group)),
          std::string("Unknown color group")
        );

        // Silent the compiler's complaint.
        return Color::NamedColor::Black;
      }

      inline
      Color
      Palette::getDisabledColorFromRole(const ColorRole& role) const {
        return getColorFromRole(m_disabledColors, role);
      }

      inline
      Color
      Palette::getInactiveColorFromRole(const ColorRole& role) const {
        return getColorFromRole(m_inactiveColors, role);
      }

      inline
      Color
      Palette::getActiveColorFromRole(const ColorRole& role) const {
        return getColorFromRole(m_activeColors, role);
      }

      inline
      Color
      Palette::getColorFromRole(const std::unordered_map<ColorRole, Color>& colors,
                                const ColorRole& role) const
      {
        const std::unordered_map<ColorRole, Color>::const_iterator color = colors.find(role);

        // Check whether this role is available.
        if (color == colors.cend()) {
          error(
            std::string("Cannot retrieve color role ") + std::to_string(static_cast<int>(role)),
            std::string("Empty role")
          );
        }

        // Return the color for this role.
        return color->second;
      }

      inline
      void
      Palette::setDisabledColor(const ColorRole& role,
                                const Color& color) noexcept
      {
        setColorForRoleAndGroup(m_disabledColors, role, color);
      }

      inline
      void
      Palette::setInactiveColor(const ColorRole& role,
                                const Color& color) noexcept
      {
        setColorForRoleAndGroup(m_inactiveColors, role, color);
      }

      inline
      void
      Palette::setActiveColor(const ColorRole& role,
                              const Color& color) noexcept
      {
        setColorForRoleAndGroup(m_activeColors, role, color);
      }

      inline
      void
      Palette::setColorForRoleAndGroup(std::unordered_map<ColorRole, Color>& colorGroup,
                                       const ColorRole& role,
                                       const Color& color) noexcept
      {
        colorGroup[role] = color;
      }

      inline
      void
      Palette::copyInactiveFromActiveColorGroup() noexcept {
        m_inactiveColors = m_activeColors;
      }

    }
  }
}

#endif    /* PALETTE_HXX */
