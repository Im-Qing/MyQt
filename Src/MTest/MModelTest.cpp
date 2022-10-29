﻿#include "MModelTest.h"

MModelTest::MModelTest(QObject *parent) : QObject (parent)
{
}

MGLModel *MModelTest::getModel()
{
    MGLModel *pModel = nullptr;

    m_modelId = 6;
    switch (m_modelId)
    {
    case 1:
        pModel = new MModelShape(m_modelId, this);
        break;
    case 2:
        pModel = new MModelTexture(m_modelId, this);
        break;
    case 3:
        pModel = new MModelTransform(m_modelId, this);
        break;
    case 4:
        pModel = new MModelStencilTest(m_modelId, this);
        break;
    case 5:
        pModel = new MModelBlend(m_modelId, this);
        break;
    case 6:
        pModel = new MModelFBO(m_modelId, this);
        break;
    }

    return pModel;
}

MModelShape::MModelShape(int id, QObject *parent) : MGLModel(id, parent)
{
    //正方体
    static float vertices[] =
    {
         //位置              颜色
        -0.5, -0.5, -0.5,   1.0f, 0.0f, 0.0f,
        -0.5, -0.5,  0.5,   1.0f,  242.f/255,  204.f/255,
         0.5, -0.5,  0.5,   0.0f, 0.0f, 1.0f,
         0.5, -0.5, -0.5,   1.0f, 1.0f, 0.0f,
        -0.5,  0.5, -0.5,   0.0f, 0.0f, 1.0f,
        -0.5,  0.5,  0.5,   1.0f,  242.f/255,  204.f/255,
         0.5,  0.5,  0.5,   1.0f, 0.0f, 0.0f,
         0.5,  0.5, -0.5,   1.0f,  242.f/255,  204.f/255
    };
    static unsigned int indices[] =
    {
        0,2,1,
        0,2,3,
        2,5,1,
        2,5,6,
        2,7,3,
        2,7,6,
        0,5,1,
        0,5,4,
        4,6,5,
        4,6,7,
        0,7,4,
        0,7,3
    };
    addVertices(vertices, sizeof(vertices));
    addIndexs(indices, sizeof(indices));
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/vertex.glsl");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fragment.glsl");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 6*sizeof(float));
    addAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 6*sizeof(float));
}

void MModelShape::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    int key = 0;
    bind(key);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);      //禁用深度缓冲的写入

    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);

    glm::mat4 modelMat = glm::mat4(1.0f); ;
    pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelMat));
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    pShaderProgram->setUniformValue("uUseTexture", false);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    release(key);
}


MModelTexture::MModelTexture(int id, QObject *parent): MGLModel(id, parent)
{
    static float vertices[] = {
        //位置                颜色                纹理
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f
    };
    addVertices(vertices, sizeof(vertices));
    addTexture2DFile(0, "uTexture1", "://Res/Img/onetwo.jpg");
    addTexture2DFile(1, "uTexture2", "://Res/Img/container2.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/vertex.glsl");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fragment.glsl");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
}

void MModelTexture::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    int key = 0;
    bind(key);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);      //禁用深度缓冲的写入

    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);

    glm::mat4 modelMat = glm::mat4(1.0f);
    pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelMat));
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    pShaderProgram->setUniformValue("uUseTexture", true);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    release(key);
}


MModelTransform::MModelTransform(int id, QObject *parent): MGLModel(id, parent)
{
    static float vertices[] = {
        //位置                颜色                纹理
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  242.f/255,  204.f/255,  0.0f, 1.0f
    };
    addVertices(vertices, sizeof(vertices));
    addTexture2DFile(0, "uTexture1", "://Res/Img/bubu.jpg");
    addTexture2DFile(1, "uTexture2", "://Res/Img/container2.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/vertex.glsl");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fragment.glsl");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
}

void MModelTransform::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    int key = 0;
    bind(key);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glDepthMask(GL_FALSE);      //禁用深度缓冲的写入

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

    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);

    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    pShaderProgram->setUniformValue("uUseTexture", true);

    for(int i = 0; i<10; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, cubePositions[i]);                   //平移
        float angle = 20.0f * i;
        modelTranMat = glm::rotate(modelTranMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));    //旋转(逆时针为正)
        modelTranMat = glm::scale(modelTranMat, glm::vec3(1.0, 1.0, 1.0));                          //缩放
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    release(key);
}


MModelStencilTest::MModelStencilTest(int id, QObject *parent): MGLModel(id, parent)
{
    static float vertices[] = {
        //位置                 颜色                         纹理
        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 242.f/255, 204.f/255,  0.0f, 1.0f
    };
    addVertices(vertices, sizeof(vertices));
    addTexture2DFile(0, "uTexture1", "://Res/Img/onetwo.jpg");
    addTexture2DFile(1, "uTexture2", "://Res/Img/container2.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/vertex.glsl");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fragment.glsl");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
}

void MModelStencilTest::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    int key = 0;
    bind(key);
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
    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);

    //模板测试
    glEnable(GL_STENCIL_TEST);
    //深度测试
    glEnable(GL_DEPTH_TEST);
    //清除缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);

    //绘制正常大小的箱子，将箱子的片段的模板值更新为1
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    pShaderProgram->setUniformValue("uUseTexture", true);
    for(int i = 0; i<10; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, cubePositions[i]);                   //平移
        float angle = 20.0f * i;
        modelTranMat = glm::rotate(modelTranMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));    //旋转(逆时针为正)
        modelTranMat = glm::scale(modelTranMat, glm::vec3(1.0, 1.0, 1.0));                          //缩放
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //绘制放大的箱子，在模板值为0处绘制，形成箱子边框效果
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    pShaderProgram->setUniformValue("uUseTexture", false);
    for(int i = 0; i<10; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, cubePositions[i]);                   //平移
        float angle = 20.0f * i;
        modelTranMat = glm::rotate(modelTranMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));    //旋转(逆时针为正)
        modelTranMat = glm::scale(modelTranMat, glm::vec3(1.05, 1.05, 1.05));                          //缩放
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
    release(key);
}


MModelBlend::MModelBlend(int id, QObject *parent): MGLModel(id, parent)
{
    static float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    static float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    static float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };
    //绘制箱子需要的数据
    setCurrentKey(0);
    addVertices(cubeVertices, sizeof(cubeVertices));
    addTexture2DFile(0, "uTexture1", "://Res/Img/onetwo.jpg");
    addTexture2DFile(1, "uTexture2", "://Res/Img/container2.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/blend.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/blend.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 5*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
    //绘制地板需要的数据
    setCurrentKey(1);
    addVertices(planeVertices, sizeof(planeVertices));
    addTexture2DFile(2, "uTexture1", "://Res/Img/metal.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/blend.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/blend.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 5*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
    //绘制窗户需要的数据
    setCurrentKey(2);
    addVertices(transparentVertices, sizeof(transparentVertices));
    addTexture2DFile(3, "uTexture1", "://Res/Img/blending_transparent_window.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/blend.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/blend.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 5*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
}

void MModelBlend::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    glm::vec3 cubePositions[] = {
      glm::vec3( -1.0f, 0.0f, -1.0f),
      glm::vec3( 2.0f, 0.0f, 0.0f)
    };
    std::vector<glm::vec3> windows
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3( 0.5f, 0.0f, -0.6f)
    };

    //深度测试
    glEnable(GL_DEPTH_TEST);
    //开启混合
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //清除缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //绘制箱子
    int key = 0;
    bind(key);
    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);
    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    for(int i = 0; i<2; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, cubePositions[i]);                   //平移
//        float angle = 20.0f * i;
//        modelTranMat = glm::rotate(modelTranMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));    //旋转(逆时针为正)
//        modelTranMat = glm::scale(modelTranMat, glm::vec3(1.0, 1.0, 1.0));                          //缩放
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    release(key);

    //绘制地板
    key = 1;
    bind(key);
    pShaderProgram = getShaderProgram(key);
    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    //变换矩阵，顺序为：缩放->旋转->位移
    glm::mat4 modelTranMat = glm::mat4(1.0f);
    pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    release(key);

    //绘制窗户
    key = 2;
    bind(key);
    pShaderProgram = getShaderProgram(key);
    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    for(int i = 0; i<5; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, windows[i]);                   //平移
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    release(key);
}


MModelFBO::MModelFBO(int id, QObject *parent): MGLModel(id, parent)
{
    static float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    static float planeVertices[] = {
        // positions          // texture Coords
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    static float quadVertices[] = {
        // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };
    static float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    static QStringList skyBoxTexturePaths{
        "://Res/Img/skybox/right.jpg",
        "://Res/Img/skybox/left.jpg",
        "://Res/Img/skybox/top.jpg",
        "://Res/Img/skybox/bottom.jpg",
        "://Res/Img/skybox/front.jpg",
        "://Res/Img/skybox/back.jpg",
    };
    //绘制箱子需要的数据
    setCurrentKey(0);
    addVertices(cubeVertices, sizeof(cubeVertices));
    addTexture2DFile(0, "uTexture1", "://Res/Img/onetwo.jpg");
    addTexture2DFile(1, "uTexture2", "://Res/Img/container2.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/blend.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/blend.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 5*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
    //绘制地板需要的数据
    setCurrentKey(1);
    addVertices(planeVertices, sizeof(planeVertices));
    addTexture2DFile(2, "uTexture1", "://Res/Img/metal.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/blend.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/blend.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 5*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 3*sizeof(float), 2, 5*sizeof(float));
    //绘制四边形需要的数据
    setCurrentKey(2);
    addVertices(quadVertices, sizeof(quadVertices));
    addTexture2DFile(3, "uTexture1", "://Res/Img/blending_transparent_window.png");
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/fbo.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fbo.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 2, 4*sizeof(float));
    addAttributeBuffer("vTexCoord", GL_FLOAT, 2*sizeof(float), 2, 4*sizeof(float));
    //绘制天空盒需要的数据
    setCurrentKey(3);
    addVertices(skyboxVertices, sizeof(skyboxVertices));
    addSkyBoxTextureFile(3, "uTexture1", skyBoxTexturePaths);
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/skybox.vert");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/skybox.frag");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 3*sizeof(float));
}

void MModelFBO::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    glm::vec3 cubePositions[] = {
      glm::vec3( -1.0f, 0.0f, -1.0f),
      glm::vec3( 2.0f, 0.0f, 0.0f)
    };
    std::vector<glm::vec3> windows
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3( 1.5f, 0.0f, 0.51f),
        glm::vec3( 0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3( 0.5f, 0.0f, -0.6f)
    };

    //深度测试
    glEnable(GL_DEPTH_TEST);
    //清除缓冲
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //绘制箱子
    int key = 0;
    bind(key);
    QOpenGLShaderProgram* pShaderProgram = getShaderProgram(key);
    //设置uniform变量值
    pShaderProgram->setUniformValue("uViewMat", viewMat);
    pShaderProgram->setUniformValue("uProjectionMat", projectionMat);
    for(int i = 0; i<2; i++)
    {
        //变换矩阵，顺序为：缩放->旋转->位移
        glm::mat4 modelTranMat = glm::mat4(1.0f);
        modelTranMat = glm::translate(modelTranMat, cubePositions[i]);                   //平移
//        float angle = 20.0f * i;
//        modelTranMat = glm::rotate(modelTranMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));    //旋转(逆时针为正)
//        modelTranMat = glm::scale(modelTranMat, glm::vec3(1.0, 1.0, 1.0));                          //缩放
        pShaderProgram->setUniformValue("uModelMat", MOpenGL::glmMat4ToQMat4(modelTranMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    release(key);
}
