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

          void
          setActiveWindow(const Window::UUID& uuid) override;

          void
          setWindowIcon(const Window::UUID& uuid,
                        const std::string& icon) override;

          void
          clearWindow(const Window::UUID& uuid) override;

          void
          renderWindow(const Window::UUID& uuid) override;

          void
          destroyWindow(const Window::UUID& uuid) override;

          Texture::UUID
          createTexture(const utils::Sizei& size) override;

          Texture::UUID
          createTextureFromFile(const std::string& file) override;

          Texture::UUID
          createTextureFromText(const std::string& text,
                                ColoredFontShPtr font) override;

          void
          fillTexture(const Texture::UUID& uuid,
                      const Palette& palette) override;

          void
          setTextureAlpha(const Texture::UUID& uuid,
                          const Color& color) override;

          void
          drawTexture(const Texture::UUID& tex,
                      const Texture::UUID* on = nullptr,
                      utils::Boxf* where = nullptr) override;

          utils::Sizei
          queryTexture(const Texture::UUID& uuid) override;

          void
          destroyTexture(const Texture::UUID& uuid) override;
      };

    }
  }
}

# include "NullEngine.hxx"

#endif    /* NULL_ENGINE_HH */
