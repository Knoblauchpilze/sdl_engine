
# include "Event.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      std::string
      Event::getNameFromType(const Type& type) noexcept {
        std::string name("\"unknown event\"");

        switch (type) {
          case Type::None:
            name = std::string("\"none\"");
            break;
          case Type::Drop:
            name = std::string("\"drop\"");
            break;
          case Type::Enter:
            name = std::string("\"enter\"");
            break;
          case Type::FocusIn:
            name = std::string("\"focus_in\"");
            break;
          case Type::FocusOut:
            name = std::string("\"focus_out\"");
            break;
          case Type::GainFocus:
            name = std::string("\"gain_focus\"");
            break;
          case Type::GeometryUpdate:
            name = std::string("\"geometry_update\"");
            break;
          case Type::Hide:
            name = std::string("\"hide\"");
            break;
          case Type::KeyboardGrabbed:
            name = std::string("\"keyboard_grabbed\"");
            break;
          case Type::KeyboardReleased:
            name = std::string("\"keyboard_released\"");
            break;
          case Type::KeyPress:
            name = std::string("\"key_press\"");
            break;
          case Type::KeyRelease:
            name = std::string("\"key_release\"");
            break;
          case Type::Leave:
            name = std::string("\"leave\"");
            break;
          case Type::LostFocus:
            name = std::string("\"lost_focus\"");
            break;
          case Type::MouseButtonPress:
            name = std::string("\"mouse_button_press\"");
            break;
          case Type::MouseButtonRelease:
            name = std::string("\"mouse_button_release\"");
            break;
          case Type::MouseDoubleClick:
            name = std::string("\"mouse_double_click\"");
            break;
          case Type::MouseDrag:
            name = std::string("\"mouse_drag\"");
            break;
          case Type::MouseMove:
            name = std::string("\"mouse_move\"");
            break;
          case Type::MouseWheel:
            name = std::string("\"mouse_wheel\"");
            break;
          case Type::Repaint:
            name = std::string("\"repaint\"");
            break;
          case Type::Resize:
            name = std::string("\"resize\"");
            break;
          case Type::Show:
            name = std::string("\"show\"");
            break;
          case Type::WindowEnter:
            name = std::string("\"window_enter\"");
            break;
          case Type::WindowLeave:
            name = std::string("\"window_leave\"");
            break;
          case Type::WindowResize:
            name = std::string("\"window_resize\"");
            break;
          case Type::Quit:
            name = std::string("\"quit\"");
            break;
          case Type::ZOrderChanged:
            name = std::string("\"z_order_change\"");
            break;
          default:
            break;
        }

        return name;
      }

      Event::Event(const Type& type,
                   EngineObject* receiver,
                   const std::string& name):
        utils::CoreObject(name),
        m_accepted(false),
        m_type(type),
        m_hasWinID(false),
        m_winID(),
        m_sdlWinID(),
        m_receiver(receiver),
        m_emitter(nullptr),

        m_timestamp(std::chrono::steady_clock::now())
      {
        setService(std::string("event"));
      }

      void
      Event::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      void
      Event::merge(const Event& e) {
        // Check that both `this` and `event` are of the same type.
        if (typeid(*this) != typeid(e)) {
          // This is a problem, we cannot merge events of different
          // type.
          error(
            std::string("Cannot merge event"),
            std::string("Event types are \"") + getNameFromType(getType()) + "\" and \"" + getNameFromType(e.getType()) + "\""
          );
        }

        // Use the internal handler.
        mergePrivate(e);
      }

      bool
      Event::equal(const Event& other) const noexcept {
        return
          m_type == other.m_type &&
          m_receiver == other.m_receiver &&
          m_emitter == other.m_emitter &&
          m_accepted == other.m_accepted &&
          m_hasWinID == other.m_hasWinID &&
          m_sdlWinID == other.m_sdlWinID &&
          m_winID == other.m_winID
        ;
      }

      bool
      Event::mergePrivate(const Event& other) noexcept {
        // Check timestamps to notify in case we merge with an older event.
        if (m_timestamp >= other.m_timestamp && m_type != Type::Repaint) {
          warn("Merging event with timestamp " + other.getTimestampAsString() + " anterior to own " + getTimestampAsString());
        }

        // Copy the fields from `other` to this event.
        m_type = other.m_type;

        m_receiver = other.m_receiver;
        m_emitter = other.m_emitter;

        m_accepted = other.m_accepted;

        m_hasWinID = other.m_hasWinID;
        m_sdlWinID = other.m_sdlWinID;
        m_winID = other.m_winID;

        m_timestamp = other.m_timestamp;

        // Events could be merged.
        return true;
      }

    }
  }
}
