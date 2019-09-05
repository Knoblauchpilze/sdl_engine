
# include "FocusEvent.hh"
# include "Engine.hh"

namespace sdl {
  namespace core {
    namespace engine {

      FocusEvent::FocusEvent(const Event::Type& type,
                             const Reason& reason,
                             bool primary,
                             EngineObject* receiver):
        Event(type, receiver, std::string("focus_event")),
        m_reason(reason),
        m_primary(primary)
      {}

      FocusEventShPtr
      FocusEvent::createEventFromType(const Event::Type& type,
                                      const Reason& reason,
                                      bool primary,
                                      EngineObject* emitter,
                                      EngineObject* receiver)
      {
        FocusEventShPtr e(new FocusEvent(type, reason, primary, receiver));
        e->setEmitter(emitter);

        return e;
      }

      FocusEventShPtr
      FocusEvent::createFocusInEvent(const Reason& reason,
                                     bool primary,
                                     EngineObject* receiver,
                                     EngineObject* emitter)
      {
        return createEventFromType(Event::Type::FocusIn, reason, primary, emitter, receiver);
      }

      FocusEventShPtr
      FocusEvent::createFocusOutEvent(const Reason& reason,
                                      bool primary,
                                      EngineObject* receiver,
                                      EngineObject* emitter)
      {
        return createEventFromType(Event::Type::FocusOut, reason, primary, emitter, receiver);
      }

      FocusEventShPtr
      FocusEvent::createGainFocusEvent(const Reason& reason,
                                       bool primary,
                                       EngineObject* receiver,
                                       EngineObject* emitter)
      {
        return createEventFromType(Event::Type::GainFocus, reason, primary, emitter, receiver);
      }

      FocusEventShPtr
      FocusEvent::createLostFocusEvent(const Reason& reason,
                                       bool primary,
                                       EngineObject* receiver,
                                       EngineObject* emitter)
      {
        return createEventFromType(Event::Type::LostFocus, reason, primary, emitter, receiver);
      }

      FocusEventShPtr
      FocusEvent::copyFromExisting(FocusEventShPtr e,
                                   bool copyEmitter,
                                   bool copyReceiver)
      {
        if (e == nullptr) {
          return nullptr;
        }

        FocusEventShPtr ne(new FocusEvent(e->getType(), e->getReason(), e->isPrimary()));

        if (copyEmitter) {
          ne->setEmitter(e->getEmitter());
        }

        if (copyReceiver) {
          ne->setReceiver(e->getReceiver());
        }

        return ne;
      }

      void
      FocusEvent::populateFromEngineData(Engine& engine) {
        engine.populateEvent(*this);
      }

      bool
      FocusEvent::equal(const Event& other) const noexcept {
        const FocusEvent& e = dynamic_cast<const FocusEvent&>(other);
        return Event::equal(other) && getReason() == e.getReason();
      }

      bool
      FocusEvent::mergePrivate(const Event& other) noexcept {
        // Use the base handler to determine whether the input event can
        // be merged with this event.
        bool canMerge = Event::mergePrivate(other);

        if (!canMerge) {
          // Return early.
          return canMerge;
        }

        // Convert the input `other` event to usable data type.
        const FocusEvent& usable = dynamic_cast<const FocusEvent&>(other);

        // Equalize internal fields.
        m_reason = usable.m_reason;

        // Return the base handler's prescriptions.
        return canMerge;
      }

    }
  }
}
