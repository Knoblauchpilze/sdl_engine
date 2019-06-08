
# include "Texture.hh"
# include "RendererState.hh"

namespace {
  /**
   * @brief - Builds a top left SDL_Rect object from the input box.
   * @return - a sdl rect object based on the input description of the box.
   */
  template <typename CoordinateType>
  inline
  SDL_Rect
  toSDLRect(const utils::Box<CoordinateType>& box) noexcept {
    return SDL_Rect{
      static_cast<int>(box.getLeftBound()),
      static_cast<int>(box.getBottomBound()),
      static_cast<int>(box.w()),
      static_cast<int>(box.h())
    };
  }
}

namespace sdl {
  namespace core {
    namespace engine {

      void
      Texture::fill(const Palette& palette)
      {
        // Performs the creation of the texture using the dedicated handler
        // which will only create it once.
        createOnce();

        // Retrieve the color to use to fill the texture from the palette.
        SDL_Color color = palette.getColorForRole(getRole()).toSDLColor();

        // Save the current state of the renderer: this will automatically handle restoring
        // the state upon destroying this object.
        RendererState state(getRenderer());

        // Configure the renderer to draw on the texture, apply the color and perform
        // the filling.
        SDL_SetRenderTarget(getRenderer(), m_texture);
        SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(getRenderer());

        // Also apply alpha modulation for this texture.
        setAlpha(palette.getColorForRole(getRole()));
      }

      void
      Texture::draw(utils::Boxf* box,
                    SDL_Texture* on)
      {
        // Performs the creation of the texture using the dedicated handler
        // which will only create it once.
        createOnce();

        // Save the renderer state so that we can restore the
        // initial rendering target and properties (color, etc.).
        RendererState state(getRenderer());

        // Set the input texture as rendering target.
        SDL_SetRenderTarget(getRenderer(), on);

        // Draw the input texture at the corresponding location.
        if (box == nullptr) {
          SDL_RenderCopy(getRenderer(), m_texture, nullptr, nullptr);
        }
        else {
          SDL_Rect dstArea = toSDLRect(*box);
          SDL_RenderCopy(getRenderer(), m_texture, nullptr, &dstArea);
        }
      }

      void
      Texture::setAlpha(const Color& color) {
        // Performs the creation of the texture using the dedicated handler
        // which will only create it once.
        createOnce();

        // Assign the alpha channel.
        SDL_SetTextureAlphaMod(m_texture, color.toSDLColor().a);
      }

      utils::Sizei
      Texture::query() {
        // Performs the creation of the texture using the dedicated handler
        // which will only create it once.
        createOnce();

        // Query the texture.
        int w, h;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

        return utils::Sizei(w, h);
      }

    }
  }
}
