
# include "PaintEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      utils::Boxf
      PaintEvent::convertToLocal(const utils::Boxf& area,
                                 const utils::Boxf& reference) const noexcept
      {
        // The position of the `reference` is used to convert the position of the
        // input `area`. To do so we compute the relative offset between both areas.
        // The dimensions are kept unchanged as there is no scaling.
        return utils::Boxf(
          area.x() - reference.x(),
          area.y() - reference.y(),
          area.w(),
          area.h()
        );
      }

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

        // Equalize internal fields.
        m_updateRegions.insert(
          m_updateRegions.end(),
          usable.m_updateRegions.begin(),
          usable.m_updateRegions.end()
        );

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
