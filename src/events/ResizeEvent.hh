#ifndef    RESIZE_EVENT_HH
# define   RESIZE_EVENT_HH

# include <memory>
# include "Event.hh"
# include <core_utils/Uuid.hh>
# include <maths_utils/Box.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class ResizeEvent: public Event {
        public:

          ResizeEvent(const utils::Boxf& newSize,
                      const utils::Boxf& oldSize,
                      EngineObject* receiver = nullptr);

          ~ResizeEvent();

          void
          populateFromEngineData(Engine& engine) override;

          const utils::Boxf&
          getNewSize() const noexcept;

          const utils::Boxf&
          getOldSize() const noexcept;

          void
          setNewSize(const utils::Boxf& newSize) noexcept;

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

          utils::Boxf m_new;
          utils::Boxf m_old;

      };

      using ResizeEventShPtr = std::shared_ptr<ResizeEvent>;
    }
  }
}

# include "ResizeEvent.hxx"

#endif    /* RESIZE_EVENT_HH */
