#ifndef    EVENTS_UTILS_HH
# define   EVENTS_UTILS_HH

# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      /**
       * @brief - Describes the pass of events processing which can be applied to
       *          this object. A pass describe a type of events to process and
       *          allows for efficient factoring of the newly generated events.
       *          We currently define 2 passes, one for the visibility events
       *          (i.e. show and hide event) and another one for the rest of the
       *          events.
       */
      enum class EventProcessingPass {
        Visibility,  //<!- A pass to process visibility events.
        Rest         //<!- A pass to process the rest of the events.
      };

      /**
       * @brief - Used to determine whether the input event type belongs to the
       *          provided event processing pass. This method can be used to see
       *          whether an event is relevant for a pass.
       * @param type - the event type which should be checked for a given pass.
       * @param pass - the event processing pass which should be checked against
       *               the event type.
       * @return - `true` if the input event type belongs to the event processing
       *           pass and `false` otherwise.
       */
      bool
      belongsToPass(const Event::Type& type,
                    const EventProcessingPass& pass) noexcept;

      /**
       * @brief - Used to retrieve an integer value classigying the input event
       *          type by order of importance relatively to other elements. The
       *          smaller the returned value the more important the event type.
       * @param type - the event type to classify.
       * @return - an integer value representing the relative importance of the
       *           input event type.
       */
      int
      getEventID(const Event::Type& type) noexcept;

      /**
       * @brief - Convenience wrapper for the base `getEventID` method which
       *          takes an event instead of a raw type.
       * @param e - the event for which a valid id should be retrieved. The
       *            id will be computed from the type of this event.
       * @return - a value identical to the value provided by calling the
       *           `getEventID(e.getType())`.
       */
      int
      getEventID(const Event& e) noexcept;

      /**
       * @brief - Convenience wrapper for the base `getEventID` method which
       *          takes a shared pointer to an event.
       * @param e - the event for which a valid id should be retrieved. The
       *            id will be computed from the type of this event.
       * @return - a value identical to the value provided by calling the
       *           `getEventID(*e)`.
       */
      int
      getEventID(const EventShPtr e) noexcept;

    }
  }
}

# include "EventsUtils.hxx"

#endif    /* EVENTS_UTILS_HH */
