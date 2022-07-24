#ifndef MOSGWIDGET_H
#define MOSGWIDGET_H

#include "MOsg_global.h"

#include <QInputEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QPaintEngine>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QDebug>

#include <osg/Notify>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/GUIEventHandler>
#include <osgDB/ReadFile>

#include "MOsgScene.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgWidget : public QGraphicsView
{
public:
    MOsgWidget(MOsgScene* pScene, QWidget *parent = nullptr);
protected:
    bool viewportEvent(QEvent* event);
    void setKeyboardModifiers(QInputEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void moveEvent(QMoveEvent* event);
    virtual void timerEvent(QTimerEvent *event);

    virtual void drawForeground(QPainter *painter, const QRectF& rect);
    virtual void drawBackground(QPainter *painter, const QRectF& rect);
private:
    QGraphicsScene *m_pScene;
    QOpenGLWidget* m_pGlViewPort;

    osg::ref_ptr<osgViewer::GraphicsWindow> m_pGraphicsWindow;
    osg::ref_ptr<osgViewer::Viewer> m_pViewer;
};
}

#endif // MOSGWIDGET_H
