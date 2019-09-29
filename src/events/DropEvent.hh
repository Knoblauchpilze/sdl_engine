#ifndef    DROP_EVENT_HH
# define   DROP_EVENT_HH

# include <memory>
# include "Event.hh"
# include <maths_utils/Vector2.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class DropEvent: public Event {
        public:

          /**
           * @brief - Create a new drop event with the provided starting position and
           *          end position. Both position describe the position of the cursor
           *          when the drag and drop operation started while the end position
           *          describe the position where the drop occurred.
           * @param startPos - the position where the drag and drop event started.
           * @param endPos - the position where the drop operation was issued.
           */
          DropEvent(const utils::Vector2f& startPos,
                    const utils::Vector2f& endPos,
                    EngineObject* receiver = nullptr);

          ~DropEvent();

          void
          populateFromEngineData(Engine& engine) override;

          /**
           * @brief - Return the position of the mouse when the drag and drop 
           *          started.
           * @return - the position of the mouse at the beginning of the operation.
           */
          const utils::Vector2f&
          getStartPosition() const noexcept;

          /**
           * @brief - Return the position of the mouse when the drop operation was
           *          issued.
           * @return - the position of the mouse at the end of the operation.
           */
          const utils::Vector2f&
          getEndPosition() const noexcept;

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
           * @brief - Describes the position of the mouse at the beginning and at the
           *          end of the drag and drop operation.
           */
          utils::Vector2f m_startPosition;
          utils::Vector2f m_endPosition;

      };

      using DropEventShPtr = std::shared_ptr<DropEvent>;
    }
  }
}

# include "DropEvent.hxx"

#endif    /* DROP_EVENT_HH */
