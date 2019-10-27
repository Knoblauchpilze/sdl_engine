
# include "HideEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      HideEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      HideEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const HideEvent& usable = dynamic_cast<const HideEvent&>(other);

        // Equalize internal fields.
        m_region = usable.m_region;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
