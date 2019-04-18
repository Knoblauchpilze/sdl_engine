#ifndef    EVENT_HH
# define   EVENT_HH

# include <memory>
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Engine;

      class Event: public utils::CoreObject {
        public:

          // Describes the available type of events.
          enum class Type {
            None,                //<! - Not an event
            KeyPress,            //<! - One of the keyboard's keys has been pressed.
            KeyRelease,          //<! - One of the keyboard's keys has been released.
            MouseButtonPress,    //<! - One of the mouse button has been pressed.
            MouseButtonRelease,  //<! - One of the mouse button has been released.
            MouseMove,           //<! - The mouse cursor has been moved.
            MouseWheel,          //<! - The mouse wheel has been used.
            Enter,               //<! - Mouse enter object's boundaries.
            FocusIn,             //<! - Object gains keyboard focus.
            FocusOut,            //<! - Object loses keyboard focus.
            Leave,               //<! - Mouse leaves the object's boundaries.
            WindowEnter,         //<! - Mouse leaves the window's boundaries.
            WindowLeave,         //<! - Mouse leaves the window's boundaries.
            WindowResize,        //<! - Size of window has been modified.
            Quit                 //<! - Main application was closed.
          };

        public:

          ~Event();

          bool
          isAccepted() const noexcept;

          void
          accept() noexcept;

          void
          ignore() noexcept;

          void
          setAccepted(const bool accepted) noexcept;

          Type
          getType() const noexcept;

          virtual void
          populateFromEngineData(Engine& engine);

        protected:

          Event(const Type& type = Type::None,
                const std::string& name = std::string("event"));

          void
          setType(const Type& type) noexcept;

        private:

          bool m_accepted;
          Type m_type;

      };

      using EventShPtr = std::shared_ptr<Event>;
    }
  }
}

# include "Event.hxx"

#endif    /* EVENT_HH */
