#ifndef    EVENT_HH
# define   EVENT_HH

# include <memory>
# include <chrono>
# include <unordered_set>
# include <core_utils/Uuid.hh>
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Engine;
      class EngineObject;

      class Event: public utils::CoreObject {
        public:

          // Describes the available type of events.
          enum class Type {
            None,                //<! - Not an event
            Drop,                //<! - A drag and drop action is finished.
            Enter,               //<! - Mouse enter object's boundaries.
            FocusIn,             //<! - Object gains keyboard focus.
            FocusOut,            //<! - Object loses keyboard focus.
            GainFocus,           //<! - Child gained focus.
            GeometryUpdate,      //<! - The geometry of a component should be updated.
            Hide,                //<! - Object has been hidden.
            KeyboardGrabbed,     //<! - Object has gained keyboard focus.
            KeyboardReleased,    //<! - Object has lost keyboard focus.
            KeyPress,            //<! - One of the keyboard's keys has been pressed.
            KeyRelease,          //<! - One of the keyboard's keys has been released.
            Leave,               //<! - Mouse leaves the object's boundaries.
            LostFocus,           //<! - Child lost focus.
            MouseButtonPress,    //<! - One of the mouse button has been pressed.
            MouseButtonRelease,  //<! - One of the mouse button has been released.
            MouseDoubleClick,    //<! - One of the mouse button has been performing a double click.
            MouseDrag,           //<! - The mouse is being moved while a button is pressed.
            MouseMove,           //<! - The mouse cursor has been moved.
            MouseWheel,          //<! - The mouse wheel has been used.
            Repaint,             //<! - Trigger a repaint operation for a component.
            Resize,              //<! - Size of the component has been modified.
            Show,                //<! - Object is now visible.
            WindowEnter,         //<! - Mouse leaves the window's boundaries.
            WindowLeave,         //<! - Mouse leaves the window's boundaries.
            WindowResize,        //<! - Size of window has been modified.
            Quit,                //<! - Main application was closed.
            ZOrderChanged        //<! - The z order for a component has changed.
          };

          /**
           * @brief - Convenience define to refer to a set of events type. Particularly
           *          useful to handle filtering.
           */
          using Types = std::unordered_set<Type>;

          static
          std::string
          getNameFromType(const Type& type) noexcept;

          static
          std::string
          getNameFromEvent(const Event& e) noexcept;

          static
          std::string
          getNameFromEvent(const std::shared_ptr<Event> e) noexcept;

          static
          Types
          getAllEvents() noexcept;

          static
          Types
          getAllNonWindowEvents() noexcept;

          /**
           * @brief - Convenience using which allows to refer to the timestamp of an event easily.
           */
          using Timestamp = std::chrono::time_point<std::chrono::steady_clock>;

        public:

          Event(const Type& type = Type::None,
                EngineObject* receiver = nullptr,
                const std::string& name = std::string("event"));

          ~Event();

          bool
          operator==(const Event& other) const noexcept;

          bool
          operator!=(const Event& other) const noexcept;

          /**
           * @brief - Returns true if this event has been marked accepted by at least
           *          one of the object it has been transmitted. One can accept an event
           *          by calling the `accept` method.
           *          By default events are not accepted.
           * @return - true if the `accept` method has been called on this event, false
           *           otherwise.
           */
          bool
          isAccepted() const noexcept;

          /**
           * @brief - Used to mark this event as accepted. Once this method is called
           *          this event will not be transmitted to any other object.
           */
          void
          accept() const noexcept;

          /**
           * @brief - Reset any accept flags previously set for this event. Marking an
           *          event as ignored means that the object was not interested in
           *          processing it.
           */
          void
          ignore() const noexcept;

          /**
           * @brief - Retrieves the dynamic type for this event. Useful to know how to
           *          downcast it into its actual type.
           * @return - the type of this event.
           */
          Type
          getType() const noexcept;

          /**
           * @brief - Returns `true` if this event is a mouse event (and thus can be
           *          safely casted to an instance of a `MouseEvent`) and `false`
           *          otherwise.
           * @return - `true` if the event is a mouse event and `false` otherwise.
           */
          bool
          isMouseEvent() const noexcept;

          /**
           * @brief - Returns `true` if this event is a keyboard related event (and
           *          thus can be safely casted to an instance of a `KeyboardEvent`)
           *          and `false` otherwise.
           * @return - `true` if the event is a keyboard event and `false` otherwise.
           */
          bool
          isKeyboardEvent() const noexcept;

          /**
           * @brief - Returns the timestamp for this event. A timestamp is a timed
           *          indication of the creation date of the event. It allows to
           *          compare two events to determine which one is older than the
           *          other for example.
           * @return - the timestamp of the creation of this event.
           */
          Timestamp
          getTimestamp() const noexcept;

          /**
           * @brief - Similar method to `getTimestamp` but returns the timestamp
           *          as a displayable string. Not suited for comparison but for
           *          human readable output.
           * @return - the timestamp of this event as a string.
           */
          std::string
          getTimestampAsString() const noexcept;

          /**
           * @brief - Retrieves the assigned receiver for this event. If the value is not null
           *          the event will be dispatched only to this object, otherwise it will be
           *          transmitted to all the registered listeners.
           * @return - a pointer to the object to which the event is directed. If the returned
           *           value is null the event will be propagated to all listeners.
           */
          EngineObject*
          getReceiver() const noexcept;

          /**
           * @brief - Assigns the input `receiver` object as receiver of this event.
           *          Note that the input value can be null and is not checked for
           *          that. Proceeding with a null input pointer will transform the
           *          event into an undirected event.
           * @param receiver - the receiver object to which this event is directed.
           */
          void
          setReceiver(EngineObject* receiver) noexcept;

          /**
           * @brief - Returns true if the event is directed to a particular object.
           *          Kinda equivalent to `getReceiver() == nullptr`.
           * @return -  true if this event is directed towards a specific object,
           *            false otherwise.
           */
          bool
          isDirected() const noexcept;

          /**
           * @brief - Retrieves the assigned emitter for this event. Note that the
           *          returned pointer might be null if the event is spontaneous.
           * @return - a pointer to the object which spawned this event or null if
           *           the event is spontaneous (i.e. generated by the system).
           */
          EngineObject*
          getEmitter() const noexcept;

          /**
           * @brief - Assigns the input `emitter` object as emitter of this event.
           *          Note that the input value can be null and is not checked for
           *          that. Proceeding with a null input pointer will transform the
           *          event into a spontaneous event.
           * @param emitter - the emitter object which spawned this event.
           */
          void
          setEmitter(EngineObject* emitter) noexcept;

          /**
           * @brief - An event is considered spontaneous when there's no associated
           *          emitter, which means it has probably be emitted by the events
           *          system and not by a specific object.
           *          Kinda equivalent to `getEmitter() == nullptr`.
           * @return - true if this event has not been spawned by a specific object,
           *           false otherwise.
           */
          bool
          isSpontaneous() const noexcept;

          /**
           * @brief - Used to determine whether this event has been emitted by the
           *          input object. Similar to `this->getEmitter() == obj` but with
           *          a nicer semantic.
           * @param obj - the object which should be checked to determine whether it
           *              is the source of `this` event.
           * @return - `true` if the `obj` is the source of `this` event, `false` in
           *           any other case.
           */
          bool
          isEmittedBy(const EngineObject* obj) const noexcept;

          /**
           * @brief - Used to determine whether this event is meant to be received
           *          by the input object. Similar to `this->getReceiver() == obj`
           *          but with a nicer semantic.
           * @param obj - the object which should be checked to determine whether it
           *              is the destination of `this` event.
           * @return - `true` if the `obj` is the destination of `this` event, `false` in
           *           any other case.
           */
          bool
          isReceivedBy(const EngineObject* obj) const noexcept;

          bool
          hasSDLWinID() const noexcept;

          std::uint32_t
          getSDLWinID() const noexcept;

          void
          clearSDLWindID() noexcept;

          const utils::Uuid&
          getWindID() const noexcept;

          void
          setWindowID(const utils::Uuid& uuid) noexcept;

          virtual void
          populateFromEngineData(Engine& engine);

          /**
           * @brief - Used to merge the input `e` with `this` event. Note that this
           *          function only merges the common attribute of an event.
           *          If the `e` is not of the same type as `this` an error is raised
           *          as we cannot really determine what to do with the merge operation.
           *          The internal `mergePrivate` method is called in the case both `this`
           *          and `e` are of the same type.
           *          Inheriting classes are encouraged to specialize the `mergePrivate`
           *          rather than this `merge` method.
           * @param e - the event to merge with `this`.
           */
          void
          merge(const Event& e);

        protected:

          /**
           * @brief - Sets this event as either accepted (if `accepted` is true) or ignored
           *          (if `accepted` is false). Used internally by the `accept` and `ignore`
           *          methods.
           * @param accepted - true if the event should be accepted, false if it should be
           *                   ignored.
           */
          void
          setAccepted(const bool accepted) const noexcept;

          /**
           * @brief - Assign a new dynamic type for this event. This method should be used
           *          with care as the type is used to downcast the event when needed. It
           *          is meant to be used during the construction of any event if some checks
           *          should be performed before determining the precise type of the event.
           *          Typical examples include mouse event, where one must first determine
           *          whether the mouse event corresponds to a mouse button click, a mouse
           *          move and so on.
           * @param type - the new dynamic type of the event.
           */
          void
          setType(const Type& type) noexcept;

          void
          setSDLWinID(const std::uint32_t& sdlWinID) noexcept;

          /**
           * @brief - Used internally by the `operator==` method in case both events have
           *          the same dynamic type. Inheriting classes are encouraged to overload
           *          this method and perform the needed conversion and comparison between
           *          the attributes of the `other` and `this` pointers.
           *          We guarantee at this point that the input `other` can be casted into
           *          a valid instance of the dynamic type of `this`.
           * @param other - the event to compare with `this`.
           */
          virtual bool
          equal(const Event& other) const noexcept;

          /**
           * @brief - Used internally by the `merge` method in case both events have the
           *          same dynamic type. Similar in behavior to `equal` except it performs
           *          the merging of the parameters defined by `other` into `this` event.
           *          Note that each inheriting classes might perform its own merge semantic.
           *          The return value indicates whether the `other` event could be merged.
           *          This can be used by inheriting classes to determine whether their
           *          custom merging stragegy should be performed or not.
           * @param other - the event to merge with `this`.
           * @return - true if `other` was merged with `this` event, false otherwise.
           */
          virtual bool
          mergePrivate(const Event& other) noexcept;

        private:

          mutable bool m_accepted;
          Type m_type;
          bool m_hasWinID;
          utils::Uuid m_winID;
          std::uint32_t m_sdlWinID;
          EngineObject* m_receiver;
          EngineObject* m_emitter;

          Timestamp m_timestamp;

      };

      using EventShPtr = std::shared_ptr<Event>;
    }
  }
}

# include "Event.hxx"

#endif    /* EVENT_HH */
