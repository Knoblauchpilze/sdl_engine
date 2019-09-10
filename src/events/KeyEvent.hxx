#ifndef    KEY_EVENT_HXX
# define   KEY_EVENT_HXX

# include "KeyEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      KeyEvent::KeyEvent(const SDL_KeyboardEvent& event):
        Event(Event::Type::None, nullptr, std::string("key_event_") + std::to_string(event.keysym.sym)),
        m_key(event)
      {
        init();
      }

      inline
      KeyEvent::~KeyEvent() {}

      inline
      int
      KeyEvent::getKey() const noexcept {
        return m_key.keysym.sym;
      }

      inline
      bool
      KeyEvent::isPress() const noexcept {
        return getType() == Event::Type::KeyPress;
      }

      inline
      bool
      KeyEvent::isRelease() const noexcept {
        return getType() == Event::Type::KeyRelease;
      }

      inline
      bool
      KeyEvent::isEscape() const noexcept {
        return getKey() == SDLK_ESCAPE;
      }

      inline
      bool
      KeyEvent::isAlphaNumeric() const noexcept {
        return
          getKey() == SDLK_a ||
          getKey() == SDLK_b ||
          getKey() == SDLK_c ||
          getKey() == SDLK_d ||
          getKey() == SDLK_e ||
          getKey() == SDLK_f ||
          getKey() == SDLK_g ||
          getKey() == SDLK_h ||
          getKey() == SDLK_i ||
          getKey() == SDLK_j ||
          getKey() == SDLK_k ||
          getKey() == SDLK_l ||
          getKey() == SDLK_m ||
          getKey() == SDLK_n ||
          getKey() == SDLK_o ||
          getKey() == SDLK_p ||
          getKey() == SDLK_q ||
          getKey() == SDLK_r ||
          getKey() == SDLK_s ||
          getKey() == SDLK_t ||
          getKey() == SDLK_u ||
          getKey() == SDLK_v ||
          getKey() == SDLK_w ||
          getKey() == SDLK_x ||
          getKey() == SDLK_y ||
          getKey() == SDLK_z ||
          getKey() == SDLK_0 ||
          getKey() == SDLK_1 ||
          getKey() == SDLK_2 ||
          getKey() == SDLK_3 ||
          getKey() == SDLK_4 ||
          getKey() == SDLK_5 ||
          getKey() == SDLK_6 ||
          getKey() == SDLK_7 ||
          getKey() == SDLK_8 ||
          getKey() == SDLK_9
        ;
      }

      inline
      char
      KeyEvent::getChar() const {
        // Check whether the key is alpha numeric: if this is not the case we can't really
        // provide an equivalent char.
        if (!isAlphaNumeric()) {
          error(
            std::string("Cannot return equivalent char to key"),
            std::string("Key is not alphanumeric")
          );
        }

        // The SDL values already correspond to the ASCII codes so we're safe on this side.
        return static_cast<char>(getKey());
      }

      inline
      bool
      KeyEvent::equal(const Event& other) const noexcept {
        const KeyEvent& e = dynamic_cast<const KeyEvent&>(other);
        return Event::equal(other) && getKey() == e.getKey();
      }

    }
  }
}

#endif    /* KEY_EVENT_HH */
