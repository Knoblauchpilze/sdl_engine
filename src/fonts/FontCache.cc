
# include "FontCache.hh"

namespace sdl {
  namespace core {
    namespace engine {

      FontCache::FontCache(const std::string& name,
                           TTF_Font* font):
        utils::CoreObject(name),

        m_font(font),
        m_glyphs()
      {
        // Check that the font is valid.
        if (m_font == nullptr) {
          error(
            std::string("Cannot create font cache from font"),
            std::string("Invalid null font")
          );
        }

        setService("font_cache");
      }

      SDL_Surface*
      FontCache::render(const std::string& text,
                        const Color& color,
                        bool exact)
      {
        // Traverse the input text and render each needed glyph while advancing on the
        // output surface which allows to position the glyphs next to each other.
        // Each glyph will be retrieved from the cache if possible and loaded if not.
        // Also we will perform the rendering of the glyphs on a base texture which
        // will then be returned.
        FontMetrics fm = getMetrics();

        // First allocate the texture which will receive each individual glyph. To do
        // that we have to retrieve the dimensions of the text.
        utils::Sizef size = querySize(text, exact);

        int w = static_cast<int>(std::round(size.w()));
        int h = fm.height;
        if (exact) {
          h = static_cast<int>(std::round(size.h()));
        }

        // We cannot rely on the default mask because we want to use the alpha channel.
        // So we have to provide a full mask for all the colors (otherwise we could run
        // into trouble because the `SDL` could apply some masks which would conflict
        // with the one we provide for the alpha channel).
        SDL_Surface* out = SDL_CreateRGBSurface(0, w, h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        if (out == nullptr) {
          error(
            std::string("Could not render text \"") + text + "\" with font \"" + getName() + "\"",
            SDL_GetError()
          );
        }

        // Fill the texture with foreground color and `0` alpha. Given the mask we used
        // we need to format the pixel to use to fill the texture accordingly.
        SDL_Color c = color.toSDLColor();
        SDL_FillRect(out, nullptr, (c.r << 16) | (c.g << 8) | c.b);

        // Traverse the input text and blit each individual glyph.
        int advance = 0;

        for (unsigned id = 0 ; id < text.size() ; ++id) {
          // Render the glyph.

          SDL_Surface* g = renderGlyph(text[id], color);

          // Get the metrics associated to it.
          GlyphMetrics gm = getMetrics(text[id]);

          // Compute the source and destination area.
          SDL_Rect srcRect = SDL_Rect{
            exact ? gm.minX : 0,
            exact ? fm.ascent - gm.maxY : 0,
            exact ? gm.maxX - gm.minX : g->w,
            exact ? gm.maxY - gm.minY : g->h
          };

          SDL_Rect dstRect = SDL_Rect{
            exact ? advance + gm.minX : advance,
            exact ? fm.ascent - gm.maxY : 0,
            0, // Not used
            0  // Not used
          };

          advance += (exact ? gm.maxX - gm.minX : std::max(gm.advance, gm.maxX));

          // Blit the glyph in the output texture with the right mode (i.e. based on
          // whether some spacing should be applied to the text).
          SDL_BlitSurface(g, &srcRect, out, &dstRect);
        }

        // Return the produced texture.
        return out;
      }

      utils::Sizef
      FontCache::querySize(const std::string& text,
                           bool exact)
      {
        // The font system allows to render glyphs using a virtual baseline where all
        // the characters are laid upon. Each character has a vertical extent which
        // can lead its visual representation to go above or below the baseline. The
        // user can query the maximum extent of the vertical extent of any font using
        // the `TTF_FontAscent` and `TTF_FontDescent`: combining these two numbers is
        // required to compute the maximum vertical extent that a text rendered with
        // the font can have.
        // Similar function are used to retrieve horizontal information so that the
        // individual characters are spaced correctly along the horitontal axis.
        // The goal of this method is to combine all these information to retrieve the
        // size that the input `text` would have using these metrics. Basically what
        // we want to do is to perform a traversal of the input text and advance on a
        // virtual texture based on the character of each processed glyph. We will
        // accumulate the data along the way.
        int maxAscent = std::numeric_limits<int>::lowest();
        int minAscent = std::numeric_limits<int>::max();

        int accumulatedW = 0;

        for (unsigned id = 0u; id < text.size() ; ++id) {
          // Check whether the current character is provided by the font.
          if (!exists(text[id])) {
            warn(std::string("Could not determine size of glyph '") + std::to_string(static_cast<int>(text[id])) + "' (not found in font \"" + getName() + "\"");

            // The size will probably be inaccurate but what can we do ?
            continue;
          }

          // To aggregate the ascent for this character we need to use the maximum glyph
          // ascent and descent.
          GlyphMetrics m = getMetrics(text[id]);

          maxAscent = std::max(maxAscent, m.maxY);
          minAscent = std::min(minAscent, m.minY);

          // Accumulate the width of this character based on the exactitude of the desired
          // answer.
          accumulatedW += (exact ? m.maxX - m.minX : std::max(m.maxX, m.advance));
        }

        // Return the dimensions of this text.
        return utils::Sizef(1.0f * accumulatedW, 1.0f * (maxAscent - minAscent));
      }

      FontCache::GlyphPtr
      FontCache::renderGlyph(char c,
                             const Color& color)
      {
        std::string key = makeKey(c, color);

        // Check whether the input character has already been loaded in the cache.
        Glyphs::const_iterator it = m_glyphs.find(key);

        if (it != m_glyphs.cend()) {
          if (color != it->second.c) {
            warn("Using glyph with color " + color.toString() + " while cached glyph has color " + it->second.c.toString());
          }
          // Return the cached version of the glyph.
          return it->second.tex;
        }

        // The glyph does not exist yet, create it and register it to the cache.
        SDL_Surface* glyph = TTF_RenderGlyph_Blended(m_font, c, color.toSDLColor());
        if (glyph == nullptr) {
          error(
            std::string("Could not render glyph \"") + std::to_string(static_cast<int>(c)) + "\"",
            TTF_GetError()
          );
        }

        m_glyphs[key] = GlyphData{glyph, color};

        return glyph;
      }

    }
  }
}
