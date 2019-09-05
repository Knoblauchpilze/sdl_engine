#ifndef    FOCUS_EVENT_HH
# define   FOCUS_EVENT_HH

# include <memory>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class FocusEvent;
      using FocusEventShPtr = std::shared_ptr<FocusEvent>;

      class FocusEvent: public Event {
        public:

          /**
           * @brief - Description of the possible reasons for an object to receive
           *          a focus event.
           */
          enum class Reason {
            HoverFocus,   //<! - A hovering action triggered the event.
            MouseFocus,   //<! - The mouse (mainly through click) triggered the event.
            TabFocus,     //<! - A tab triggered the event.
            BacktabFocus, //<! - A backtab triggered the event.
            OtherFocus    //<! - Other reason.
          };

        public:

          /**
           * @brief - Creates a new focus in event with the specified reason and source
           *          objects.
           * @param reason - the reason of the focus.
           * @param primary - `true` if the focus event to create is a primary source
           *                  of the focus, `false` otherwise.
           * @param receiver - the object to which this event is directed.
           * @param emitter - the emitter of the event.
           * @return - a shared pointer on the newly created event.
           */
          static
          FocusEventShPtr
          createFocusInEvent(const Reason& reason,
                             bool primary,
                             EngineObject* receiver = nullptr,
                             EngineObject* emitter = nullptr);

          /**
           * @brief - Creates a new focus out event with the specified reason and source
           *          objects.
           * @param reason - the reason of the focus.
           * @param primary - `true` if the focus event to create is a primary source
           *                  of the focus, `false` otherwise.
           * @param receiver - the object to which this event is directed.
           * @param emitter - the emitter of the event.
           * @return - a shared pointer on the newly created event.
           */
          static
          FocusEventShPtr
          createFocusOutEvent(const Reason& reason,
                              bool primary,
                              EngineObject* receiver = nullptr,
                              EngineObject* emitter = nullptr);

          /**
           * @brief - Creates a new gain focus event with the specified reason and source
           *          objects.
           * @param reason - the reason of the focus.
           * @param primary - `true` if the focus event to create is a primary source
           *                  of the focus, `false` otherwise.
           * @param receiver - the object to which this event is directed.
           * @param emitter - the emitter of the event.
           * @return - a shared pointer on the newly created event.
           */
          static
          FocusEventShPtr
          createGainFocusEvent(const Reason& reason,
                               bool primary,
                               EngineObject* receiver = nullptr,
                               EngineObject* emitter = nullptr);

          /**
           * @brief - Creates a new lost focus event with the specified reason and source
           *          objects.
           * @param reason - the reason of the focus.
           * @param primary - `true` if the focus event to create is a primary source
           *                  of the focus, `false` otherwise.
           * @param receiver - the object to which this event is directed.
           * @param emitter - the emitter of the event.
           * @return - a shared pointer on the newly created event.
           */
          static
          FocusEventShPtr
          createLostFocusEvent(const Reason& reason,
                               bool primary,
                               EngineObject* receiver = nullptr,
                               EngineObject* emitter = nullptr);

          /**
           * @brief - Performs the copy of the input event in a new focus event. The emitter
           *          and receiver fields are only copied based on the input boolean values.
           * @param e - the focus event to copy.
           * @param copyEmitter - `true` if the emitter of the event `e` should be copied to
           *                      the new event.
           * @param copyReceiver - `true` if the receiver of the event `e` should be copied
           *                       to the new event.
           * @retrun - a new shared pointer describing a focus event with the same focus type
           *           and reason and whose emitter and receiver fields are set based on the
           *           input boolean values.
           */
          static
          FocusEventShPtr
          copyFromExisting(FocusEventShPtr e,
                           bool copyEmitter,
                           bool copyReceiver);

          ~FocusEvent();

          void
          populateFromEngineData(Engine& engine) override;

          /**
           * @brief - Returns true if this event is associated with a focus gain
           *          action. Similar to `getType() == Event::Type::FocusIn`.
           *          Also returns `true` if `getType() == Event::Type::GainFocus`.
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

          /**
           * @brief - Return whether this event is a primary focus event.
           * @return - `true` if the focus event is a primary source of the focus
           *           and `false` otherwise.
           */
          bool
          isPrimary() const noexcept;

        protected:

          /**
           * @brief - Internal wrapper which allows to mutualize some of the code
           *          needed by the factory methods.
           * @param type - the type of the focus event to create.
           * @param reason - the focus reason of the event.
           * @param primary - `true` if the event is a primary focus reason and
           *                  `false` otherwise.
           * @param emitter - the emitter of the event to create.
           * @param receiver - the receiver of the event to create.
           * @return - a shared pointer to the created focus event.
           */
          static
          FocusEventShPtr
          createEventFromType(const Event::Type& type,
                              const Reason& reason,
                              bool primary,
                              EngineObject* emitter,
                              EngineObject* receiver);

          /**
           * @brief - Creates a focus event with the specified type. The type should
           *          be a value among the `FocusIn`, `FocusOut`, `GainFocus` or a
           *          `LostFocus` value. Typically the user should create a focus
           *          event using the factory methods provided as public members.
           *          The user should specify the reason of the focus and possibly
           *          the receiver of the event.
           *          A primary focus event is one that originated from the focus
           *          source while a secondary focus event is mostly generated to
           *          ensure the propagation of the focus information.
           * @param type - the type of the focus event to create.
           * @param reason - the reason of the focus (click, hover, tab, etc.).
           * @param receiver - the receiver of the focus event, null if the event is
           *                   not directed.
           */
          FocusEvent(const Event::Type& type,
                     const Reason& reason,
                     bool primary,
                     EngineObject* receiver = nullptr);

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
          bool m_primary;

      };

    }
  }
}

# include "FocusEvent.hxx"

#endif    /* FOCUS_EVENT_HH */
