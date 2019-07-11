
# include "PaintEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      void
      PaintEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      PaintEvent::equal(const Event& other) const noexcept {
        // First handle the base equality checks.
        if (!Event::equal(other)) {
          return false;
        }

        // Compare each update regions and check if one is different. We
        // can rely on the comparison of vectors as it will perform the
        // comparison of each individual element.
        // Note that we're not robust to same areas in different order
        // but we do not want to handle this for now.
        const PaintEvent& e = dynamic_cast<const PaintEvent&>(other);

        return m_updateRegions != e.m_updateRegions;
      }

      bool
      PaintEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can be merged with
        // this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const PaintEvent& usable = dynamic_cast<const PaintEvent&>(other);

        // We need to merge both internal arrays to keep only relevant
        // areas. Instead of adding all the areas from the `other` to
        // `this` event we select only the ones which do not already
        // exist in `this` event.
        // We keep extra care to only proces needed areas: we consider
        // the the `other` event is valid and only contains unique areas
        // so we can check them against the initial areas of this event.

        const int max = static_cast<int>(m_updateRegions.size());

        // Traverse the list of regions defined for `other`.
        for (int id = 0 ; id < static_cast<int>(usable.m_updateRegions.size()) ; ++id) {
          // Check whether this area can be added to `this` event.
          bool found = 0;
          int elem = 0;
          while (!found && elem < max) {
            found = usable.m_updateRegions[id] == m_updateRegions[elem];
            ++elem;
          }

          // If this update region already exists, do not add it. And
          // conversely if it does not exist yet, add it as part of
          // `this` event.
          if (!found) {
            m_updateRegions.push_back(usable.m_updateRegions[id]);
          }
        }

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
