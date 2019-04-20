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
        m_texture(nullptr),
        m_renderer(renderer),
        
        m_type(Type::Basic),
        m_size(size),
        m_file(),
        m_surface(nullptr)
      {
        setService(std::string("texture"));
      }

      inline
      Texture::Texture(const std::string& file,
                       const Palette::ColorRole& role,
                       SDL_Renderer* renderer):
        utils::CoreObject(std::string("texture")),
        m_role(role),
        m_texture(nullptr),
        m_renderer(renderer),

        m_type(Type::Image),
        m_size(),
        m_file(file),
        m_surface(nullptr)
      {
        setService(std::string("texture"));
      }

      inline
      Texture::Texture(SDL_Surface* surface,
                       SDL_Renderer* renderer,
                       const Palette::ColorRole& role):
        utils::CoreObject(std::string("texture")),
        m_role(role),
        m_texture(nullptr),
        m_renderer(renderer),

        m_type(Type::Surface),
        m_size(),
        m_file(),
        m_surface(surface)
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
      void
      Texture::setRole(const Palette::ColorRole& role) {
        m_role = role;
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
      Texture::create() {
        switch (m_type) {
          case Type::Basic:
            create(m_size, m_renderer);
            break;
          case Type::Image:
            create(m_file, m_renderer);
            break;
          case Type::Surface:
            create(m_renderer);
            break;
          default:
            error(std::string("Cannot create texture with unknown type ") + std::to_string(static_cast<int>(m_type)));
            break;
        }
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
