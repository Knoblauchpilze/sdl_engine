#ifndef    EVENT_LISTENER_HXX
# define   EVENT_LISTENER_HXX

# include <algorithm>
# include "EventListener.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EventListener::~EventListener() {}

      inline
      const EventListener::Interaction::Mask&
      EventListener::getInteractionMask() const noexcept {
        return m_mask;
      }

      inline
      void
      EventListener::onKeyPressedEvent(const KeyEvent& /*keyEvent*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onKeyReleasedEvent(const KeyEvent& /*keyEvent*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onMouseMotionEvent(const MouseEvent& /*mouseMotionEvent*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onMouseButtonPressedEvent(const MouseEvent& /*mouseButtonEvent*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onMouseButtonReleasedEvent(const MouseEvent& /*mouseButtonEvent*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onMouseWheelEvent(const MouseEvent& /*event*/) {
        // Empty implementation
      }

      inline
      void
      EventListener::onQuitEvent(const QuitEvent& /*event*/) {
        // Empty implementation
      }

      inline
      bool
      EventListener::isRelevant(const Interaction::Mask& event) const noexcept {
        return m_mask & event;
      }

    }
  }
}

#endif    /* EVENT_LISTENER_HXX */
