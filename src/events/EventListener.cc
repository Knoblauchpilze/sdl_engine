
# include "EventListener.hh"

namespace sdl {
  namespace core {
    namespace engine {

      constexpr EventListener::Interaction::Mask EventListener::Interaction::NoInteraction;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::KeyPressed;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::KeyReleased;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::Key;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseButtonPressed;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseButtonReleased;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseButton;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseMotion;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseWheelDown;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseWheelUp;
      constexpr EventListener::Interaction::Mask EventListener::Interaction::MouseWheel;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::Mouse;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::Quit;

      constexpr EventListener::Interaction::Mask EventListener::Interaction::FullInteraction;

      EventListener::EventListener(const std::string& name,
                                  const Interaction::Mask& mask):
        utils::CoreObject(name),
        m_mask(mask)
      {
        // Nothing to do.
      }

    }
  }
}
