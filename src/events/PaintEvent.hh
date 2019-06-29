#ifndef    PAINT_EVENT_HH
# define   PAINT_EVENT_HH

# include <memory>
# include <maths_utils/Box.hh>
# include "Event.hh"

namespace sdl {
  namespace core {
    namespace engine {

      class PaintEvent: public Event {
        public:

          /**
           * @brief - Creates an event which is used to completely repaint the component.
           *          In order to make it agnostic to the size of the component, we chose
           *          to not provide any size: it is up to the component to retrieve its
           *          internal size and to perform a repaint operation on all of it.
           * @param receiver - the object which will receive this paint event. Leave it
           *                   empty if it needs to be transmitted to all elements.
           */
          PaintEvent(EngineObject* receiver = nullptr);

          /**
           * @brief - Creates an event which is used to repaint the area defined by the
           *          `updateRegion` of the object described by the `receiver` or to be
           *          transmitted to all registered elements if it is left empty.
           * @param updateRegion - the region to update for the component.
           * @param receiver - the object which will receive this paint event. If left
           *                   empty all registered elements will receive it.
           */
          PaintEvent(const utils::Boxf& updateRegion,
                     EngineObject* receiver = nullptr);

          ~PaintEvent();

          /**
           * @brief - Used to determine whether this event is a global paint event or a
           *          localized one. Paint operations might concern only a subset of the
           *          element they should be applied onto, in which case a valid area is
           *          provided during the construction.
           *          But in some specific cases one might want to update the whole area
           *          defined by a component: in this case the `isGlobal` method will
           *          return true and the value provided by `getUpdateRegion` should be
           *          ignored.
           */
          bool
          isGlobal() const noexcept;

          /**
           * @brief - Retrieves the region to update as provided during the construction
           *          of the object. One can check whether this area is valid using the
           *          `isGlobal` method: if this method returns true the area retrieved
           *          by this function will not be valid.
           * @return - the update region associated to this paint event. Might be empty
           *           based on the return value of the `isGlobal` method.
           */
          const utils::Boxf&
          getUpdateRegion() const noexcept;

          void
          populateFromEngineData(Engine& engine) override;

        protected:

          bool
          equal(const Event& other) const noexcept override;

        private:

          utils::Boxf m_updateRegion;

      };

      using PaintEventShPtr = std::shared_ptr<PaintEvent>;
    }
  }
}

# include "PaintEvent.hxx"

#endif    /* PAINT_EVENT_HH */
