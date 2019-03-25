#ifndef    EVENT_HXX
# define   EVENT_HXX

# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      Event::Event(const Type& type,
                   const std::string& name):
        utils::CoreObject(name),
        m_accepted(false),
        m_type(type)
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
      Event::accept() noexcept {
        setAccepted(true);
      }

      inline
      void
      Event::setAccepted(const bool accepted) noexcept {
        m_accepted = accepted;
      }

      inline
      Event::Type
      Event::getType() const noexcept {
        return m_type;
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
