#ifndef    SDL_ENGINE_HH
# define   SDL_ENGINE_HH

# include <mutex>
# include <unordered_map>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "Engine.hh"
# include "Window.hh"
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class SdlEngine : public Engine, public utils::CoreObject {
        public:

          SdlEngine();

          virtual ~SdlEngine();

          Window::UUID
          createWindow(const utils::Sizei& size,
                       const std::string& title = std::string("Default SDL window")) override;

          Texture::UUID
          createTexture(const utils::Sizei& size) override;

          void
          setActiveWindow(const Window::UUID& uuid) override;

        private:

          void
          initializeSDLLib();

          void
          releaseSDLLib();

        private:

          using WindowsMap = std::unordered_map<Window::UUID, WindowShPtr>;
          using TexturesMap = std::unordered_map<Texture::UUID, TextureShPtr>;

          std::mutex m_locker;

          Window::UUID m_winID;
          WindowsMap m_windows;
          WindowShPtr m_activeWin;

          Texture::UUID m_texID;
          TexturesMap m_textures;
      };

    }
  }
}

# include "SdlEngine.hxx"

#endif    /* SDL_ENGINE_HH */
