#ifndef    QUIT_EVENT_HH
# define   QUIT_EVENT_HH

# include "Event.hh"
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      class QuitEvent: public Event {
        public:

          QuitEvent();

          QuitEvent(const SDL_QuitEvent& event);

          ~QuitEvent();

          void
          populateFromEngineData(Engine& engine) override;

        protected:

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific behavior to compare both the common attribute (using the
           *          base handler) and the properties defined by this type of event.
           * @param other - the `other` event to check for equality with `this`.
           * @return - true if both `other` and `this` are equal, false otherwise.
           */
          bool
          equal(const Event& other) const noexcept override;

          /**
           * @brief - Reimplementation of the base `Event` method in order to provide
           *          specific merge strategy for this type of event. We will use the
           *          base handler internally to merge common attributes of the event,
           *          and then downcast the input `other` event to `this` dynamic type
           *          to perform custom merging.
           *          Note that the return value of the base class will indicate whether
           *          we should perform the custom merge strategy.
           *          The return value of this method is indistinguishable from the
           *          return value of the base `Event` method.
           * @param other - the `other` event to merge with `this`.
           * @return - true if the `other` event was merged with `this`, false otherwise.
           */
          bool
          mergePrivate(const Event& other) noexcept override;

        private:

          void
          init();

        private:

          SDL_QuitEvent m_quit;

      };

    }
  }
}

# include "QuitEvent.hxx"

#endif    /* QUIT_EVENT_HH */
