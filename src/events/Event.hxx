#ifndef    EVENT_HXX
# define   EVENT_HXX

# include "Event.hh"

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
      Event::Timestamp
      Event::getTimestamp() const noexcept {
        return m_timestamp;
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
      Event::hasSDLWinID() const noexcept {
        return m_hasWinID;
      }

      inline
      std::uint32_t
      Event::getSDLWinID() const noexcept {
        return m_sdlWinID;
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
