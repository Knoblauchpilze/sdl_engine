#ifndef    EVENT_HXX
# define   EVENT_HXX

# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

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
        m_receiver(receiver)
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

    }
  }
}

#endif    /* EVENT_HXX */
