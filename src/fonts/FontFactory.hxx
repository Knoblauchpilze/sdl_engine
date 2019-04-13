#ifndef    FONTFACTORY_HXX
# define   FONTFACTORY_HXX

# include "FontFactory.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FontFactory::FontFactory():
        utils::CoreObject(std::string("font_factory")),
        m_fonts()
      {
        initializeTTFLib();
      }

      inline
      FontFactory::~FontFactory() {
        releaseFonts();
        releaseTTFLib();
      }

      inline
      ColoredFontShPtr
      FontFactory::createColoredFont(const std::string& name,
                                     const Palette& palette,
                                     const int& size)
      {
        return std::make_shared<ColoredFont>(
          createFont(name),
          palette,
          size
        );
      }

      inline
      FontShPtr
      FontFactory::createFont(const std::string& name) {
        // Try to find the requested font from its name.
        std::unordered_map<std::string, FontShPtr>::const_iterator font = m_fonts.find(name);
        if (font != m_fonts.cend()) {
          return font->second;
        }

        // Name not found, create it.
        m_fonts[name] = std::make_shared<Font>(name);

        // Return the created value.
        return m_fonts[name];
      }

      inline
      void
      FontFactory::releaseFonts() {
        m_fonts.clear();
      }

    }
  }
}

#endif    /* FONTFACTORY_HXX */
