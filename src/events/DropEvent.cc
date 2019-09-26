
# include "DropEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      DropEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      DropEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const DropEvent& usable = dynamic_cast<const DropEvent&>(other);

        // Equalize internal fields.
        m_startPosition = usable.m_startPosition;
        m_endPosition = usable.m_endPosition;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
