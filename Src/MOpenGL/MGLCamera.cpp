#include "MGLCamera.h"

using namespace NS_MOpenGL;

MGLCamera::MGLCamera(QObject *glWidget) : QObject(glWidget)
{
    m_pGLWidget = qobject_cast<QWidget *>(glWidget);
    //为关联的opengl窗口注册事件
    m_pGLWidget->installEventFilter(this);
}

void MGLCamera::look(float yaw, float pitch, float roll)
{

}

QMatrix4x4 MGLCamera::getViewMat()
{
    m_viewMat.setToIdentity();
    m_viewMat.lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

    return m_viewMat;
}

QMatrix4x4 MGLCamera::getProjectionMat()
{
    m_projectionMat.setToIdentity();
    m_projectionMat.perspective(m_fov, m_pGLWidget->width() * 1.0 / m_pGLWidget->height(), 0.1f, 100.0f);

    return m_projectionMat;
}

bool MGLCamera::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == parent())     //gl窗口事件
    {
        float cameraSpeed = 0.05f;
        switch (ev->type())
        {
        case QEvent::KeyPress:      //按键移动
        {
            auto event = static_cast<QKeyEvent *>(ev);
            switch(event->key())
            {
            case Qt::Key_W:     //前进
                m_cameraPos += cameraSpeed * m_cameraFront;
                break;
            case Qt::Key_S:     //后退
                m_cameraPos -= cameraSpeed * m_cameraFront;
                break;
            case Qt::Key_A:     //向左
                m_cameraPos -=  QVector3D::crossProduct(m_cameraFront, m_cameraUp).normalized();
                break;
            case Qt::Key_D:     //向右
                m_cameraPos +=  QVector3D::crossProduct(m_cameraFront, m_cameraUp).normalized();
                break;
            default:
                break;
            }

            emit sign_viewMatChanged(getViewMat());
        }break;
        case QEvent::MouseMove:
        {
            auto event = static_cast<QMouseEvent *>(ev);
            float xpos = event->x();
            float ypos = event->y();
            if(m_isFirstMouseMove)
            {
                m_lastX = xpos;
                m_lastY = ypos;
                m_isFirstMouseMove = false;
            }

            float xoffset = xpos - m_lastX;
            float yoffset = m_lastY - ypos;
            m_lastX = xpos;
            m_lastY = ypos;

            float sensitivity = 0.05;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            m_cameraYaw += xoffset;
            m_cameraPitch += yoffset;

            if(m_cameraPitch > 89.0f)
                m_cameraPitch = 89.0f;
            if(m_cameraPitch < -89.0f)
                m_cameraPitch = -89.0f;

            m_cameraFront.setX(cos(m_cameraPitch * AngleToRadian) * cos(m_cameraYaw * AngleToRadian));
            m_cameraFront.setY(sin(m_cameraPitch * AngleToRadian));
            m_cameraFront.setZ(cos(m_cameraPitch * AngleToRadian) * sin(m_cameraYaw * AngleToRadian));
            m_cameraFront.normalize();

            emit sign_viewMatChanged(getViewMat());
        }break;
        case QEvent::Wheel:
        {
            auto event = static_cast<QWheelEvent *>(ev);
            float yoffset = 1.0;
            if(event->delta() > 0)      // 当滚轮远离使用者时进行放大
            {
                m_fov -= yoffset;
            }
            else                        // 当滚轮向使用者方向旋转时进行缩小
            {
                m_fov += yoffset;
            }

            emit sign_projectionMatChanged(getProjectionMat());
        }break;
        default:
            break;
        }
    }

    return QObject::eventFilter(obj, ev);
}
