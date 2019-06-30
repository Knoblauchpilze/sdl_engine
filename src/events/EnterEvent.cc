
# include "EnterEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      EnterEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      EnterEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const EnterEvent& usable = dynamic_cast<const EnterEvent&>(other);

        // Equalize internal fields.
        m_coordinates = usable.m_coordinates;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
