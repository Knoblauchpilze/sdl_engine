#ifndef    HIDE_EVENT_HH
# define   HIDE_EVENT_HH

# include "Event.hh"
# include <memory>
# include <maths_utils/Box.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class HideEvent: public Event {
        public:

          /**
           * @brief - Creates a new hide event with the specified update region. The region
           *          corresponds to the area which is impacted by the hide event.
           *          The user can specify the receiver object of this event.
           * @param region - the region where something was hidden.
           * @param receiver - the receiver of this object and `null` if no particular object
           *                   should receive it.
           */
          HideEvent(const utils::Boxf& region,
                    EngineObject* receiver = nullptr);

          /**
           * @brief - Destruction of the object.
           */
          ~HideEvent();

          void
          populateFromEngineData(Engine& engine) override;

          /**
           * @brief - Retrieves the hidden area as a box. This area is expressed in the coordinate
           *          frame of the object which emitted the event.
           * @return - a box representig the area impacted by the hide event.
           */
          const utils::Boxf&
          getHiddenRegion() const noexcept;

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

          utils::Boxf m_region;
      };

      using HideEventShPtr = std::shared_ptr<HideEvent>;
    }
  }
}

# include "HideEvent.hxx"

#endif    /* HIDE_EVENT_HH */
