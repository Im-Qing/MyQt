#pragma once

#include <QOpenGLWidget>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

#include "MOpenGL.h"
#include "MGLCamera.h"

namespace NS_MOpenGL
{

class MGLScene;
class MGLModel;

class MOPENGL_EXPORT MGLWidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    MGLWidget(MGLScene* scene, QWidget *parent = Q_NULLPTR);
    ~MGLWidget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public slots:
    void slot_cameraProjectionChanged(QMatrix4x4 projectionMat);
    void slot_cameraViewMatChanged(QMatrix4x4 viewMat);
private:
    MGLScene* m_pScene;
    MGLCamera* m_pGLCamera;

    friend class MGLScene;
    friend class MGLModel;
};
}
