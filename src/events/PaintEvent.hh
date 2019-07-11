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
           * @brief - Retrieves the regions to update as provided during the construction
           *          of the object.
           * @return - the update regions associated to this paint event.
           */
          const std::vector<utils::Boxf>&
          getUpdateRegions() const noexcept;

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
