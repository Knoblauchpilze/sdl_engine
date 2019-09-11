
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

        Event::Type type = Event::Type::KeyPress;
        if (m_key.type == SDL_KEYUP) {
          type = Event::Type::KeyRelease;
        }

        m_converted = fromSDLKey(m_key.keysym.sym);
        m_mod = fromSDLMod(m_key.keysym.mod);

        setType(type);

        setSDLWinID(m_key.windowID);
      }

    }
  }
}
