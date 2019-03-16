#ifndef    NULL_ENGINE_HH
# define   NULL_ENGINE_HH

# include <string>

# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class NullEngine : public Engine {
        public:

          Window::UUID
          createWindow(const utils::Sizei& size,
                       const std::string& title = std::string("Default SDL window")) override;

          Texture::UUID
          createTexture(const utils::Sizei& size) override;

          void
          setActiveWindow(const Window::UUID& uuid) override;
      };

    }
  }
}

# include "NullEngine.hxx"

#endif    /* NULL_ENGINE_HH */
