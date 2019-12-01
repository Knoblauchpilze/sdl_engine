#ifndef    BRUSH_HH
# define   BRUSH_HH

# include <memory>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Brush: public utils::CoreObject {
        public:

          /**
           * @brief - Creates a new brush with the specified name.
           * @param name - the name of the brush.
           */
          Brush(const std::string& name);

          virtual ~Brush();

          /**
           * @brief - Performs the rendering of the content of this brush using
           *          the provided renderer so that we create a valid texture
           *          from it. Note that the texture is guaranteed to be valid
           *          if the method returns.
           * @param renderer - the renderer to use to perform the drawing of the
           *                   content of this brush.
           * @return - a texture created from the brush's content.
           */
          virtual TextureShPtr
          render(SDL_Renderer* renderer);

        private:

      };

      using BrushShPtr = std::shared_ptr<Brush>;
    }
  }
}

# include "Brush.hxx"

#endif    /* BRUSH_HH */
