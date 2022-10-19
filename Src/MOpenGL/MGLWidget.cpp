#include "MGLWidget.h"
#include "MGLScene.h"
#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLWidget::MGLWidget(MGLScene* scene, QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLExtraFunctions()
    ,m_pScene(scene)
{
    setFocusPolicy(Qt::ClickFocus);

    m_pGLCamera = new MGLCamera(this);
    connect(m_pGLCamera, &MGLCamera::sign_projectionMatChanged, this, &MGLWidget::slot_cameraProjectionChanged, Qt::QueuedConnection);
    connect(m_pGLCamera, &MGLCamera::sign_viewMatChanged, this, &MGLWidget::slot_cameraViewMatChanged, Qt::QueuedConnection);
}

MGLWidget::~MGLWidget()
{

}

void MGLWidget::slot_timeout()
{
    repaint();
}

void MGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void MGLWidget::paintGL()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    float angle = 15.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(-0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1, 1, 1));

    //渲染模型
    QList<MGLModel *> modelList = m_pScene->getAllModel();
    for(auto pModel : modelList)
    {
        pModel->paint(MOpenGL::glmMat4ToQMat4(model), m_pGLCamera->getViewMat(), m_pGLCamera->getProjectionMat(), m_pGLCamera->getCameraPos());
    }
}

void MGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  //这里是显示窗体，上面有截取，这里才有显示。不然窗口不会显示任何内容
}

void MGLWidget::slot_cameraProjectionChanged(QMatrix4x4 projectionMat)
{
    repaint();
}

void MGLWidget::slot_cameraViewMatChanged(QMatrix4x4 viewMat)
{
    repaint();
}
