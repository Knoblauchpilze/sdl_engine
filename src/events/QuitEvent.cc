
# include "QuitEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      QuitEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      QuitEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const QuitEvent& usable = dynamic_cast<const QuitEvent&>(other);

        // Equalize internal fields.
        m_quit = usable.m_quit;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
