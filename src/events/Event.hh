#ifndef    EVENT_HH
# define   EVENT_HH

# include <memory>
# include <core_utils/CoreObject.hh>

namespace sdl {
  namespace core {
    namespace engine {

      class Event: public utils::CoreObject {
        public:

          // Describes the available type of events.
          enum class Type {
            None,
            KeyPress,
            KeyRelease,
            MouseButtonPress,
            MouseButtonRelease,
            MouseMove,
            MouseWheel,
            Quit
          };

        public:

          ~Event();

          bool
          isAccepted() const noexcept;

          void
          accept() noexcept;

          void
          setAccepted(const bool accepted) noexcept;

          Type
          getType() const noexcept;

        protected:

          Event(const Type& type = Type::None,
                const std::string& name = std::string("event"));

          void
          setType(const Type& type) noexcept;

        private:

          bool m_accepted;
          Type m_type;

      };

      using EventShPtr = std::shared_ptr<Event>;
    }
  }
}

# include "Event.hxx"

#endif    /* EVENT_HH */
