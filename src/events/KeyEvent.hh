#ifndef    KEY_EVENT_HH
# define   KEY_EVENT_HH

# include "Event.hh"
# include <SDL2/SDL.h>

namespace sdl {
  namespace core {
    namespace engine {

      class KeyEvent: public Event {
        public:

          KeyEvent(const SDL_KeyboardEvent& event);

          ~KeyEvent();

          void
          populateFromEngineData(Engine& engine) override;

          int
          getKey() const noexcept;

          bool
          isPress() const noexcept;

          bool
          isRelease() const noexcept;

          bool
          isEscape() const noexcept;

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

          SDL_KeyboardEvent m_key;

      };

    }
  }
}

# include "KeyEvent.hxx"

#endif    /* KEY_EVENT_HH */
