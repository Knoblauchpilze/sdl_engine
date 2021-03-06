#ifndef    EVENT_HXX
# define   EVENT_HXX

# include "Event.hh"
# include <sstream>
# include <iomanip>

namespace sdl {
  namespace core {
    namespace engine {

      inline
      bool
      Event::operator==(const Event& other) const noexcept {
        return typeid(*this) == typeid(other) && equal(other);
      }

      inline
      bool
      Event::operator!=(const Event& other) const noexcept {
        return !operator==(other);
      }

      inline
      std::string
      Event::getNameFromEvent(const Event& e) noexcept {
        return getNameFromType(e.getType());
      }

      inline
      std::string
      Event::getNameFromEvent(const std::shared_ptr<Event> e) noexcept {
        if (e == nullptr) {
          return getNameFromType(Type::None);
        }

        return getNameFromEvent(*e);
      }

      inline
      Event::Types
      Event::getAllEvents() noexcept {
        return Types{
          Type::Drop,
          Type::Enter,
          Type::FocusIn,
          Type::FocusOut,
          Type::GainFocus,
          Type::GeometryUpdate,
          Type::Hide,
          Type::KeyPress,
          Type::KeyRelease,
          Type::Leave,
          Type::LostFocus,
          Type::MouseButtonPress,
          Type::MouseButtonRelease,
          Type::MouseDoubleClick,
          Type::MouseDrag,
          Type::MouseMove,
          Type::MouseWheel,
          Type::Repaint,
          Type::Resize,
          Type::Show,
          Type::WindowEnter,
          Type::WindowLeave,
          Type::WindowResize,
          Type::Quit,
          Type::ZOrderChanged
        };
      }

      inline
      Event::Types
      Event::getAllNonWindowEvents() noexcept {
        Types t = getAllEvents();

        t.erase(Type::WindowEnter);
        t.erase(Type::WindowLeave);
        t.erase(Type::WindowResize);
        t.erase(Type::Quit);

        return t;
      }

      inline
      Event::~Event() {}

      inline
      bool
      Event::isAccepted() const noexcept {
        return m_accepted;
      }

      inline
      void
      Event::accept() const noexcept {
        setAccepted(true);
      }

      inline
      void
      Event::ignore() const noexcept {
        setAccepted(false);
      }

      inline
      Event::Type
      Event::getType() const noexcept {
        return m_type;
      }

      inline
      bool
      Event::isMouseEvent() const noexcept {
        return
          m_type == Type::Drop ||
          m_type == Type::MouseButtonPress ||
          m_type == Type::MouseButtonRelease ||
          m_type == Type::MouseDoubleClick ||
          m_type == Type::MouseDrag ||
          m_type == Type::MouseMove ||
          m_type == Type::MouseWheel
        ;
      }

      inline
      bool
      Event::isKeyboardEvent() const noexcept {
        return
          m_type == Type::KeyPress ||
          m_type == Type::KeyRelease
        ;
      }

      inline
      Event::Timestamp
      Event::getTimestamp() const noexcept {
        return m_timestamp;
      }

      inline
      std::string
      Event::getTimestampAsString() const noexcept {
        // Convert the timestamp to a system clock timepoint.
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + (m_timestamp - std::chrono::steady_clock::now()));

        // Convert to a local time.
        std::tm* localTime = std::localtime(&t);

        // Output this time into a stringstream.
        std::ostringstream localTimeAsStringStream;
        localTimeAsStringStream << std::put_time(localTime, "%d-%m-%Y %H:%M:%S");

        // Return the built-in string.
        return localTimeAsStringStream.str();
      }

      inline
      EngineObject*
      Event::getReceiver() const noexcept {
        return m_receiver;
      }

      inline
      void
      Event::setReceiver(EngineObject* receiver) noexcept {
        m_receiver = receiver;
      }

      inline
      bool
      Event::isDirected() const noexcept {
        return m_receiver != nullptr;
      }

      inline
      EngineObject*
      Event::getEmitter() const noexcept {
        return m_emitter;
      }

      inline
      void
      Event::setEmitter(EngineObject* emitter) noexcept {
        m_emitter = emitter;
      }

      inline
      bool
      Event::isSpontaneous() const noexcept {
        return m_emitter == nullptr;
      }

      inline
      bool
      Event::isEmittedBy(const EngineObject* obj) const noexcept {
        return m_emitter == obj;
      }

      inline
      bool
      Event::isReceivedBy(const EngineObject* obj) const noexcept {
        return m_receiver == obj;
      }

      inline
      bool
      Event::hasSDLWinID() const noexcept {
        return m_hasWinID;
      }

      inline
      std::uint32_t
      Event::getSDLWinID() const noexcept {
        return m_sdlWinID;
      }

      inline
      void
      Event::clearSDLWindID() noexcept {
        // Indicate that this window does not have any linked `SDL` window ID.
        m_hasWinID = false;

        // Reset any assigned logical window identifier.
        m_winID.invalidate();
      }

      inline
      const utils::Uuid&
      Event::getWindID() const noexcept {
        return m_winID;
      }

      inline
      void
      Event::setWindowID(const utils::Uuid& uuid) noexcept {
        m_winID = uuid;
      }

      inline
      void
      Event::setAccepted(const bool accepted) const noexcept {
        m_accepted = accepted;
      }

      inline
      void
      Event::setType(const Type& type) noexcept {
        m_type = type;
      }

      inline
      void
      Event::setSDLWinID(const std::uint32_t& sdlWinID) noexcept {
        m_sdlWinID = sdlWinID;
        m_hasWinID = true;
      }

    }
  }
}

#endif    /* EVENT_HXX */
