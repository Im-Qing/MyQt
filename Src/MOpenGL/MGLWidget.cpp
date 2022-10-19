#include "MGLWidget.h"

using namespace NS_MOpenGL;

float normalVertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

MGLWidget::MGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLExtraFunctions()
{
    setFocusPolicy(Qt::ClickFocus);

    m_pGLCamera = new MGLCamera(this);
    connect(m_pGLCamera, &MGLCamera::sign_projectionMatChanged, this, &MGLWidget::slot_cameraProjectionChanged, Qt::QueuedConnection);
    connect(m_pGLCamera, &MGLCamera::sign_viewMatChanged, this, &MGLWidget::slot_cameraViewMatChanged, Qt::QueuedConnection);

    m_pObject = new MGLModel("object", this);
    m_pLight = new MGLModel("lignt", this);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(1000);
    connect(m_pTimer, &QTimer::timeout, this, &MGLWidget::slot_timeout);
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

    m_pObject->setVertices(vertices, sizeof(vertices));
//    m_pObject->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
//    m_pObject->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
//    m_pObject->setAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 3*sizeof(float));
    m_pObject->initialize();

//    m_pLight->setVertices(normalVertices, sizeof(normalVertices));
//    m_pObject->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
//    m_pObject->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
//    m_pLight->initialize();
}

void MGLWidget::paintGL()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    float angle = 15.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(-0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1, 1, 1));
    m_pObject->paint(MOpenGL::glmMat4ToQMat4(model), m_pGLCamera->getViewMat(), m_pGLCamera->getProjectionMat(), m_pGLCamera->getCameraPos());

//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(5.f, -0.2f, 1.0f));
//    angle = 0.0f;
//    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//    model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
//    m_pLight->paint(glmMat4ToQMat4(model), m_pGLCamera->getViewMat(), m_pGLCamera->getProjectionMat(), m_pGLCamera->getCameraPos(), false);
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
