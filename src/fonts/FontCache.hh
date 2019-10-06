#ifndef    FONT_CACHE_HH
# define   FONT_CACHE_HH

# include <memory>
# include <unordered_map>
# include <SDL2/SDL_ttf.h>
# include <core_utils/CoreObject.hh>
# include <maths_utils/Size.hh>
# include "Color.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FontCache: public utils::CoreObject {
        public:

          /**
           * @brief - Creates a font cache for the specified font. Can be used to render
           *          some glyphs and cache their corresponding surface in order to get
           *          faster rendering time and consistent spacing.
           * @param font - the font associated to this cache.
           */
          explicit
          FontCache(TTF_Font* font);

          /**
           * @brief - Destruction of the font cache and all the associated saved glyphs.
           *          Internally calls the `clear` method.
           */
          virtual ~FontCache();

          /**
           * @brief - Performs a clear of all the glyphs saved in this cache. Most of the
           *          time this method should not be called as the cache already manages
           *          its content in an optimal way.
           */
          void
          clear();

          /**
           * @brief - Used to perform the rendering of the input text with the specified color.
           *          All glyphs composing the text will either be retrieved from the cache or
           *          loaded if necessary.
           * @param text - the text to render.
           * @param color - the color to use to render the text.
           * @return - the surface representing the input text.
           */
          SDL_Surface*
          render(const std::string& text,
                 const Color& color = Color::NamedColor::Black);

          /**
           * @brief - Used to query the size of the input text given the glyphs associated to this
           *          font. 
           * @param text - the text zhich size should be retrieved.
           * @param exact - `true` if the exact size of the text should be retrieved (i.e. pixel
           *                perfect size) and `false` otherwise.
           * @return - the size of the input text.
           */
          utils::Sizef
          querySize(const std::string& text,
                    bool exact);

        private:

          /**
           * @brief - Describes what a glyph is (i.e. a visual representation of a character).
           */
          using Glyph = SDL_Surface;
          using GlyphPtr = Glyph*;

          /**
           * @brief - Used to perform the rendering of the input glyph as a valid area to be
           *          displayed. Uses the cache if the glyph as already been rendered and add
           *          it to the cache if this is not the case.
           *          Note that the glyph is rendered using the provided color.
           * @param c - the character to render.
           * @param color - the color to use to render the glyph.
           * @return - the visual representation of the input glyph.
           */
          GlyphPtr
          renderGlyph(char c,
                      const Color& color);

          /**
           * @brief - Used to clear the memory used by the input glyph.
           */
          void
          clearGlyph(GlyphPtr glyph) const;

        private:

          /**
           * @brief - Describes a glyph tables used to register all the glyphs loaded so far
           *          for a font.
           */
          using Glyphs = std::unordered_map<char, GlyphPtr>;

          /**
           * @brief - The font associated to this cache. Represents the underlying `API`
           *          object allowing to render some texts.
           */
          TTF_Font* m_font;

          /**
           * @brief - A table containing all the glyphs rendered so far and still stored
           *          in the cache. This table aggregates the glyphs with keys defining
           *          the characters and the corresponding values as surfaces representing
           *          the visual data associated to the glyph.
           */
          Glyphs m_glyphs;
      };

      using FontCacheShPtr = std::shared_ptr<FontCache>;
    }
  }
}

# include "FontCache.hxx"

#endif    /* FONT_CACHE_HH */
