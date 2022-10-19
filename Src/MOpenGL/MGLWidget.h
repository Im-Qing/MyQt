#pragma once

#include "MOpenGL_global.h"

#include <QOpenGLWidget>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

#include "MOpenGL.h"
#include "MGLCamera.h"
#include "MGLModel.h"

namespace NS_MOpenGL
{
class MOPENGL_EXPORT MGLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    MGLWidget(QWidget *parent = Q_NULLPTR);
    ~MGLWidget();
public slots:
    void slot_timeout();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public slots:
    void slot_cameraProjectionChanged(QMatrix4x4 projectionMat);
    void slot_cameraViewMatChanged(QMatrix4x4 viewMat);
private:
    QTimer* m_pTimer;
    MGLCamera* m_pGLCamera;

    MGLModel* m_pObject;
    MGLModel* m_pLight;
};
}
