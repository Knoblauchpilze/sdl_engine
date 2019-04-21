#ifndef    TEXTURE_HXX
# define   TEXTURE_HXX

# include "Texture.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Texture::Texture(SDL_Renderer* renderer,
                       const Palette::ColorRole& role,
                       const Type& type):
        utils::CoreObject(std::string("texture")),
        m_renderer(renderer),
        m_role(role),
        m_type(type),
        m_texture(nullptr)
      {
        setService(std::string("texture"));
      }

      inline
      Texture::~Texture() {
        clean();
      }

      inline
      SDL_Texture*
      Texture::operator()() {
        // Ensure we return a valid texture by creating it.
        createOnce();

        // Return the valid texture.
        return m_texture;
      }

      inline
      const Palette::ColorRole&
      Texture::getRole() const noexcept {
        return m_role;
      }

      inline
      SDL_Renderer*
      Texture::getRenderer() const noexcept {
        return m_renderer;
      }

      inline
      bool
      Texture::valid() const noexcept {
        return m_texture != nullptr;
      }

      inline
      void
      Texture::setRole(const Palette::ColorRole& role) {
        m_role = role;
      }

      inline
      void
      Texture::clean() {
        if (m_texture != nullptr) {
          SDL_DestroyTexture(m_texture);
        }
      }

      inline
      void
      Texture::createOnce() {
        // Create the texture if needed.
        if (!valid()) {
          m_texture = create();

          if (!valid()) {
            error(std::string("Could not create texture with type ") + std::to_string(static_cast<int>(m_type)));
          }
        }
      }

    }
  }
}

#endif    /* TEXTURE_HXX */
