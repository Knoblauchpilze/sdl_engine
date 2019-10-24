
# include "Texture.hh"
# include "TextureUtils.hxx"
# include "RendererState.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      Texture::fill(const Palette& palette,
                    const utils::Boxf* area)
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
        // the filling. We also need to handle filling only part of the texture if the
        // `area` argument is not null. This is done by either:
        // a. if the `area` is null we just clear the renderer target.
        // b. if the `area` is not null we just draw a rectangle at the specified area.

        // Assign the renderer target.
        SDL_SetRenderTarget(getRenderer(), m_texture);

        // Assign the renderer draw color.
        SDL_SetRenderDrawColor(getRenderer(), color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

        // Perofrm either the filling of the rectangle drawing based on the input `area`.
        if (area == nullptr) {
          SDL_RenderClear(getRenderer());
        }
        else {
          SDL_Rect dstRect = toSDLRect(*area);
          SDL_RenderFillRect(getRenderer(), &dstRect);
        }

        // Also apply alpha modulation for this texture.
        setAlpha(palette.getColorForRole(getRole()));
      }

      void
      Texture::draw(const utils::Boxf* from,
                    const utils::Boxf* box,
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
        if (from == nullptr) {
          if (box == nullptr) {
            SDL_RenderCopy(getRenderer(), m_texture, nullptr, nullptr);
          }
          else {
            SDL_Rect dstArea = toSDLRect(*box);
            SDL_RenderCopy(getRenderer(), m_texture, nullptr, &dstArea);
          }
        }
        else {
          SDL_Rect srcArea = toSDLRect(*from);
          if (box == nullptr) {
            SDL_RenderCopy(getRenderer(), m_texture, &srcArea, nullptr);
          }
          else {
            SDL_Rect dstArea = toSDLRect(*box);
            SDL_RenderCopy(getRenderer(), m_texture, &srcArea, &dstArea);
          }
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

      utils::Sizef
      Texture::query() {
        // Performs the creation of the texture using the dedicated handler
        // which will only create it once.
        createOnce();

        // Query the texture.
        int w, h;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

        return utils::Sizef(static_cast<float>(w), static_cast<float>(h));
      }

    }
  }
}
