#pragma once

#include "MOpenGL_global.h"

#include <QOpenGLWidget>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

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
private:
    void drawBox();
    QMatrix4x4 glmMat4ToQMat4(glm::mat4 mat4);
public slots:
    void slot_cameraProjectionChanged(QMatrix4x4 projectionMat);
    void slot_cameraViewMatChanged(QMatrix4x4 viewMat);
private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLTexture m_texture;

    glm::mat4 trans;
    glm::mat4 model;

    QTimer* m_pTimer;
    MGLCamera* m_pGLCamera;
};
}
