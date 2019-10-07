#ifndef    KEY_EVENT_HH
# define   KEY_EVENT_HH

# include <memory>
# include <SDL2/SDL.h>
# include "Event.hh"
# include "KeyUtils.hh"
# include "KeyModifier.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class KeyEvent: public Event {
        public:

          KeyEvent(const SDL_KeyboardEvent& event);

          ~KeyEvent();

          void
          populateFromEngineData(Engine& engine) override;

          Key
          getKey() const noexcept;

          KeyModifier
          getModifiers() const noexcept;

          bool
          isPress() const noexcept;

          bool
          isRelease() const noexcept;

          bool
          isRepeat() const noexcept;

          bool
          isEscape() const noexcept;

          /**
           * @brief - Used to determine whether the code of the key pressed or released
           *          corresponds to an alpha numeric value.
           *          This is especially useful in case we want to react to specific keys.
           * @return - `true` if the key pressed or released belongs to `[a-z0-9]` and
           *           `false` otherwise.
           */
          bool
          isAlphaNumeric() const noexcept;

          /**
           * @brief - Used to determine whether the code of the key pressed or released
           *          corresponds to a printable character.
           *          This is useful in order to determine whether we can display this
           *          character for example in a text box.
           * @return - `true` if the character can be displayed, `false` otherwise.
           */
          bool
          isPrintable() const noexcept;

          /**
           * @brief - Used to return the char code equivalent to the alpha numeric key
           *          pressed or released. Note that if the key is not alpha numeric an
           *          error is raised. One can check if this is the case using the above
           *          method `isAlphaNumeric`.
           * @return - a char which vaule corresponds to the ASCII code of the character
           *           associated to the key of this event.
           */
          char
          getChar() const;

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

          Key m_converted;
          KeyModifier m_mods;

      };


      using KeyEventShPtr = std::shared_ptr<KeyEvent>;
    }
  }
}

# include "KeyEvent.hxx"

#endif    /* KEY_EVENT_HH */
