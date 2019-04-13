#ifndef    TEXTURE_HXX
# define   TEXTURE_HXX

# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Texture::Texture(const utils::Sizei& size,
                       const Palette::ColorRole& role,
                       SDL_Renderer* renderer):
        utils::CoreObject(std::string("texture")),
        m_role(role),
        m_texture(nullptr)
      {
        setService(std::string("texture"));

        create(size, renderer);
      }

      inline
      Texture::Texture(const std::string& file,
                       const Palette::ColorRole& role,
                       SDL_Renderer* renderer):
        utils::CoreObject(std::string("texture")),
        m_role(role),
        m_texture(nullptr)
      {
        setService(std::string("texture"));

        create(file, renderer);
      }

      inline
      Texture::Texture(SDL_Texture* tex):
        utils::CoreObject(std::string("texture")),
        m_texture(tex)
      {
        setService(std::string("texture"));
      }

      inline
      Texture::~Texture() {
        clean();
      }

      inline
      SDL_Texture*
      Texture::operator()() const noexcept {
        return m_texture;
      }

      inline
      void
      Texture::setAlpha(const Color& color) {
        SDL_SetTextureAlphaMod(m_texture, color.toSDLColor().a);
      }

      inline
      utils::Sizei
      Texture::query() {
        // Query the texture.
        int w, h;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

        return utils::Sizei(w, h);
      }

      inline
      void
      Texture::clean() {
        if (m_texture != nullptr) {
          SDL_DestroyTexture(m_texture);
        }
      }

    }
  }
}

#endif    /* TEXTURE_HXX */
