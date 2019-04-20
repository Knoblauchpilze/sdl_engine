
# include "EngineObject.hh"

namespace sdl {
  namespace core {
    namespace engine {

      EngineObject::EngineObject(const std::string& name,
                                 const bool allowLog):
        utils::CoreObject(name, allowLog),
        m_filters(),
        m_queue(nullptr)
      {
        setService(std::string("object"));
      }

      bool
      EngineObject::event(EventShPtr e) {
        // Apply all the filters registered for this listener.

        // Assume the event is not filtered.
        bool filtered = false;
        Filter filter = m_filters.cbegin();

        while (filter != m_filters.cend() && !filtered) {
          filtered = (*filter)->filterEvent(this, e);
          ++filter;
        }

        // Check whether this event has been filtered before calling
        // the internal handler.
        if (filtered) {
          // The event has been recognized since it was filtered.
          return true;
        }

        // Proceed with the internal handler: this will determine whether the event
        // has been regognized.
        return handleEvent(e);
      }

      void
      EngineObject::installEventFilter(EngineObjectShPtr filter) {
        // Check filter validity.
        if (filter == nullptr) {
          log(
            std::string("Cannot install event filter, invalid null filter"),
            utils::Level::Warning
          );

          return;
        }

        // Only add this filter if it does not exist yet.
        // The `removeFilter` does handle properly the case where
        // the provided filter does not exist so use it as a cheap
        // solution to remove the `filter` in all cases.
        removeFilter(findFilter(filter));

        // Insert this filter at the end of the internal vector.
        // Based on the mechanism provided by `filterEvent`, if
        // we insert the filter at the end of the vector it will
        // be applied first which is what we want.
        m_filters.push_back(filter);
      }

      void
      EngineObject::postEvent(EventShPtr e,
                              bool autosetReceiver) noexcept {
        // Check event coherence.
        if (e == nullptr) {
          log(
            std::string("Cannot post empty event in queue"),
            utils::Level::Warning
          );
          return;
        }

        // Check whether a queue is provided.
        if (m_queue == nullptr) {
          log(
            std::string("Cannot post event of type ") + std::to_string(static_cast<int>(e->getType())) + ", no queue provided",
            utils::Level::Warning
          );
          return;
        }

        // Assign the receiver to `this` if asked.
        if (autosetReceiver) {
          e->setReceiver(this);
        }

        // Post the event.
        m_queue->postEvent(e);
      }

      bool
      EngineObject::handleEvent(EventShPtr e) {
        // Check for degenerate event.
        if (e == nullptr) {
          log(std::string("Dropping invalid null event"), utils::Level::Warning);
          // The event was not recognized.
          return false;
        }

        // Check the event type and dispatch to the corresponding handler.
        switch (e->getType()) {
          case Event::Type::Enter:
            return enterEvent(*std::dynamic_pointer_cast<EnterEvent>(e));
          case Event::Type::FocusIn:
            return focusInEvent(*e);
          case Event::Type::FocusOut:
            return focusOutEvent(*e);
          case Event::Type::GeometryUpdate:
            return geometryUpdateEvent(*e);
          case Event::Type::KeyPress:
            return keyPressEvent(*std::dynamic_pointer_cast<KeyEvent>(e));
          case Event::Type::KeyRelease:
            return keyReleaseEvent(*std::dynamic_pointer_cast<KeyEvent>(e));
          case Event::Type::Leave:
            return leaveEvent(*e);
          case Event::Type::MouseButtonPress:
            return mouseButtonPressEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
          case Event::Type::MouseButtonRelease:
            return mouseButtonReleaseEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
          case Event::Type::MouseMove:
            return mouseMoveEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
          case Event::Type::MouseWheel:
            return mouseWheelEvent(*std::dynamic_pointer_cast<MouseEvent>(e));
          case Event::Type::Refresh:
            return refreshEvent(*std::dynamic_pointer_cast<PaintEvent>(e));
          case Event::Type::Repaint:
            return repaintEvent(*std::dynamic_pointer_cast<PaintEvent>(e));
          case Event::Type::Resize:
            return resizeEvent(*std::dynamic_pointer_cast<ResizeEvent>(e));
          case Event::Type::WindowEnter:
            return windowEnterEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
          case Event::Type::WindowLeave:
            return windowLeaveEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
          case Event::Type::WindowResize:
            return windowResizeEvent(*std::dynamic_pointer_cast<WindowEvent>(e));
          case Event::Type::Quit:
            return quitEvent(*std::dynamic_pointer_cast<QuitEvent>(e));
          default:
            // Event type is not handled, continue the process.
            break;
        }

        // Not recognized event.
        return false;
      }

    }
  }
}
