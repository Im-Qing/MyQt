#pragma once

#include "MOpenGL_global.h"

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QDateTime>
#include <QTimer>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>

#include "MGLCamera.h"

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

    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
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
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    QTimer* m_pTimer;
    MGLCamera* m_pGLCamera;
};
}
