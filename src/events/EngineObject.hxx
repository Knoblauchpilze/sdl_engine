#ifndef    EVENT_LISTENER_HXX
# define   EVENT_LISTENER_HXX

# include <algorithm>
# include "EngineObject.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      EngineObject::~EngineObject() {
        // Unregister from the event queue if any has been provided.
        if (m_queue != nullptr) {
          m_queue->removeListener(this);
        }
      }

      inline
      void
      EngineObject::removeEventFilter(EngineObjectShPtr filter) {
        // Use the dedicated handler.
        removeFilter(findFilter(filter));
      }

      inline
      bool
      EngineObject::filterEvent(EngineObject* /*watched*/,
                                 EventShPtr /*e*/)
      {
        // No filtering provided here, return false.
        return false;
      }

      inline
      void
      EngineObject::setEventsQueue(EventsQueue* queue) noexcept {
        m_queue = queue;
      }

      inline
      bool
      EngineObject::enterEvent(const engine::EnterEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::focusInEvent(const engine::Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::focusOutEvent(const engine::Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::geometryUpdateEvent(const engine::Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyPressEvent(const engine::KeyEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::keyReleaseEvent(const engine::KeyEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::leaveEvent(const engine::Event& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseButtonPressEvent(const engine::MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseButtonReleaseEvent(const engine::MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseMoveEvent(const engine::MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::mouseWheelEvent(const engine::MouseEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::refreshEvent(const engine::PaintEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::repaintEvent(const engine::PaintEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::resizeEvent(const engine::ResizeEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowEnterEvent(const engine::WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowLeaveEvent(const engine::WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::windowResizeEvent(const engine::WindowEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      bool
      EngineObject::quitEvent(const engine::QuitEvent& /*e*/) {
        // Empty implementation.
        return true;
      }

      inline
      EngineObject::Filter
      EngineObject::findFilter(EngineObjectShPtr filter) const {
        // Traverse the registered filter and try to find the input `filter`.
        Filter internalFilter = m_filters.cbegin();

        while (validFilter(internalFilter) && *internalFilter != filter) {
          ++internalFilter;
        }

        return internalFilter;
      }

      inline
      bool
      EngineObject::validFilter(const Filter& filter) const noexcept {
        return filter != m_filters.cend();
      }

      inline
      void
      EngineObject::removeFilter(const Filter& filter) {
        // Check whether this filter is valid.
        if (validFilter(filter)) {
          // Remove it.
          m_filters.erase(filter);
        }
      }

    }
  }
}

#endif    /* EVENT_LISTENER_HXX */
