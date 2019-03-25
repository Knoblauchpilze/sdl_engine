#ifndef    EVENT_LISTENER_HH
# define   EVENT_LISTENER_HH

# include "KeyEvent.hh"
# include "MouseEvent.hh"
# include "QuitEvent.hh"
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class EventListener: public utils::CoreObject {
        public:

          struct Interaction {
            using Mask = unsigned char;

            static constexpr Mask NoInteraction = 0x00;

            static constexpr Mask KeyPressed = 0x01;
            static constexpr Mask KeyReleased = 0x02;
            static constexpr Mask Key = KeyPressed | KeyReleased;

            static constexpr Mask MouseButtonPressed = 0x04;
            static constexpr Mask MouseButtonReleased = 0x08;
            static constexpr Mask MouseButton = MouseButtonPressed | MouseButtonReleased;

            static constexpr Mask MouseMotion = 0x10;

            static constexpr Mask MouseWheelDown = 0x20;
            static constexpr Mask MouseWheelUp = 0x40;
            static constexpr Mask MouseWheel = MouseWheelDown | MouseWheelUp;

            static constexpr Mask Mouse = MouseButton | MouseMotion | MouseWheel;

            static constexpr Mask Quit = 0x80;

            static constexpr Mask FullInteraction = Key | Mouse | Quit;

          };

        public:

          EventListener(const std::string& name,
                        const Interaction::Mask& mask);

          virtual ~EventListener();

          const Interaction::Mask&
          getInteractionMask() const noexcept;

          virtual void
          onKeyPressedEvent(const KeyEvent& keyEvent);

          virtual void
          onKeyReleasedEvent(const KeyEvent& keyEvent);

          virtual void
          onMouseMotionEvent(const MouseEvent& mouseMotionEvent);

          virtual void
          onMouseButtonPressedEvent(const MouseEvent& mouseButtonEvent);

          virtual void
          onMouseButtonReleasedEvent(const MouseEvent& mouseButtonEvent);

          virtual void
          onMouseWheelEvent(const MouseEvent& event);

          virtual void
          onQuitEvent(const QuitEvent& event);

        protected:

          bool
          isRelevant(const Interaction::Mask& event) const noexcept;

        private:

          Interaction::Mask m_mask;

      };

    }
  }
}

# include "EventListener.hxx"

#endif    /* EVENT_LISTENER_HH */
