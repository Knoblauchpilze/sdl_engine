
# include "PaintEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      bool
      PaintEvent::addUpdateRegion(const update::Region& region) noexcept {

        // Add the region to the internal areas if it does not already exist.
        if (isUnique(region)) {
          m_updateRegions.push_back(region);

          // Sanitize in case the new region encompasses some old areas.
          sanitize();

          return true;
        }

        // The region was not added.
        return false;
      }

      void
      PaintEvent::copyUpdateRegions(const PaintEvent& e) noexcept {
        // We need to merge both internal arrays to keep only relevant
        // areas. Instead of adding all the areas from the `other` to
        // `this` event we select only the ones which do not already
        // exist in `this` event.
        // We keep extra care to only proces needed areas: we consider
        // the `other` event is valid and only contains unique areas so
        // we can check them against the initial areas of this event.
        const int max = static_cast<int>(m_updateRegions.size());

        // Traverse the list of regions defined for `other`.
        for (int id = 0 ; id < static_cast<int>(e.m_updateRegions.size()) ; ++id) {
          // Check whether this area can be added to `this` event (i.e.
          // check its uniqueness).
          if (!isUnique(e.m_updateRegions[id], max)) {
            // Continue the process.
            continue;
          }

          // Safely add the input area to the internal array.
          m_updateRegions.push_back(e.m_updateRegions[id]);
        }

        // Last step: sanitize the update regions. Indeed as we only
        // checked whether some internal areas contained the one from
        // the `other` event we have neglected the case where some
        // new areas encompassed existing ones. We need to take care
        // of this.
        sanitize();
      }

      bool
      PaintEvent::isContained(const utils::Boxf& area,
                              const update::Frame& frame) const noexcept
      {
        // We need to traverse all the update regions and check whether the input
        // area contains each one.
        int id = 0;
        int max = static_cast<int>(m_updateRegions.size());
        bool contained = true;

        while (id < max && contained) {
          contained = m_updateRegions[id].frame == frame && area.contains(m_updateRegions[id].area);
          ++id;
        }

        // Return the contained boolean which describes the required status.
        return contained;
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

        // Use the dedicated handler to merge the update regions.
        copyUpdateRegions(usable);

        // Return the base handler's prescriptions.
        return canMerge;
      }

      bool
      PaintEvent::isUnique(const update::Region& region,
                           int max) const noexcept
      {
        // Determine the maximum: i.e. update it if it is negative.
        if (max < 0) {
          max = static_cast<int>(m_updateRegions.size());
        }

        // Traverse the internal list of regions to update until we
        // find either this `region` exactly or an area which spans
        // the input one.
        int id = 0;
        bool found = false;

        while (!found && id < max) {
          // The logic to determine if the area is contained inside the
          // other one already accounts for equality: we consider to
          // equal areas to be contained into each other.
          found = m_updateRegions[id].frame == region.frame && m_updateRegions[id].area.contains(region.area);
          ++id;
        }

        // Return the status for this `area`.
        return !found;
      }

      void
      PaintEvent::sanitize() {
        // What we want to do here is make sure that all the areas in the
        // internal `m_updateRegions` are unique. To do so, we will proceed
        // sequentially and keep only the areas which are not contained in
        // any other.

        // First, copy the internal array into a temporary one.
        std::vector<update::Region> working;
        working.swap(m_updateRegions);

        // Traverse the working vector and populate the `m_updateRegions`
        // with areas which are not contained in any other.
        for (int id = 0 ; id < static_cast<int>(working.size()) ; ++id) {

          int check = 0;
          bool contained = false;
          while (!contained && check < static_cast<int>(working.size())) {
            // Do not check an area against itself, as it is obviously contained
            // in it.
            if (check == id) {
              ++check;
              continue;
            }

            contained = (working[check].frame == working[id].frame) && working[check].area.contains(working[id].area);

            if (!contained) {
              ++check;
            }
          }

          // Insert this area if it was not contained in any other area.
          if (contained) {
            continue;
          }

          m_updateRegions.push_back(working[id]);
        }
      }

    }
  }
}
