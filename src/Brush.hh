#ifndef    BRUSH_HH
# define   BRUSH_HH

# include <memory>
# include <SDL2/SDL.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "Texture.hh"
# include "Palette.hh"
# include "Gradient.hh"
# include "SurfaceTexture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class Brush: public utils::CoreObject {
        public:

          /**
           * @brief - Represents a direction in a 2D coordinate space.
           */
          enum class Direction {
            Horizontal,
            Vertical
          };

        public:

          /**
           * @brief - Creates a new brush with the specified name. Note that
           *          this brush is not thread safe and should ever be used
           *          by a single thread.
           *          It creates a representation of the its content in an
           *          opaque way and can then be transformed into a texture
           *          through an engine method. The rendering capabilities
           *          can be used outside of the main thread unlike most calls
           *          to the drawing method of the engine.
           * @param name - the name of the brush.
           * @param ownsTexture - `true` if the brush owns its internal texture
           *                      and `false` otherwise.
           */
          Brush(const std::string& name,
                bool ownsTexture = true);

          /**
           * @brief - Create a new brush with the specified name and size. A
           *          canvas matching the input size is allocated right upon
           *          building this object.
           *          Note that this method internally calls `create` but does
           *          not request a `clear` operation.
           * @param name - the name of the brush.
           * @param size - the size of the canvas to create for this brush.
           * @param ownsTexture - `true` if this brush owns its related texture
           *                      and `false` otherwise.
           */
          Brush(const std::string& name,
                const utils::Sizef& size,
                bool ownsTexture = true);

          virtual ~Brush();

          /**
           * @brief - Assign a new color to be used when performing drawing
           *          operations. This color replaces any existing color.
           * @param color - the new drawing color to use.
           */
          void
          setColor(const Color& color) noexcept;

          /**
           * @brief - Assign a new clear color to use when clearing the internal
           *          canvas. This color is distinct from the drawing color.
           * @param color - the new clear color to use.
           */
          void
          setClearColor(const Color& color) noexcept;

          /**
           * @brief - Used to performt he creation of a new canvas for this brush
           *          with the specified dimension. Any existing canvas is cleared.
           *          Nothing apart from the creation is done unless the `fill`
           *          boolean is set to `true` in case a clear operation (equivalent
           *          to calling `clear`) method is performed.
           * @param size - the size of the canvas to create.
           * @param fill - true if a `clear` operation should be scheduled after the
           *               creation of the canvas has been performed.
           */
          void
          create(const utils::Sizef& size,
                 bool fill = false);

          /**
           * @brief - Used to create a texture from the input data. The vector is
           *          interpreted as an array with the specified dimensions. From
           *          this array, the brush creates a surface with a default color
           *          format that can be used to create a texture.
           *          Note that the `colors` vector is emptied by the method and
           *          will not contain any data after the call.
           * @param dims - the dimensions of the `colors` vector when interpreted
           *               as a 2D array.
           * @param colors - the raw data of the surface to associate to the brush,
           *                 as a 1D array.
           */
          void
          createFromRaw(const utils::Sizei& dims,
                        std::vector<Color>& colors);

          /**
           * @brief - Used to clear the whole canvas if any with the clear color.
           *          Note that nothing happens if the canvas has not been allocated
           *          yet.
           */
          void
          clear() noexcept;

          /**
           * @brief - Used to draw a line at the coordinate `coord` representing a
           *          position in the local brush's canvas coordinate frame. The
           *          direction of the line is specified by the `dir` argument.
           *          If no canvas is defined an error is raised. The line is drawn
           *          using the current color (see `setColor` to modify it).
           * @param dir - the direction of the line to create.
           * @param coord - a value representing the position of the line to draw.
           */
          void
          drawLine(const Direction& dir,
                   float coord);

          /**
           * @brief - Used to perform the drawing of the gradient into the internal
           *          brush's canvas. NO allocation is performed meaning that if no
           *          canvas is attached already to the brush an error is raised.
           * @param grad - the gradient to represent with this brush.
           */
          void
          drawGradient(const Gradient& grad);

          /**
           * @brief - Performs the rendering of the content of this brush using
           *          the provided renderer so that we create a valid texture
           *          from it. Note that the texture is guaranteed to be valid
           *          if the method returns.
           *          The created texture is *not* set to take ownership of the
           *          canvas used to create it.
           * @param renderer - the renderer to use to perform the drawing of the
           *                   content of this brush.
           * @return - a texture created from the brush's content.
           */
          virtual TextureShPtr
          render(SDL_Renderer* renderer);

        private:

          /**
           * @brief - Used to retrieve the role assigne dto any texture created
           *          by this brush.
           * @return - a color role used to create the texture from the data of
           *           this brush.
           */
          static
          Palette::ColorRole
          getDefaultTextureRole() noexcept;

          /**
           * @brief - Used to check whether a canvas is available for this brush. If
           *          this is not the case most of the operations available for this
           *          brush will return without doing anything.
           * @return - `true` if a valid canvas is assigned to this brush and `false`
           *           otherwise.
           */
          bool
          hasCanvas() const noexcept;

          /**
           * @brief - USed to check whether some raw data is available for this brush.
           * @return - `true` if raw data is used to describe this texture and `false`
           *           otherwise.
           */
          bool
          hasRawData() const noexcept;

          /**
           * @brief - Used to destroy any existing canvas.
           */
          void
          destroy() noexcept;

        private:

          /**
           * @brief - The color to use when performing drawing operations.
           */
          Color m_color;

          /**
           * @brief - The color to use when performing clear operations.
           */
          Color m_clearColor;

          /**
           * @brief - The canvas to use to perform drawing operations.
           */
          SDL_Surface* m_canvas;

          /**
           * @brief - A raw array of pixels which can be used to describe
           *          the canvas, rather than using the texture itself.
           */
          SurfaceTexture::RawSurfaceDataShPtr m_rawData;

          /**
           * @brief - Use this value to determine whether the surface is
           *          owned by the brush or if it should not be released
           *          upon destroying the brush because it will be used
           *          by external elements.
           *          Note that this does not include the potential free
           *          operations performed when some methods like `create`
           *          are called on an existing brush (in which case the
           *          internal surface is always freed).
           */
          bool m_ownsCanvas;
      };

      using BrushShPtr = std::shared_ptr<Brush>;
    }
  }
}

# include "Brush.hxx"

#endif    /* BRUSH_HH */
