#ifndef    PAINT_EVENT_HH
# define   PAINT_EVENT_HH

# include <memory>
# include <vector>
# include <maths_utils/Box.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class PaintEvent: public Event {
        public:

          /**
           * @brief - Creates an event with no associated update region and the specified
           *          receiver. The default `null` value of the receiver makes it not
           *          directed towards any specific object.
           *          User are encouraged to add update regions with the `addUpdateRegion`
           *          method otherwise the paint event will do nothing.
           * @param receiver - the object which will receive this paint event. If left
           *                   empty all registered elements will receive it.
           */
          PaintEvent(EngineObject* receiver = nullptr);

          /**
           * @brief - Creates an event which is used to repaint the area defined by the
           *          `updateRegion` of the object described by the `receiver` or to be
           *          transmitted to all registered elements if it is left empty.
           * @param updateRegion - the region to update for the component.
           * @param receiver - the object which will receive this paint event. If left
           *                   empty all registered elements will receive it.
           */
          PaintEvent(const utils::Boxf& updateRegion,
                     EngineObject* receiver = nullptr);

          ~PaintEvent();

          /**
           * @brief - Returns true if this paint event has at least an update region associated
           *          to it and false otherwise.
           * @return - true if at least one update regions is associated to this event, false
           *           otherwise.
           */
          bool
          hasUpdateRegions() const noexcept;

          /**
           * @brief - Retrieves the regions to update as provided during the construction
           *          of the object.
           * @return - the update regions associated to this paint event.
           */
          const std::vector<utils::Boxf>&
          getUpdateRegions() const noexcept;

          /**
           * @brief - Add the input region as a region to update for this event. Note that
           *          the standard process is used to clean duplicated region and to merge
           *          potentially overlapping regions.
           * @param region - the region to add as a region to update for this event.
           */
          void
          addUpdateRegion(const utils::Boxf& region) noexcept;

          void
          populateFromEngineData(Engine& engine) override;

        protected:

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific behavior to compare both the common attribute (using the
           *          base handler) and the properties defined by this type of event.
           * @param other - the `other` event to check for equality with `this`.
           * @return - true if both `other` and `this` are equal, false otherwise.
           */
          bool
          equal(const Event& other) const noexcept override;

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific merge strategy for this type of event. We will use the
           *          base handler internally to merge common attributes of the event,
           *          and then downcast the input `other` event to `this` dynamic type
           *          to perform custom merging.
           *          Note that the returnvalue of the base class will indicate whether
           *          we should perform the custom merge strategy.
           *          The return value of this method is indistinguishable from the
           *          return value of the base `Event` method.
           * @param other - the `other` event to merge with `this`.
           * @return - true if the `other` event was merged with `this`, false otherwise.
           */
          bool
          mergePrivate(const Event& other) noexcept override;

        private:

          /**
           * @brief - Used to determine whether the input `area` already exists in the
           *          internal `m_updateRegions` array. The term `exists` covers both
           *          the fact that an exactly equal region might be present in the
           *          internal array but also the case where a region containing the
           *          input `area` exists in the array.
           *          If none of this scenarii occurs, the method returns true.
           *          The internal array is searched up until the `max` index is reached
           *          or up until the end if `max` is negative.
           *          This allows to dynamically insert elements in the `m_updateRegions`
           *          without researching the already inserted elements (for example in
           *          the `meregPrivate` method).
           * @param area - the area which should be checked for uniqueness.
           * @return - true if the `area` is not already part of the internal areas,
           *           false ig this ara either exists or is covered by another one.
           */
          bool
          isUnique(const utils::Boxf& area,
                   int max = -1) const noexcept;

          /**
           * @brief - Should be used after any insertion operation of an element inside
           *          the internal `m_updateRegions` array.
           *          This method will check that no area is contained in another one
           *          so that we keep only the minimum amount of elements in the update
           *          regions.
           */
          void
          sanitize();

        private:

          /**
           * @brief - Contains all the regions to update when processing this event.
           */
          std::vector<utils::Boxf> m_updateRegions;

      };

      using PaintEventShPtr = std::shared_ptr<PaintEvent>;
    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HH */
