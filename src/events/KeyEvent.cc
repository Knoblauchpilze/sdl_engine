
# include "KeyEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      KeyEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      KeyEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const KeyEvent& usable = dynamic_cast<const KeyEvent&>(other);

        // Equalize internal fields.
        m_key = usable.m_key;

        // Return the base handler's prescriptions.
        return canMerge;
      }

      void
      KeyEvent::init() {
        // Check whether the event has a right type.
        if (m_key.type != SDL_KEYDOWN && m_key.type != SDL_KEYUP) {
          error(
            std::string("Cannot create key event"),
            std::string("Key event has invalid type ") + std::to_string(static_cast<int>(m_key.type))
          );
        }

        // The type of the event is determined from the undelrying `API` event.
        Event::Type type = Event::Type::KeyPress;
        if (m_key.type == SDL_KEYUP) {
          type = Event::Type::KeyRelease;
        }

        // Build both the raw and converted key values.
        m_raw = fromSDLScancode(m_key.keysym.scancode);
        // TODO: We should retrieve this somehow.
        m_interpreted = fromRawKey(m_raw, keyboard::Mode::Azerty);

        // Retrieve the key modifiers.
        m_mods = fromSDLMod(m_key.keysym.mod);

        log(
          std::string("Pressed ") +
          "key " + std::to_string(m_key.keysym.sym) + " " +
          "(scan: " + std::to_string(m_key.keysym.scancode) + ", name: \"" + SDL_GetKeyName(m_key.keysym.sym) + "\") " +
          "converted to " + std::to_string(static_cast<int>(m_raw)) + " "
          "interpreted in " + std::to_string(static_cast<int>(m_interpreted))
        );

        setType(type);

        setSDLWinID(m_key.windowID);
      }

      Key
      KeyEvent::fromRawKey(const RawKey& key,
                           const keyboard::Mode& mode) noexcept
      {
        error(
          std::string("Cannot convert from raw key"),
          std::string("Not implemented")
        );

        return Key::None;
      }

    }
  }
}
