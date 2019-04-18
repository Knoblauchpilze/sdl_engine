#ifndef    ENGINE_DECORATOR_HXX
# define   ENGINE_DECORATOR_HXX

# include "EngineDecorator.hh"

namespace sdl {
  namespace core {
    namespace engine {

      inline
      utils::Uuid
      EngineDecorator::createWindow(const utils::Sizei& size,
                                    const std::string& title)
      {
        return m_engine->createWindow(size, title);
      }

      inline
      void
      EngineDecorator::setWindowIcon(const utils::Uuid& uuid,
                                     const std::string& icon)
      {
        m_engine->setWindowIcon(uuid, icon);
      }

      inline
      void
      EngineDecorator::clearWindow(const utils::Uuid& uuid) {
        m_engine->clearWindow(uuid);
      }

      inline
      void
      EngineDecorator::renderWindow(const utils::Uuid& uuid) {
        m_engine->renderWindow(uuid);
      }

      inline
      void
      EngineDecorator::destroyWindow(const utils::Uuid& uuid) {
        m_engine->destroyWindow(uuid);
      }

      inline
      utils::Uuid
      EngineDecorator::createTexture(const utils::Uuid& win,
                                     const utils::Sizei& size,
                                     const Palette::ColorRole& role)
      {
        return m_engine->createTexture(win, size, role);
      }

      inline
      utils::Uuid
      EngineDecorator::createTexture(const utils::Sizei& size,
                                     const Palette::ColorRole& role)
      {
        return m_engine->createTexture(size, role);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromFile(const utils::Uuid& win,
                                             const std::string& file,
                                             const Palette::ColorRole& role)
      {
        return m_engine->createTextureFromFile(win, file, role);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromFile(const std::string& file,
                                             const Palette::ColorRole& role)
      {
        return m_engine->createTextureFromFile(file, role);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromText(const utils::Uuid& win,
                                             const std::string& text,
                                             const utils::Uuid& font)
      {
        return m_engine->createTextureFromText(win, text, font);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromText(const std::string& text,
                                             const utils::Uuid& font)
      {
        return m_engine->createTextureFromText(text, font);
      }

      inline
      void
      EngineDecorator::fillTexture(const utils::Uuid& uuid,
                                   const Palette& palette)
      {
        m_engine->fillTexture(uuid, palette);
      }

      inline
      void
      EngineDecorator::setTextureAlpha(const utils::Uuid& uuid,
                                       const Color& color)
      {
        m_engine->setTextureAlpha(uuid, color);
      }

      inline
      void
      EngineDecorator::setTextureRole(const utils::Uuid& uuid,
                                      const Palette::ColorRole& role)
      {
        m_engine->setTextureRole(uuid, role);
      }

      inline
      void
      EngineDecorator::drawTexture(const utils::Uuid& tex,
                                   const utils::Uuid* on,
                                   utils::Boxf* where)
      {
        m_engine->drawTexture(tex, on, where);
      }

      inline
      utils::Sizei
      EngineDecorator::queryTexture(const utils::Uuid& uuid) {
        return m_engine->queryTexture(uuid);
      }

      inline
      void
      EngineDecorator::destroyTexture(const utils::Uuid& uuid) {
        m_engine->destroyTexture(uuid);
      }

      inline
      utils::Uuid
      EngineDecorator::createColoredFont(const std::string& name,
                                         const Palette& palette,
                                         const int& size)
      {
        return m_engine->createColoredFont(name, palette, size);
      }

      inline
      void
      EngineDecorator::destroyColoredFont(const utils::Uuid& uuid) {
        m_engine->destroyColoredFont(uuid);
      }

      inline
      EventShPtr
      EngineDecorator::pollEvent(bool& moreEvents) {
        return m_engine->pollEvent(moreEvents);
      }

      inline
      void
      EngineDecorator::populateEvent(Event& event) {
        m_engine->populateEvent(event);
      }

      inline
      void
      EngineDecorator::populateEvent(EnterEvent& event) {
        m_engine->populateEvent(event);
      }

      inline
      void
      EngineDecorator::populateEvent(KeyEvent& event) {
        m_engine->populateEvent(event);
      }

      inline
      void
      EngineDecorator::populateEvent(MouseEvent& event) {
        m_engine->populateEvent(event);
      }

      inline
      void
      EngineDecorator::populateEvent(QuitEvent& event) {
        m_engine->populateEvent(event);
      }

      inline
      void
      EngineDecorator::populateEvent(WindowEvent& event) {
        m_engine->populateEvent(event);
      }

    }
  }
}

#endif    /* ENGINE_DECORATOR_HXX */
