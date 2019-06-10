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
          installEventFilter(EngineObjectShPtr filter);

          void
          removeEventFilter(EngineObjectShPtr filter);

          virtual bool
          filterEvent(EngineObject* watched,
                      EventShPtr e);

          virtual void
          setEventsQueue(EventsQueue* queue) noexcept;

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
           * @brief - Posts an event to the underlying events queue.
           * @param e - the event to post.
           * @param autosetReceiver - defines whether the input event `e`
           *                          should be assigned this object as a
           *                          receiver. Default value is true (meaning
           *                          that the event will be set to be received
           *                          by this object).
           *                          Note that this flag is ignored if a
           *                          receiver is already set for the event.
           */
          void
          postEvent(EventShPtr e,
                    bool autosetReceiver = true) noexcept;

          /**
           * @brief - Returns true whenever the input event `e` has this object has
           *          unique receiver and false otherwise.
           * @param e - the event for which the receiver should be checked.
           * @return - true if the event `e` has this object has receiver and false
           *           otherwise.
           */
          bool
          isReceiver(const Event& e) const noexcept;

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
          focusInEvent(const Event& e);

          virtual bool
          focusOutEvent(const Event& e);

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
          mouseButtonPressEvent(const MouseEvent& e);

          virtual bool
          mouseButtonReleaseEvent(const MouseEvent& e);

          virtual bool
          mouseMoveEvent(const MouseEvent& e);

          virtual bool
          mouseWheelEvent(const MouseEvent& e);

          virtual bool
          refreshEvent(const PaintEvent& e);

          virtual bool
          repaintEvent(const PaintEvent& e);

          virtual bool
          resizeEvent(const ResizeEvent& e);

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

        private:

          using Filters = std::vector<EngineObjectShPtr>;
          using Filter = Filters::const_iterator;
          using Events = std::vector<EventShPtr>;

          Filter
          findFilter(EngineObjectShPtr filter) const;

          bool
          validFilter(const Filter& filter) const noexcept;

          void
          removeFilter(const Filter& filter);

          void
          sortLocalEvents();

        private:

          Filters m_filters;
          EventsQueue* m_queue;

          std::mutex m_eventsLocker;
          Events m_events;

      };

    }
  }
}

# include "EngineObject.hxx"

#endif    /* ENGINE_OBJECT_HH */
