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
                                     const utils::Sizei& size)
      {
        return m_engine->createTexture(win, size);
      }

      inline
      utils::Uuid
      EngineDecorator::createTexture(const utils::Sizei& size) {
        return m_engine->createTexture(size);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromFile(const utils::Uuid& win,
                                             const std::string& file)
      {
        return m_engine->createTextureFromFile(win, file);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromFile(const std::string& file) {
        return m_engine->createTextureFromFile(file);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromText(const utils::Uuid& win,
                                             const std::string& text,
                                             ColoredFontShPtr font)
      {
        return m_engine->createTextureFromText(win, text, font);
      }

      inline
      utils::Uuid
      EngineDecorator::createTextureFromText(const std::string& text,
                                             ColoredFontShPtr font)
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
      EventShPtr
      EngineDecorator::pollEvent(bool& moreEvents) {
        return m_engine->pollEvent(moreEvents);
      }

    }
  }
}

#endif    /* ENGINE_DECORATOR_HXX */
