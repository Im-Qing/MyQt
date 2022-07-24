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

#include <osgViewer/GraphicsWindow>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osg/Notify>
#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

class MOSG_EXPORT MOsgWidget : public QGraphicsView
{
public:
    MOsgWidget(QWidget *parent = nullptr);
public:
    void setModel(QString filePath);
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
    osg::ref_ptr<osg::Group> m_pRoot;
    osg::ref_ptr<osg::Group> m_pModelNode;
};

#endif // MOSGWIDGET_H
