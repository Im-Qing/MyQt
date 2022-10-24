#include "MModelTest.h"

MModelTest::MModelTest(QObject *parent) : QObject (parent)
{
}

MGLModel *MModelTest::getModel()
{
    MGLModel *pModel = nullptr;

    m_modelId = 1;
    switch (m_modelId)
    {
    case 1:
        pModel = new MModelShape(m_modelId, this);
        break;
    }

    return pModel;
}

MModelShape::MModelShape(int id, QObject *parent) : MGLModel(id, parent)
{
    static float vertices[] = {
        // 位置              // 颜色
         0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    // 右下
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // 顶点
        -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f    // 左上角
    };
    static unsigned int indices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    setVertices(vertices, sizeof(vertices));
    setIndexs(indices, sizeof(indices));
    addShaderFromSourceFile(QOpenGLShader::Vertex, "://Res/GLSL/vertex.glsl");
    addShaderFromSourceFile(QOpenGLShader::Fragment, "://Res/GLSL/fragment.glsl");
    addAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 6*sizeof(float));
    addAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), 3, 6*sizeof(float));
}

void MModelShape::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

