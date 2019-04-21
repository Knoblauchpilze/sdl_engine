
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
          case Type::Enter:
            name = std::string("\"enter\"");
            break;
          case Type::FocusIn:
            name = std::string("\"focus_in\"");
            break;
          case Type::FocusOut:
            name = std::string("\"focus_out\"");
            break;
          case Type::GeometryUpdate:
            name = std::string("\"geometry_update\"");
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
          case Type::MouseButtonPress:
            name = std::string("\"mouse_button_press\"");
            break;
          case Type::MouseButtonRelease:
            name = std::string("\"mouse_button_release\"");
            break;
          case Type::MouseMove:
            name = std::string("\"mouse_move\"");
            break;
          case Type::MouseWheel:
            name = std::string("\"mouse_wheel\"");
            break;
          case Type::Refresh:
            name = std::string("\"refresh\"");
            break;
          case Type::Repaint:
            name = std::string("\"repaint\"");
            break;
          case Type::Resize:
            name = std::string("\"resize\"");
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
          default:
            break;
        }

        return name;
      }

      void
      Event::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

    }
  }
}
