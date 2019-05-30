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
      bool
      Event::equal(const Event& other) const noexcept {
        return
          m_type == other.m_type &&
          m_receiver == other.m_receiver &&
          m_accepted == other.m_accepted
        ;
      }

    }
  }
}

#endif    /* EVENT_HXX */
