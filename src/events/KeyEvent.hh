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

          /**
           * @brief - Retrieve the raw key as received from the underlying `API`. This key
           *          is linked to a physical position in the keyboard which means that it
           *          might not be best suited depending on the layout of the keyboard.
           * @return - an identifier for the physical key linked to this event.
           */
          RawKey
          getRawKey() const noexcept;

          /**
           * @brief - Return a flag describing the modifiers associated to this key event.
           *          Modifiers usually helps modify the value of the key for example by
           *          making it uppercase or by changing the meaning altogether (like the
           *          `1` keys).
           * @return - the modifiers currently available for this key event.
           */
          KeyModifier
          getModifiers() const noexcept;

          /**
           * @brief - Return the determined layout for the keyboard that produced this event.
           *          Note that this indication might not always be reliable.
           * @return - an enumeration describing the layout of the keyboard that generated this
           *           event.
           */
          const keyboard::Mode&
          getKeyboardLayout() const noexcept;

          /**
           * @brief - Returns `true` if the key associated to this event has been pressed.
           * @return - `true` if this is a key press event, `false` if the key has been
           *           released.
           */
          bool
          isPress() const noexcept;

          /**
           * @brief - Returns `true` if the key associated to this event has been released.
           * @return - `true` if this is a key release event, `false` if the key has been
           *           pressed.
           */
          bool
          isRelease() const noexcept;

          /**
           * @brief - Returns `true` if this event describes a repeated key (i.e. generated
           *          automatically by the operating system after some time) and not a user
           *          generated one.
           * @return - `true` if the event is a repeat of an old event, `false` otherwise.
           */
          bool
          isRepeat() const noexcept;

          /**
           * @brief - Used to determine whether the code of the key pressed or released
           *          corresponds to an alpha numeric value.
           *          This is especially useful in case we want to react to specific keys.
           *          Note that this method uses the `getInterpretedKey` internally so the
           *          work is done not directly on the raw values returned by the `API`.
           *          This methods is mostly suited for display purposes because otherwise
           *          the user is encouraged to use the raw key codes returned by the `API`
           *          rather than interpreting the inputs.
           * @return - `true` if the key pressed or released belongs to `[a-zA-Z0-9]` and
           *           `false` otherwise.
           */
          bool
          isAlphaNumeric() const noexcept;

          /**
           * @brief - Used to determine whether the code of the key pressed or released
           *          corresponds to a printable character. This is useful in order to
           *          determine whether we can display this character for example in a
           *          text box.
           *          Note that as for the `isAlphaNumeric` method relies on the physical
           *          key but also uses the keyboard layout to precisely define if the
           *          key is associated to some displayable content.
           * @return - `true` if the character can be displayed, `false` otherwise.
           */
          bool
          isPrintable() const noexcept;

          /**
           * @brief - Used to return the char code equivalent to the key associated to
           *          this event. Basically it allows to get a human-readable display
           *          of the key for this event. Note that this function uses the raw
           *          key but also accounts for the keyboard layout to get a precise
           *          idea of the character associated to a key.
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

          /**
           * @brief - Performs the initialization of the data for this event based on
           *          the input underlying `API` event.
           */
          void
          init();

          /**
           * @brief - Used to try to perform a guess of the keyboard layout for this
           *          event. Used in order to associate the correct keys to the raw
           *          physical key codes provided by the `API`.
           */
          void
          guessKeyboardLayout() noexcept;

        private:

          SDL_KeyboardEvent m_key;

          /**
           * @brief - Holds the converted value of the raw physical key associated to this
           *          event. This key is linked to a physical position in the keyboard and
           *          does not take the layout into account. This is the preferred way to
           *          bind some processing on specific keys because it does not depend on
           *          the layout of the keyboard. This way no matter the layout processes
           *          will always be triggered by the keys at the same position.
           */
          RawKey m_raw;

          /**
           * @brief - The key modifiers associated to this event. Note that the modifier
           *          are triggered by keys so it might happen that the key is also a
           *          modifier.
           */
          KeyModifier m_mods;

          /**
           * @brief - Description of the layout used by the keyboard that generated the
           *          key event.
           *          This mode is determined by querying the underlying `API` to get a
           *          feel of the layout. It might not always be reliable.
           */
          keyboard::Mode m_keyboardLayout;
      };

      using KeyEventShPtr = std::shared_ptr<KeyEvent>;
    }
  }
}

# include "KeyEvent.hxx"

#endif    /* KEY_EVENT_HH */
