#ifndef    RESIZE_EVENT_HXX
# define   RESIZE_EVENT_HXX

# include "Event.hh"
# include <core_utils/Uuid.hh>
# include <maths_utils/Size.hh>

namespace sdl {
  namespace core {
    namespace engine {

      inline
      ResizeEvent::ResizeEvent(const utils::Sizef& newSize,
                               const utils::Sizef& oldSize,
                               EngineObject* receiver):
        Event(Event::Type::Resize, receiver, std::string("resize_event")),
        m_new(newSize),
        m_old(oldSize)
      {}

      inline
      ResizeEvent::~ResizeEvent() {}

      inline
      const utils::Sizef&
      ResizeEvent::getNewSize() const noexcept {
        return m_new;
      }

      inline
      const utils::Sizef&
      ResizeEvent::getOldSize() const noexcept {
        return m_old;
      }

      inline
      bool
      ResizeEvent::equal(const Event& other) const noexcept {
        const ResizeEvent& e = dynamic_cast<const ResizeEvent&>(other);
        return Event::equal(other) && getNewSize() == e.getNewSize() && getOldSize() == e.getOldSize();
      }

    }
  }
}

#endif    /* RESIZE_EVENT_HH */
