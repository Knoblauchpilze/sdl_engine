#ifndef    FONTFACTORY_HH
# define   FONTFACTORY_HH

# include <memory>
# include <unordered_map>
# include <core_utils/CoreObject.hh>
# include "Palette.hh"
# include "ColoredFont.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FontFactory: utils::CoreObject {
        public:

          FontFactory();

          ~FontFactory();

          FontFactory(const FontFactory& other) = delete;

          void operator=(const FontFactory& other) = delete;

          ColoredFontShPtr
          createColoredFont(const std::string& name,
                            const Palette& palette,
                            int size = 25);

        private:

          void
          initializeTTFLib();

          void
          releaseTTFLib();

          FontShPtr
          createFont(const std::string& name);

          void
          releaseFonts();

        private:

          std::unordered_map<std::string, FontShPtr> m_fonts;

      };

      using FontFactoryShPtr = std::shared_ptr<FontFactory>;
    }
  }
}

# include "FontFactory.hxx"

#endif    /* FONTFACTORY_HH */
