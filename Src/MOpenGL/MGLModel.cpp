#include "MGLModel.h"
#include "MGLScene.h"

using namespace NS_MOpenGL;

MGLModel::MGLModel(const QString& name, QObject *parent) : QObject(parent)
  ,m_name(name)
{

}

void MGLModel::initialize()
{
    initializeOpenGLFunctions();

    m_vao.create();
    m_vbo.create();
    m_shaderProgram.create();

    m_vao.bind();
    m_vbo.bind();
    m_shaderProgram.bind();

    //顶点数据
    m_vbo.allocate(m_pVertexBuffer, m_vertexBufferSize);

    //着色器加载链接
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
    m_shaderProgram.link();

    //着色器解析规则
    m_shaderProgram.setAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 3*sizeof(float));
    m_shaderProgram.enableAttributeArray("vPos");
//    m_shaderProgram.setAttributeBuffer("vNormal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
//    m_shaderProgram.enableAttributeArray("vNormal");
//    m_shaderProgram.setAttributeBuffer("vTextureCoords", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
//    m_shaderProgram.enableAttributeArray("vTextureCoords");

    m_shaderProgram.release();
    m_vbo.release();
    m_vao.release();
}

void MGLModel::paint(QMatrix4x4 modelMat, QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    m_vao.bind();
    m_shaderProgram.bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_shaderProgram.release();
    m_vao.release();
}

void MGLModel::setVertices(float *vertices, int nSize)
{
    m_pVertexBuffer = vertices;
    m_vertexBufferSize = nSize;
}

void MGLModel::setAttributeBuffer(const QString& name, GLenum type, int offset, int tupleSize, int stride)
{
    MGLAttributeBufferPara attributeBufferPara;
    attributeBufferPara.name = name;
    attributeBufferPara.type = type;
    attributeBufferPara.offset = offset;
    attributeBufferPara.tupleSize = tupleSize;
    attributeBufferPara.stride = stride;
    m_mapNameToAttributeBufferPara[name] = attributeBufferPara;
}

bool MGLModel::addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString &fileName)
{
    m_mapShaderTypeToShaderFile[type] = fileName;
}

QString MGLModel::getName()
{
    return m_name;
}




