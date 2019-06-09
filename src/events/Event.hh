#ifndef    EVENT_HH
# define   EVENT_HH

# include <memory>
# include <chrono>
# include <core_utils/Uuid.hh>
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Engine;
      class EngineObject;

      class Event: public utils::CoreObject {
        public:

          // Describes the available type of events.
          enum class Type {
            None,                //<! - Not an event
            Enter,               //<! - Mouse enter object's boundaries.
            FocusIn,             //<! - Object gains keyboard focus.
            FocusOut,            //<! - Object loses keyboard focus.
            GeometryUpdate,      //<! - The geometry of a component should be updated.
            Hide,                //<! - Object has been hidden.
            KeyPress,            //<! - One of the keyboard's keys has been pressed.
            KeyRelease,          //<! - One of the keyboard's keys has been released.
            Leave,               //<! - Mouse leaves the object's boundaries.
            MouseButtonPress,    //<! - One of the mouse button has been pressed.
            MouseButtonRelease,  //<! - One of the mouse button has been released.
            MouseMove,           //<! - The mouse cursor has been moved.
            MouseWheel,          //<! - The mouse wheel has been used.
            Refresh,             //<! - Trigger a refrech operation for a component.
            Repaint,             //<! - Trigger a repaint operation for a component.
            Resize,              //<! - Size of the component has been modified.
            Show,                //<! - Object is now visible.
            WindowEnter,         //<! - Mouse leaves the window's boundaries.
            WindowLeave,         //<! - Mouse leaves the window's boundaries.
            WindowResize,        //<! - Size of window has been modified.
            Quit                 //<! - Main application was closed.
          };

          static
          std::string
          getNameFromType(const Type& type) noexcept;

          static
          std::string
          getNameFromEvent(const Event& e) noexcept;

          static
          std::string
          getNameFromEvent(const std::shared_ptr<Event> e) noexcept;

        public:

          Event(const Type& type = Type::None,
                EngineObject* receiver = nullptr,
                const std::string& name = std::string("event"));

          ~Event();

          bool
          operator==(const Event& other) const noexcept;

          bool
          operator!=(const Event& other) const noexcept;

          bool
          isAccepted() const noexcept;

          void
          accept() const noexcept;

          void
          ignore() const noexcept;

          Type
          getType() const noexcept;

          std::chrono::time_point<std::chrono::steady_clock>
          getTimestamp() const noexcept;

          /**
           * @brief - An event is considered spontaneous when there's no associated receiver,
           *          which means it should be transmitted to all receivers.
           *          Kinda equivalent to `getReceiver() == nullptr`.
           * @return - true if this event should be sent to a specific receiver or broadcasted
           *           to any listener.
           */
          bool
          isSpontaneous() const noexcept;

          EngineObject*
          getReceiver() const noexcept;

          void
          setReceiver(EngineObject* receiver) noexcept;

          bool
          hasSDLWinID() const noexcept;

          std::uint32_t
          getSDLWinID() const noexcept;

          const utils::Uuid&
          getWindID() const noexcept;

          void
          setWindowID(const utils::Uuid& uuid) noexcept;

          virtual void
          populateFromEngineData(Engine& engine);

        protected:

          void
          setAccepted(const bool accepted) const noexcept;

          void
          setType(const Type& type) noexcept;

          void
          setSDLWinID(const std::uint32_t& sdlWinID) noexcept;

          virtual bool
          equal(const Event& other) const noexcept;

        private:

          mutable bool m_accepted;
          Type m_type;
          bool m_hasWinID;
          utils::Uuid m_winID;
          std::uint32_t m_sdlWinID;
          EngineObject* m_receiver;

          std::chrono::time_point<std::chrono::steady_clock> m_timestamp;

      };

      using EventShPtr = std::shared_ptr<Event>;
    }
  }
}

# include "Event.hxx"

#endif    /* EVENT_HH */
