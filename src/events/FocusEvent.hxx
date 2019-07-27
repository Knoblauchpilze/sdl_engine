#ifndef    FOCUS_EVENT_HXX
# define   FOCUS_EVENT_HXX

# include "FocusEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FocusEvent::FocusEvent(const bool gainFocus,
                             const Reason& reason,
                             EngineObject* receiver):
        Event(gainFocus ? Event::Type::FocusIn : Event::Type::FocusOut,
              receiver,
              std::string("focus_event")),
        m_reason(reason)
      {}

      inline
      FocusEvent::FocusEvent(const Reason& reason,
                             EngineObject* receiver):
        Event(Event::Type::GainFocus, receiver, std::string("focus_event")),
        m_reason(reason)
      {}

      inline
      FocusEvent::~FocusEvent() {}

      inline
      bool
      FocusEvent::gotFocus() const noexcept {
        return getType() == Event::Type::FocusIn;
      }

      inline
      bool
      FocusEvent::lostFocus() const noexcept {
        return getType() == Event::Type::FocusOut;
      }

      inline
      const FocusEvent::Reason&
      FocusEvent::getReason() const noexcept {
        return m_reason;
      }

    }
  }
}

#endif    /* FOCUS_EVENT_HXX */
