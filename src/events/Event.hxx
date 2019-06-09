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

        m_timestamp(std::chrono::steady_clock::now())
      {
        setService(std::string("event"));
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
      std::chrono::time_point<std::chrono::steady_clock>
      Event::getTimestamp() const noexcept {
        return m_timestamp;
      }

      inline
      bool
      Event::isSpontaneous() const noexcept {
        return m_receiver == nullptr;
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

      inline
      bool
      Event::equal(const Event& other) const noexcept {
        return
          m_type == other.m_type &&
          m_receiver == other.m_receiver &&
          m_accepted == other.m_accepted &&
          m_hasWinID == other.m_hasWinID &&
          m_sdlWinID == other.m_sdlWinID &&
          m_winID == other.m_winID
        ;
      }

    }
  }
}

#endif    /* EVENT_HXX */
