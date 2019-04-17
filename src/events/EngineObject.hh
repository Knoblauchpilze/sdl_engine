#ifndef    ENGINE_OBJECT_HH
# define   ENGINE_OBJECT_HH

# include <vector>
# include <core_utils/CoreObject.hh>
# include "Event.hh"
# include "EventQueue.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class EngineObject;
      using EngineObjectShPtr = std::shared_ptr<EngineObject>;

      class EngineObject: public utils::CoreObject {
        public:

          EngineObject(const std::string& name = std::string("EngineObject"),
                       const bool allowLog = true);

          virtual ~EngineObject();

          // Note that this function returns `true` if the event has been recognized,
          // and false if this is not the case.
          // To determine whether the event should be sent to children one should check
          // the `e->isAccepted()` result.
          bool
          event(EventShPtr e);

          void
          installEventFilter(EngineObjectShPtr filter);

          void
          removeEventFilter(EngineObjectShPtr filter);

          virtual bool
          filterEvent(EngineObject* watched,
                      EventShPtr e);

          void
          setEventQueue(EventQueue* queue) noexcept;

        protected:

          // Note that the return value it is true only if the event `e` has been recognized.
          // To check whether the event has been accepted, use the `e->isAccepted()` method.
          virtual bool
          handleEvent(EventShPtr e);

          void
          postEvent(EventShPtr e) noexcept;

        private:

          using Filters = std::vector<EngineObjectShPtr>;

          using Filter = Filters::const_iterator;

          Filter
          findFilter(EngineObjectShPtr filter) const;

          bool
          validFilter(const Filter& filter) const noexcept;

          void
          removeFilter(const Filter& filter);

        private:

          Filters m_filters;
          EventQueue* m_queue;

      };

    }
  }
}

# include "EngineObject.hxx"

#endif    /* ENGINE_OBJECT_HH */
