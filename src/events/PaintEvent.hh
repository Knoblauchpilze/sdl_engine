#ifndef    PAINT_EVENT_HH
# define   PAINT_EVENT_HH

# include <memory>
# include <vector>
# include <maths_utils/Box.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      namespace update {

        /**
         * @brief - Describes a coordinate frame for an update region.
         */
        enum class Frame {
          Local, //<! - This value indicates that the area associated to the update
                 //<!   region is expressed in local coordinate frame.
          Global //<! - This value indicates that the area associated to the update
                 //<!   region is expressed in global coordinate frame.
        };

        /**
         * @brief - Used to describe an update region associated to a paint event. The typical
         *          update region is composed of a area representing the actual extent of the
         *          region to update, and also a value indicating the coordinate frame that it
         *          is expressed into so that the user knows how to interpret it.
         */
        struct Region {
          utils::Boxf area;
          Frame frame;

          /**
           * @brief - Reuses the namespace method to print this region to a string.
           * @return - a string representing this region as a human-readable data.
           */
          std::string
          toString() const noexcept;

          /**
           * @brief - Determines whether `this` and `rhs` are equals. In order for
           *          two regions to be equal they should have the same coordinate
           *          frame and the same extent.
           * @param rhs - the element to compare with `this`.
           * @return - `true` if `rhs` is equal to `this` and `false` otherwise.
           */
          bool
          operator==(const Region& rhs) const noexcept;

          /**
           * @brief - Determines whether `this` and `rhs` are different. In order for
           *          two regions to be different they should either have a different
           *          coordinate frame or a different extent.
           * @param rhs - the element to compare with `this`.
           * @return - `true` if `rhs` is different from `this` and `false` otherwise.
           */
          bool
          operator!=(const Region& rhs) const noexcept;
        };

        /**
         * @brief - Retrieves a human-readable string for the input frame.
         * @param frame - the coordinate frame to convert to a string.
         * @return - a string representing a name for the input coordinate frame or "unknown"
         *           if the coordinate frame is unknown.
         */
        std::string
        getNameFromFrame(const Frame& frame) noexcept;

      }

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
           *          The user should specify the coordinate frame into which the area
           *          is expressed.
           * @param updateRegion - the region to update for the component.
           * @param frame - the coordinate frame into which the `updateRegion` exists.
           * @param receiver - the object which will receive this paint event. If left
           *                   empty all registered elements will receive it.
           */
          PaintEvent(const utils::Boxf& updateRegion,
                     const update::Frame& frame = update::Frame::Global,
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
          const std::vector<update::Region>&
          getUpdateRegions() const noexcept;

          /**
           * @brief - Add the input region as a region to update for this event. Note that
           *          the standard process is used to clean duplicated region and to merge
           *          potentially overlapping regions.
           *          Also the user should specify whether the input area is expressed in
           *          local or global coordinate frame.
           * @param area - the region to add as a region to update for this event.
           * @param frame - the coordinate frame to use to interpret the region.
           * @return - `true` if the region was added, `false` otherwise.
           */
          bool
          addUpdateRegion(const utils::Boxf& area,
                          const update::Frame& frame = update::Frame::Global) noexcept;

          /**
           * @brief - Similar method to the `addUpdateRegion` with an area and a frame. This
           *          method is actually used by the above one.
           *          Note that a sanitization is performed in order to keep a consistent
           *          paint event.
           * @param region - the update region to add to this event.
           * @return - `true` if the region was added, `false` otherwise.
           */
          bool
          addUpdateRegion(const update::Region& region) noexcept;

          /**
           * @brief - Used to copy the update regions of the input paint event `e` into the
           *          internal list of regions. A sanitize operation is called at the end of
           *          the function so that we keep only relevant areas.
           *          Note that none of the other parameters of the input paint event `e`
           *          are copied.
           * @param e - the event from which update regions should be copied.
           */
          void
          copyUpdateRegions(const PaintEvent& e) noexcept;

          /**
           * @brief - Used to determine whether all the areas associated to this paint event
           *          can be contained in the input area. This can be used to determine for
           *          example if the area of a widget encompasses all the modifications brought
           *          by the paint event or to replace several areas with a single larger one.
           *          Note that the user should specify how to interpret the input area, either
           *          considering it is expressed in local or global frame.
           * @param area - the area which should be checked to determine whether it contains
           *               all the areas associated to this event.
           * @param frame - the coordinate frame associated to the input `area`.
           * @return - `true` if the input `area` contains all the area associated to this paint
           *           event and `false` otherwise.
           */
          bool
          isContained(const utils::Boxf& area,
                      const update::Frame& frame = update::Frame::Global) const noexcept;

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
           *          Note that the return value of the base class will indicate whether
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
           * @param region - the area which should be checked for uniqueness.
           * @return - true if the `area` is not already part of the internal areas,
           *           false ig this ara either exists or is covered by another one.
           */
          bool
          isUnique(const update::Region& region,
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
           *          Note that the region are expressed through both their extent
           *          but also the coordinate frame into which the area is expressed.
           */
          std::vector<update::Region> m_updateRegions;

      };

      using PaintEventShPtr = std::shared_ptr<PaintEvent>;
    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HH */
