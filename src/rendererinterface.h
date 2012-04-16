#include "renderer.h"
#include <QList>

/**
 * \class RendererInterface
 * \brief Library (*.so) interface.
 * \details All child classes should also inherit QObject
 */
class RendererInterface {
public:
  ///Virtual destructor
  virtual ~RendererInterface();
  /**
   * \brief Library initialization code
   * \details This is called after a library is loaded by QPluginLoader<br>
   * You should initialize and register all your renderers in this method.
   */
  virtual void init() const=0;
  /**
   * \brief list of all renderers in this library
   */
  virtual QList<Renderer*> renderers() const = 0;
};
 Q_DECLARE_INTERFACE(RendererInterface,"org.admiral0.lpsmagic.RendererInterface/1.0")