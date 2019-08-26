#ifndef    ENGINE_OBJECT_HH
# define   ENGINE_OBJECT_HH

# include <vector>
# include <mutex>
# include <core_utils/CoreObject.hh>
# include "Event.hh"
# include "EventsQueue.hh"
# include "EnterEvent.hh"
# include "KeyEvent.hh"
# include "MouseEvent.hh"
# include "PaintEvent.hh"
# include "ResizeEvent.hh"
# include "QuitEvent.hh"
# include "WindowEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EngineObject;
      using EngineObjectShPtr = std::shared_ptr<EngineObject>;

      class EngineObject: public utils::CoreObject {
        public:

          EngineObject(const std::string& name = std::string("EngineObject"),
                       const bool allowLog = true);

          virtual ~EngineObject();

          /**
           * @brief - Performs the processing of the input event `e`.
           *          Note that this function returns `true` if the event has been
           *          recognized, and false if this is not the case.
           *          To determine whether the event should be sent to children or
           *          (any other object for that matter) one should check the result
           *          of the `e->isAccepted()` method.
           * @param e - the event to process.
           * @return - true if the event has been recognized and false otherwise.
           *           Sets the field `e->isAccepted()` if the event should not be
           *           propagated further.
           */
          bool
          event(EventShPtr e);

          void
          installEventFilter(EngineObject* filter);

          void
          removeEventFilter(EngineObject* filter);

          /**
           * @brief - Performs the filtering of the input event `e` for the object `watched`.
           *          Returns true if the event is filtered and should be discarded, false
           *          otherwise.
           *          Note that this method does not actually filter anything but inheriting
           *          classes are encouraged to specialize this behavior.
           * @param watched - the object for which the filter should be applied.
           * @param e - the event to filter.
           * @return - true if the event should be filtered (i.e. not transmitted to the
           *           `watched` object) and false otherwise.
           */
          virtual bool
          filterEvent(EngineObject* watched,
                      EventShPtr e);

          virtual void
          setEventsQueue(EventsQueue* queue) noexcept;

          /**
           * @brief - Posts an event to the underlying events queue.
           * @param e - the event to post.
           * @param autosetReceiver - defines whether the input event `e`
           *                          should be assigned this object as a
           *                          receiver. Default value is true (meaning
           *                          that the event will be set to be received
           *                          by this object).
           *                          Note that this flag is ignored if a
           *                          receiver is already set for the event.
           * @param autosetEmitter - defines whether the input event `e`
           *                         should be assigned this object as emitter
           *                         Default value is true (meaning that the
           *                         event will be set to be emitted by this
           *                         object).
           *                         Note that this flag is ignored if an emitter
           *                         is already set for the event.
           */
          void
          postEvent(EventShPtr e,
                    bool autosetReceiver = true,
                    bool autosetEmitter = true) noexcept;

          /**
           * @brief - Contrary to the `postEvent` method, which will only send the event
           *          to the associated events queue (if any), this method actually tries
           *          to insert the input event `e` into the internal events array. This
           *          will allow a processing of this event in the next call to the
           *          `processEvents` method.
           *          Upon inserting the event this method first checks that no other event
           *          of this type is registered in the internal queue and if this is the
           *          case it handles it correctly.
           * @param e - the event to insert in the internal array.
           */
          virtual void
          postLocalEvent(EventShPtr e);

          /**
           * @brief - Returns true if this object contains internal events to process, false
           *          otherwise.
           *          Note that to ensure concurrency safety this method uses a mutex and can
           *          thus not return immediately.
           * @return - true if this object does have events to process, false otherwise.
           */
          bool
          hasEvents();

          /**
           * @brief - Performs a cleaning of all the internal events registered for this
           *          object.
           *          Note that none of the removed events will be processed, each one is
           *          ĵust trashed without further processing.
           */
          void
          clearEvents();

          /**
           * @brief - Used to perform the processing of all internal events registered for
           *          this object. Note that process will loop until no more events are
           *          produced for this object.
           */
          void
          processEvents();

        protected:

          /**
           * @brief - Used to deactivate the events processing for this object. Events will
           *          still be discarded whenever new ones are posted for this object, but
           *          we will still allow this object to serve as relay when posting event
           *          for another object.
           *          Upon the first call to `processEvents` after calling this function, the
           *          remaining events will be discarded.
           *          Note that events processing can be reactivated using the below method.
           *          This method uses the `setActive` method internally and is equivalent
           *          to calling `setActive(true)`.
           */
          void
          disableEventsProcessing() noexcept;

          /**
           * @brief - Used to activate the events processing for this object. Any event posted
           *          directly in the queue of this object will be allowed after calling this
           *          method.
           *          Previous events discarded while the object was in disabled state will not
           *          be reprocessed.
           */
          void
          activateEventsProcessing() noexcept;

          /**
           * @brief - Determine whether this object is able to receiver and process events.
           *          This can be used to completely cut-off the element from events processing
           *          until the `setActive` method is called again. This might be useful for
           *          example to prevent hidden or deactivated elements from processing some
           *          events.
           *          Note that a deactivated object still accepts events directed towards it
           *          but do not process them in any way.
           * @return - true if this item is able to handle events, false otherwise.
           */
          virtual bool
          isActive() const noexcept;

          /**
           * @brief - Used to register the input `other` object to the
           *          same events queue as this object.
           *          It allows not to break the encapsulation of the
           *          events queue by exposing something like `getEventsQueue`.
           *          Note that if no queue is defined for this object this
           *          method does nothing and thus does not override any
           *          existing queue in the `other` object.
           * @param other - the object which should be registered to this
           *                object's events queue.
           */
          virtual void
          registerToSameQueue(EngineObject* other);

          /**
           * @brief - Returns true whenever the input event `e` has this object as
           *          unique receiver and false otherwise.
           * @param e - the event for which the receiver should be checked.
           * @return - true if the event `e` has this object as receiver and false
           *           otherwise.
           */
          bool
          isReceiver(const Event& e) const noexcept;

          /**
           * @brief - Returns true whenever the input event `e` has this object as
           *          emitter and false otherwise.
           * @param e - the event for which the emitter should be checked.
           * @return - true if the event `e` has this object as emitter and false
           *           otherwise.
           */
          bool
          isEmitter(const Event& e) const noexcept;

          /**
           * @brief - Used to request the deletion of all events of the input type
           *          from the internal queue. If no such event exist nothing happens.
           *          Note that this method will most likely remove `0` or `1` event(s).
           * @param type - the type of events to remove.
           */
          void
          removeEvents(const Event::Type& type) noexcept;

          /**
           * @brief - Interface method which is called upon inserting any event to the
           *          local events queue. This gives a chance to inheriting classes to
           *          process the events currently registered to the queue (including
           *          the one which triggered this call) in order to trim some if they
           *          are not needed anymore.
           *          The precise behavior on this method is dependent on each child
           *          class.
           * @param events - the array containing all the events currently registered
           *                 into the internal events queue.
           */
          virtual void
          trimEvents(std::vector<EventShPtr>& events);

          /**
           * @brief - Performs the handling of the input event `e` through calling the
           *          adequate method based on the type of the event. The input event
           *          is also casted into its dynamic type so that it is easier for
           *          handler methods to work with.
           *          Inheriting classes are encouraged to reimplement the individual
           *          handler methods instead of this specific method.
           *          Note that this method will by default accept the event (through
           *          calling the `accept` method) if the receiver is set to this object.
           *          Also note that the return value does not indicate whether the event
           *          was accepted but whether it was recognized by this object.
           * @param e - the event to handle.
           * @return - true if the event was recognized, false otherwise.
           */
          virtual bool
          handleEvent(EventShPtr e);

          virtual bool
          enterEvent(const EnterEvent& e);

          virtual bool
          focusInEvent(const FocusEvent& e);

          virtual bool
          focusOutEvent(const FocusEvent& e);

          virtual bool
          gainFocusEvent(const FocusEvent& e);

          virtual bool
          geometryUpdateEvent(const Event& e);

          virtual bool
          hideEvent(const Event& e);

          virtual bool
          keyPressEvent(const KeyEvent& e);

          virtual bool
          keyReleaseEvent(const KeyEvent& e);

          virtual bool
          leaveEvent(const Event& e);

          virtual bool
          lostFocusEvent(const FocusEvent& e);

          virtual bool
          mouseButtonPressEvent(const MouseEvent& e);

          virtual bool
          mouseButtonReleaseEvent(const MouseEvent& e);

          virtual bool
          mouseMoveEvent(const MouseEvent& e);

          virtual bool
          mouseWheelEvent(const MouseEvent& e);

          virtual bool
          repaintEvent(const PaintEvent& e);

          virtual bool
          resizeEvent(ResizeEvent& e);

          virtual bool
          showEvent(const Event& e);

          virtual bool
          windowEnterEvent(const WindowEvent& e);

          virtual bool
          windowLeaveEvent(const WindowEvent& e);

          virtual bool
          windowResizeEvent(const WindowEvent& e);

          virtual bool
          quitEvent(const QuitEvent& e);

          virtual bool
          zOrderChanged(const Event& e);

        private:

          using Filters = std::vector<EngineObject*>;
          using Filter = Filters::const_iterator;
          using Events = std::vector<EventShPtr>;

          Filter
          findFilter(EngineObject* filter) const;

          bool
          validFilter(const Filter& filter) const noexcept;

          void
          removeFilter(const Filter& filter);

          /**
           * @brief - Used to sort the local events registered in the internal `m_queue`
           *          according to the order of importance defined by the `Event` class.
           *          This method is called upon inserting a new event in the internal
           *          queue and allow to process events in their order of importance.
           *          This helps minimizing the number of events needed as we process
           *          the events which might generate more events first.
           *          Triggers a call to `trimEvents` internally which allows inheriting
           *          classes to filter even more some events (such as duplicated events,
           *          or any other process).
           */
          void
          sortLocalEvents();

          /**
           * @brief - Used to de/activate this item so that it can handle events. Any call to
           *          this method will either activate events handling or deactivate it.
           *          Note that a deactivated element still accepts events directed towards
           *          another object (so it can still serve as a relay) but events directed
           *          to this object are discarded.
           *          Calling this method takes effect immediately (meaning for example that
           *          any remaining events in the loop will be discarded).
           * @param active - the activation status for this widget regarding events.
           */
          void
          setActive(const bool active) noexcept;

        private:

          Filters m_filters;
          EventsQueue* m_queue;

          std::mutex m_eventsLocker;
          Events m_events;

          bool m_active;

      };

    }
  }
}

# include "EngineObject.hxx"

#endif    /* ENGINE_OBJECT_HH */
