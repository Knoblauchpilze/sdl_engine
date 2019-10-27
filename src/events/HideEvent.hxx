#ifndef    HIDE_EVENT_HXX
# define   HIDE_EVENT_HXX

# include "HideEvent.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      HideEvent::HideEvent(const utils::Boxf& region,
                           EngineObject* receiver):
        Event(Event::Type::Hide,
              receiver,
              std::string("hide_event_") + region.toString()),

        m_region(region)
      {}

      inline
      HideEvent::~HideEvent() {}

      inline
      const utils::Boxf&
      HideEvent::getHiddenRegion() const noexcept {
        return m_region;
      }

      inline
      bool
      HideEvent::equal(const Event& other) const noexcept {
        // We want to consider hide event equals if they refer to the same
        // hidden region.
        const HideEvent& e = dynamic_cast<const HideEvent&>(other);

        return Event::equal(other) && getHiddenRegion() == e.getHiddenRegion();
      }

    }
  }
}

#endif    /* HIDE_EVENT_HXX */
