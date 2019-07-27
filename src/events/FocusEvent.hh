#ifndef    FOCUS_EVENT_HH
# define   FOCUS_EVENT_HH

# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FocusEvent: public Event {
        public:

          /**
           * @brief - Description of the possible reasons for an object to receive
           *          a focus event.
           */
          enum class Reason {
            MouseFocus,   //<! - The mouse (either through click or hover over) triggered the event.
            TabFocus,     //<! - A tab triggered the event.
            BacktabFocus, //<! - A backtab triggered the event.
            OtherFocus    //<! - Other reason.
          };

        public:

          /**
           * @brief - Creates a new focus event with `gainFocus` indicating whether
           *          the focus was gained or lost. The user should specify the type
           *          of focus which has triggered this event chosen among the list
           *          of `Reason`.
           * @param gainFocus - `true` if this event should represent a focus gain
           *                    and `false` otherwise.
           * @param reason - the reason which produced this event.
           * @param receiver - the receiver for this object, `null` by default.
           */
          FocusEvent(const bool gainFocus,
                     const Reason& reason,
                     EngineObject* receiver = nullptr);

          ~FocusEvent();

          void
          populateFromEngineData(Engine& engine) override;

          /**
           * @brief - Returns true if this event is associated with a focus gain
           *          action. Similar to `getType() == Event::Type::FocusIn`.
           * @return - `true` if this event is associated with a focus gain, `false`
           *           otherwise.
           */
          bool
          gotFocus() const noexcept;

          /**
           * @brief - Returns true if this event is associated with a focus loss
           *          action. Similar to `getType() == Event::Type::FocusOut`.
           * @return - `true` if this event is associated with a focus loss, `false`
           *           otherwise.
           */
          bool
          lostFocus() const noexcept;

          /**
           * @brief - Retrieves the reason of the generation of this event. The
           *          value takes one of the possible values of the `Reason`
           *          enumeration.
           * @return - an enumeration value describing the reason of this event.
           */
          const Reason&
          getReason() const noexcept;

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

          Reason m_reason;

      };

    }
  }
}

# include "FocusEvent.hxx"

#endif    /* FOCUS_EVENT_HH */
