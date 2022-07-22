#include "MGLWidget.h"

using namespace NS_MOpenGL;

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

MGLWidget::MGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLExtraFunctions()
    , m_texture(QOpenGLTexture::Target2D)
{
    setFocusPolicy(Qt::ClickFocus);

    m_pGLCamera = new MGLCamera(this);
    connect(m_pGLCamera, &MGLCamera::sign_projectionMatChanged, this, &MGLWidget::slot_cameraProjectionChanged, Qt::QueuedConnection);
    connect(m_pGLCamera, &MGLCamera::sign_viewMatChanged, this, &MGLWidget::slot_cameraViewMatChanged, Qt::QueuedConnection);

    trans = glm::mat4(1.0f);      //单位矩阵
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(1, 1, 1));

    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    m_pTimer = new QTimer(this);
//    m_pTimer->start(1000);
    connect(m_pTimer, &QTimer::timeout, this, &MGLWidget::slot_timeout);
}

MGLWidget::~MGLWidget()
{

}

void MGLWidget::slot_timeout()
{

}

void MGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0.5, 0.7, 1);

    m_vao.create();
    m_vbo.create();
    m_shaderProgram.create();

    m_vao.bind();
    m_vbo.bind();
    m_shaderProgram.bind();

    //顶点数据
    m_vbo.allocate(vertices, sizeof(vertices));

    //着色器加载链接
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
    m_shaderProgram.link();

    //着色器解析规则
    m_shaderProgram.setAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vPos");
    m_shaderProgram.setAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vColor");
    m_shaderProgram.setAttributeBuffer("vTexture", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vTexture");

    //纹理
    m_texture.create();                       //向GPU申请创建纹理对象
    m_texture.setData(QImage(":/Img/Res/Img/onetwo.jpg").mirrored());     //从QImage导入像素数据（内部会自动设置格式和分配存储）
    m_shaderProgram.setUniformValue("uTexture", 0);

    m_shaderProgram.release();
    m_vbo.release();
    m_vao.release();
}

void MGLWidget::paintGL()
{
    m_vao.bind();
    m_shaderProgram.bind();
    m_texture.bind(0);

    m_shaderProgram.setUniformValue("transform", glmMat4ToQMat4(trans));
    m_shaderProgram.setUniformValue("model", glmMat4ToQMat4(model));
    m_shaderProgram.setUniformValue("view", m_pGLCamera->getViewMat());
    m_shaderProgram.setUniformValue("projection", m_pGLCamera->getProjectionMat());

    //物体
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    float angle = -30.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(-1.0f, 1.0f, 0.0f));
    m_shaderProgram.setUniformValue("model", glmMat4ToQMat4(model));
    drawBox(model);
    //光源
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(5.0f, 2.0f, -3.5f));
    angle = 0.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
    m_shaderProgram.setUniformValue("model", glmMat4ToQMat4(model));
    drawBox(model);

//    draw10Box();

    m_texture.release();
    m_shaderProgram.release();
    m_vao.release();
}

void MGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);  //这里是显示窗体，上面有截取，这里才有显示。不然窗口不会显示任何内容
}

void MGLWidget::drawBox(glm::mat4 modelMat)
{
    m_shaderProgram.setUniformValue("model", glmMat4ToQMat4(modelMat));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MGLWidget::draw10Box()
{
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f); ;
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_shaderProgram.setUniformValue("model", glmMat4ToQMat4(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

QMatrix4x4 MGLWidget::glmMat4ToQMat4(glm::mat4 mat4)
{
    QMatrix4x4 matRes;

    for(int c = 0; c < 4; c++)
    {
        QVector4D row;
        row.setX(mat4[0][c]);
        row.setY(mat4[1][c]);
        row.setZ(mat4[2][c]);
        row.setW(mat4[3][c]);
        matRes.setRow(c, row);
    }

    return matRes;
}

void MGLWidget::slot_cameraProjectionChanged(QMatrix4x4 projectionMat)
{
    repaint();
}

void MGLWidget::slot_cameraViewMatChanged(QMatrix4x4 viewMat)
{
    repaint();
}
