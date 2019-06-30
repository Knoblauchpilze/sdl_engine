
# include "ResizeEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      ResizeEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      ResizeEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const ResizeEvent& usable = dynamic_cast<const ResizeEvent&>(other);

        // Equalize internal fields: we only want to equalize the new size and
        // not the old size. Indeed when we want to merge two resize event and
        // this operation is permitted by the base `Event` class, it means that
        // the `other` event is more recent than this one. Normally this should
        // mean that the `old size` of the `other` event corresponds to the `new
        // size` of `this` event. If this is not the case this is a problem.
        if (m_new != usable.m_old) {
          log(
            std::string("Merging resize event but sizes don't match (expected ") + m_new.toString() + " got " + usable.m_old.toString(),
            utils::Level::Warning
          );
        }

        m_new = usable.m_new;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
