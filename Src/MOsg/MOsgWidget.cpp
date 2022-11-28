#include "MOsgWidget.h"

using namespace NS_MOsg;

MOsgWidget::MOsgWidget(MOsgScene* pScene, QWidget *parent) : QGraphicsView(parent)
  ,m_pScene(new QGraphicsScene)
{
    setScene(m_pScene);

    //    QSurfaceFormat format;
    //    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    //    m_pGlViewPort = new QOpenGLWidget(this);
    //    m_pGlViewPort->setFormat(format);
    //    m_pGlViewPort->setMouseTracking(true);
    //    m_pGlViewPort->setMaximumSize(10000, 10000);
    //    setViewport(m_pGlViewPort);
    //    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QGLFormat format;
    format.setProfile(QGLFormat::CompatibilityProfile);
    m_pGlViewPort = new QGLWidget(format, this);
    m_pGlViewPort->setMouseTracking(true);
    m_pGlViewPort->setMaximumSize(10000, 10000);
    setViewport(m_pGlViewPort);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);


    m_pViewer = new osgViewer::Viewer;
    m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    m_pViewer->addEventHandler(new osgViewer::StatsHandler);
    m_pViewer->getCamera()->setNearFarRatio(0.0001);
    m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
    m_pViewer->getCamera()->setClearColor(osg::Vec4(51.0 / 255, 51.0 / 255, 102.0 / 255, 1));

    m_pGraphicsWindow = m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());

    m_pViewer->setSceneData(pScene);
    m_pViewer->realize();

    startTimer(16);
}

bool MOsgWidget::viewportEvent(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::TouchBegin:
    {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        unsigned int id = 0;
        osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
        foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
        {
            QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
            if (listItems.size() > 0)
            {
                return true;
            }
            unsigned int tap_count = touchPoints.size();
            if (!osgEvent)
            {
                osgEvent = m_pGraphicsWindow->getEventQueue()->touchBegan(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
            }
            else
            {
                osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
            }
            id++;
        }
    }
        break;
    case QEvent::TouchEnd:
    {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        unsigned int id = 0;
        osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
        foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
        {
            QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
            if (listItems.size() > 0)
            {
                return true;
            }
            unsigned int tap_count = touchPoints.size();
            if (!osgEvent)
            {
                osgEvent = m_pGraphicsWindow->getEventQueue()->touchEnded(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y(), tap_count);
            }
            else
            {
                osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y());
            }
            id++;
        }
    }
        break;
    case QEvent::TouchUpdate:
    {
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        unsigned int id = 0;
        osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
        foreach(const QTouchEvent::TouchPoint& touchPoint, touchPoints)
        {
            QList<QGraphicsItem*> listItems = items(mapToScene(touchPoint.pos().x(), touchPoint.pos().y()).toPoint());
            if (listItems.size() > 0)
            {
                return true;
            }
            unsigned int tap_count = touchPoints.size();
            if (!osgEvent)
            {
                osgEvent = m_pGraphicsWindow->getEventQueue()->touchMoved(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
            }
            else
            {
                osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
            }
            id++;
        }
    }
        break;
    default:
        return QGraphicsView::viewportEvent(event);
    }
    return true;
}

void MOsgWidget::setKeyboardModifiers(QInputEvent* event)
{
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;

    m_pGraphicsWindow->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
}

void MOsgWidget::keyPressEvent(QKeyEvent* event)
{
    QPoint pos = QCursor::pos();
    QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
    if (listItems.size() <= 0)
    {
        setKeyboardModifiers(event);
        m_pGraphicsWindow->getEventQueue()->keyPress(
                    (osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
    }

    if(event->key() == Qt::Key_S)
    {

    }
    else
    {

    }
    QGraphicsView::keyPressEvent(event);
}

void MOsgWidget::keyReleaseEvent(QKeyEvent* event)
{
    setKeyboardModifiers(event);
    m_pGraphicsWindow->getEventQueue()->keyRelease(
                (osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));

    QGraphicsView::keyReleaseEvent(event);
}

void MOsgWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
    if (listItems.size() > 0)
    {
        QGraphicsView::mousePressEvent(event);
    }
    else
    {
        int button = 0;
        switch (event->button())
        {
        case Qt::LeftButton: button = 1; break;
        case Qt::MidButton: button = 2; break;
        case Qt::RightButton: button = 3; break;
        case Qt::NoButton: button = 0; break;
        default: button = 0; break;
        }
        setKeyboardModifiers(event);
        m_pGraphicsWindow->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
    }
}

void MOsgWidget::mouseReleaseEvent(QMouseEvent* event)
{
    int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    setKeyboardModifiers(event);
    m_pGraphicsWindow->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

    QGraphicsView::mouseReleaseEvent(event);
}

void MOsgWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pos = QCursor::pos();
    QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
    if (listItems.size() > 0)
    {
        return;
    }
    int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton: button = 1; break;
    case Qt::MidButton: button = 2; break;
    case Qt::RightButton: button = 3; break;
    case Qt::NoButton: button = 0; break;
    default: button = 0; break;
    }
    setKeyboardModifiers(event);
    m_pGraphicsWindow->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

    QGraphicsView::mouseDoubleClickEvent(event);
}

void MOsgWidget::mouseMoveEvent(QMouseEvent* event)
{
    setKeyboardModifiers(event);
    m_pGraphicsWindow->getEventQueue()->mouseMotion(event->x(), event->y());
    QGraphicsView::mouseMoveEvent(event);
}

void MOsgWidget::wheelEvent(QWheelEvent* event)
{
    setKeyboardModifiers(event);
    m_pGraphicsWindow->getEventQueue()->mouseScroll(
                event->orientation() == Qt::Vertical ?
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_DOWN : osgGA::GUIEventAdapter::SCROLL_UP) :
                    (event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
    QGraphicsView::wheelEvent(event);
}

void MOsgWidget::resizeEvent(QResizeEvent *event)
{
    if (scene())
    {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    }

    const QSize& size = event->size();
    m_pGraphicsWindow->resized(x(), y(), size.width(), size.height());
    m_pGraphicsWindow->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
    m_pGraphicsWindow->requestRedraw();

    const QSize& oldSize = event->oldSize();
    int oldWidth = oldSize.width();
    int oldHeight = oldSize.height();

    int newWidth = size.width();
    int newHeight = size.height();

    double widthChangeRatio = double(newWidth) / double(oldWidth);
    double heigtChangeRatio = double(newHeight) / double(oldHeight);
    double aspectRatioChange = widthChangeRatio / heigtChangeRatio;
    QGraphicsView::resizeEvent(event);
}

void MOsgWidget::moveEvent(QMoveEvent* event)
{
    const QPoint& pos = event->pos();
    m_pGraphicsWindow->resized(pos.x(), pos.y(), width(), height());
    m_pGraphicsWindow->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

    QGraphicsView::moveEvent(event);
}

void MOsgWidget::timerEvent(QTimerEvent *event)
{
    scene()->update();
}

void MOsgWidget::drawBackground(QPainter *painter, const QRectF& rect)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
    {
        return;
    }

    // Save the painter state
    painter->save();
    painter->beginNativePainting();

    // OSG帧更新
    m_pViewer->frame();

    painter->endNativePainting();
    painter->restore();

    //    painter->beginNativePainting();
    //    m_pViewer->frame();
    //    painter->endNativePainting();
}

void MOsgWidget::drawForeground(QPainter *painter, const QRectF &rect)
{
    //    painter->setPen( Qt::white );
    //    painter->setBrush(QBrush(QColor(255,255,0,127)));
    //    painter->drawRect(rect);
}
