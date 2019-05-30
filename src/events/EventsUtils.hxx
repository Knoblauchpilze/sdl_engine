#ifndef    EVENTS_UTILS_HXX
# define   EVENTS_UTILS_HXX

# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      int
      getEventID(const Event::Type& type) {
        // Assigning an id to en event focuses on providing some
        // kind of ordering between event types.
        // From a logical point of view a mouse move event has not
        // the same priority as a resize event for instance: indeed
        // the resize event will probably issue some more events
        // like recreating the content of the widget, probably
        // recomputing the layout as the available space as been
        // modified and also trigger corresponding events on children
        // objects.
        // These considerations lead to the fact that to be efficient
        // in events processing we should try to order events as
        // precisely as possible so that we do not get stuck in cycles
        // like so:
        // repaint -> resize -> repaint (generated).
        // The above situation would be processed much more efficiently
        // if the `resize` event was handled first: this way we could
        // merge the two `repaint` events generated and perform the
        // processing only once.
        //
        // To perform the sorting, we rely on the sort algorithm provided
        // by the standard library with our custom comparison operator.
        //
        // Among all the possible events types, we set the following
        // precedence:
        // None               Not defined
        // Enter              3
        // FocusIn            5
        // FocusOut           6
        // GeometryUpdate     2
        // KeyPress           Not defined
        // KeyRelease         Not defined
        // Leave              4
        // MouseButtonPress   Not defined
        // MouseButtonRelease Not defined
        // MouseMove          Not defined
        // MouseWheel         Not defined
        // Refresh            Not defined
        // Repaint            7
        // Resize             1
        // WindowEnter        Not defined
        // WindowLeave        Not defined
        // WindowResize       Not defined
        // Quit               Not defined
        // Not that if a type has no associated number it means that
        // it is not compared (and thus set equal to all other non
        // defined types).
        switch (type) {
          case Event::Type::Resize:
            return 1;
          case Event::Type::GeometryUpdate:
            return 2;
          case Event::Type::Enter:
            return 3;
          case Event::Type::Leave:
            return 4;
          case Event::Type::FocusIn:
            return 5;
          case Event::Type::FocusOut:
            return 6;
          case Event::Type::Repaint:
            return 7;
          default:
            return 8;
        }
      }

      int
      getEventID(const Event& e) {
        return getEventID(e.getType());
      }

      int
      getEventID(const EventShPtr e) {
        if (e == nullptr) {
          return getEventID(Event::Type::None);
        }

        return getEventID(*e);
      }

    }
  }
}

#endif    /* EVENTS_UTILS_HXX */
