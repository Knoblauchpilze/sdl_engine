
# include "Font.hh"

namespace sdl {
  namespace core {
    namespace engine {

      Font::Font(const std::string& name):
        utils::CoreObject(name),
        m_fonts()
      {
        setService(std::string("font"));
      }

      Font::Font(const Font& other):
        utils::CoreObject(other.getName()),
        m_fonts(other.m_fonts)
      {
        // Nothing to do.
      }

    }
  }
}
