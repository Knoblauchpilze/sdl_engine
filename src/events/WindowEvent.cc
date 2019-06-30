
# include "WindowEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      WindowEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      WindowEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const WindowEvent& usable = dynamic_cast<const WindowEvent&>(other);

        // Equalize internal fields.
        m_window = usable.m_window;
        m_size = usable.m_size;

        // Return the base handler's prescriptions.
        return canMerge;
      }

      void
      WindowEvent::init() {
        // Check whether the event has a right type.
        if (m_window.type != SDL_WINDOWEVENT) {
          error(std::string("Cannot create window event from invalid type ") + std::to_string(static_cast<int>(m_window.type)));
        }

        Event::Type type = Event::Type::None;
        switch (m_window.event) {
          case SDL_WINDOWEVENT_LEAVE:
            type = Event::Type::WindowLeave;
            break;
          case SDL_WINDOWEVENT_ENTER:
            type = Event::Type::WindowEnter;
            break;
          case SDL_WINDOWEVENT_RESIZED:
            type = Event::Type::WindowResize;
            break;
          case SDL_WINDOWEVENT_MAXIMIZED:
            type = Event::Type::WindowResize;
            break;
          default:
            // Not handled event for now.
            break;
        }

        // Assign the size from the input event if any.
        if (type == Event::Type::WindowResize) {
          m_size = utils::Sizef(
            m_window.data1,
            m_window.data2
          );
        }

        setType(type);

        setSDLWinID(m_window.windowID);
      }

    }
  }
}
