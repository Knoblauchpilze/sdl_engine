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
           * @param name - the name of the font pointer associated to this cache.
           * @param font - the font associated to this cache.
           */
          explicit
          FontCache(const std::string& name,
                    TTF_Font* font);

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
           *          The user can specify whether the rendering of the texts should be done by
           *          concatenating exactly the characters or if some sort of spacing should be
           *          applied to the characters.
           * @param text - the text to render.
           * @param color - the color to use to render the text.
           * @param exact - `true` if the characters should be renderer without spacing, `false`
           *                if some spacing should be applied.
           * @return - the surface representing the input text.
           */
          SDL_Surface*
          render(const std::string& text,
                 const Color& color = Color::NamedColor::Black,
                 bool exact = false);

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
           * @brief - Describes the data associated with a cached glyph. Contains the texture
           *          representing the glyph and its color.
           */
          struct GlyphData {
            GlyphPtr tex;
            Color c;
          };

          /**
           * @brief - Internal struct describing the metrics associated to a font. Most of
           *          the metrics are just aggregated information from individual glyphs:
           *          such as the font's ascent and descent (i.e. how far from the baseline
           *          any glyph can get) etc.
           */
          struct FontMetrics {
            int ascent;
            int descent;

            int height;
          };

          /**
           * @brief - Internal struct describing the metrics which can be retrieve for an
           *          individual glyph. Extent in both axis is provided.
           */
          struct GlyphMetrics {
            int minX;
            int maxX;

            int minY;
            int maxY;

            int advance;
          };

          /**
           * @brief - Used to perform the rendering of the input glyph as a valid area to be
           *          displayed. Uses the cache if the glyph as already been rendered and add
           *          it to the cache if this is not the case.
           *          Note that the glyph is rendered using the provided color. Also note that
           *          the produced glyph is just large enough to contain the character.
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

          /**
           * @brief - Checks whether the input character is provided in the font associated to
           *          this cache. We assume that the font is valid..
           * @param c - the character to be checked.
           * @return - `true` if the character exists in the font and `false` otherwise.
           */
          bool
          exists(char c) const noexcept;

          /**
           * @brief - Retrieves the metrics associated to the internal font. The metrics contain
           *          information about the maximum ascent and descent, and generally aggregated
           *          data on all individual glyphs.
           *          Note that the font is assumed to be valid.
           * @return - an object representing the metrics of the font.
           */
          FontMetrics
          getMetrics() const noexcept;

          /**
           * @brief - Retrieves the metrics associated to the input character based on the data
           *          of the font. Note that the font is assumed to be valid so no checks are
           *          performed in this method.
           *          The metrics are returned using the dedicated struct with all values set to
           *          `0` if the character is not provided by the font.
           * @param c - the character which metrics should be provided.
           * @return - the metrics associated to the input character.
           */
          GlyphMetrics
          getMetrics(char c) const noexcept;

          /**
           * @brief - Used to perform the creation of a valid key from an input character and
           *          a color. This key can be used to insert elements in the internal `m_glyphs`
           *          array.
           * @param c - the character to use to create the key.
           * @param color - the color to use to create the key.
           * @return - a string representing the key built from the character and color.
           */
          static
          std::string
          makeKey(char c,
                  const Color& color) noexcept;

        private:

          /**
           * @brief - Describes a glyph tables used to register all the glyphs loaded so far
           *          for a font.
           */
          using Glyphs = std::unordered_map<std::string, GlyphData>;

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
