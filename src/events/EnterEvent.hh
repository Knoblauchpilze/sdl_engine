#ifndef    ENTER_EVENT_HH
# define   ENTER_EVENT_HH

# include "Event.hh"
# include <memory>
# include <maths_utils/Vector2.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EnterEvent: public Event {
        public:

          EnterEvent(const utils::Vector2f& coordinates,
                     EngineObject* receiver = nullptr);

          ~EnterEvent();

          void
          populateFromEngineData(Engine& engine) override;

          const utils::Vector2f&
          getMousePosition() const noexcept;

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

          utils::Vector2f m_coordinates;

      };

    }
  }
}

# include "EnterEvent.hxx"

#endif    /* ENTER_EVENT_HH */
