#ifndef    FOCUS_EVENT_HXX
# define   FOCUS_EVENT_HXX

# include "FocusEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      FocusEvent::~FocusEvent() {}

      inline
      bool
      FocusEvent::gotFocus() const noexcept {
        return getType() == Event::Type::FocusIn || getType() == Event::Type::GainFocus;
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

      inline
      bool
      FocusEvent::isPrimary() const noexcept {
        return m_primary;
      }

    }
  }
}

#endif    /* FOCUS_EVENT_HXX */
