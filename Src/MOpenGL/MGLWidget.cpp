#include "MGLWidget.h"
#include "MGLScene.h"
#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLWidget::MGLWidget(MGLScene* scene, QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLExtraFunctions()
    ,m_pScene(scene)
{
    setFocusPolicy(Qt::ClickFocus);

    m_pScene->setGLWidget(this);

    m_pGLCamera = new MGLCamera(this);
    connect(m_pGLCamera, &MGLCamera::sign_projectionMatChanged, this, &MGLWidget::slot_cameraProjectionChanged, Qt::QueuedConnection);
    connect(m_pGLCamera, &MGLCamera::sign_viewMatChanged, this, &MGLWidget::slot_cameraViewMatChanged, Qt::QueuedConnection);
}

MGLWidget::~MGLWidget()
{

}

void MGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(51.0f/255, 51.0f/255, 99.0f/255, 1.0f);

    //初始化已添加的模型
    QList<MGLModel *> modelList = m_pScene->getAllModel();
    for(auto pModel : modelList)
    {
        pModel->initialize();
    }
}

void MGLWidget::paintGL()
{
    //渲染模型
    QList<MGLModel *> modelList = m_pScene->getAllModel();
    for(auto pModel : modelList)
    {
        pModel->paintGL(m_pGLCamera->getViewMat(), m_pGLCamera->getProjectionMat(), m_pGLCamera->getCameraPos());
    }
}

void MGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  //这里是显示窗体，上面有截取，这里才有显示。不然窗口不会显示任何内容
    //通知模型窗口尺寸发生变化
    QList<MGLModel *> modelList = m_pScene->getAllModel();
    for(auto pModel : modelList)
    {
        pModel->resizeGL(w, h);
    }
}

void MGLWidget::slot_cameraProjectionChanged(QMatrix4x4 projectionMat)
{
    repaint();
}

void MGLWidget::slot_cameraViewMatChanged(QMatrix4x4 viewMat)
{
    repaint();
}
