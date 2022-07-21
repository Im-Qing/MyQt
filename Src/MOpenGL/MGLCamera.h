#ifndef MGLCAMERA_H
#define MGLCAMERA_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector3D>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

const float PI = 3.1415926;
const float AngleToRadian = PI/180.0f;

namespace NS_MOpenGL
{
class MGLCamera : public QObject
{
    Q_OBJECT
public:
    explicit MGLCamera(QObject *glWidget);
public:
    QMatrix4x4 getViewMat();
    QMatrix4x4 getProjectionMat();
protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
signals:
    void sign_viewMatChanged(QMatrix4x4 viewMat);
    void sign_projectionMatChanged(QMatrix4x4 projectionMat);
public slots:

private:
    QWidget* m_pGLWidget = nullptr;
    float m_fov = 45.0;
    QMatrix4x4 m_viewMat;
    QMatrix4x4 m_projectionMat;
    QVector3D m_cameraPos{ 0,0,3 };
    QVector3D m_cameraFront{ 0,0,-1 };
    QVector3D m_cameraUp{ 0,1,0 };

    float m_lastX;      //当鼠标点击时为false，此时将m_lastX和m_lastY重新赋值
    float m_lastY;
    float m_cameraYaw = -90.0;
    float m_cameraPitch = 0.0;
    float m_cameraRoll = 0;
};
}

#endif // MGLCAMERA_H
