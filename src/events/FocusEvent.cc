
# include "FocusEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      FocusEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      FocusEvent::equal(const Event& other) const noexcept {
        const FocusEvent& e = dynamic_cast<const FocusEvent&>(other);
        return Event::equal(other) && getReason() == e.getReason();
      }

      bool
      FocusEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can
        // be merged with this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const FocusEvent& usable = dynamic_cast<const FocusEvent&>(other);

        // Equalize internal fields.
        m_reason = usable.m_reason;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
