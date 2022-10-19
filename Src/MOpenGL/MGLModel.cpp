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
    {
        QMapIterator<QOpenGLShader::ShaderType, QString> iter(m_mapShaderTypeToShaderFile);
        while (iter.hasNext())
        {
            iter.next();
            m_shaderProgram.addShaderFromSourceFile(iter.key(), iter.value());
        }
        m_shaderProgram.link();
    }
    //着色器解析规则
    {
        QMapIterator<QString, MGLAttributeBufferPara> iter(m_mapNameToAttributeBufferPara);
        while (iter.hasNext())
        {
            iter.next();
            QString name = iter.key();
            MGLAttributeBufferPara para = iter.value();
            m_shaderProgram.setAttributeBuffer(name.toStdString().c_str(), para.type, para.offset, para.tupleSize, para.stride);
            m_shaderProgram.enableAttributeArray(name.toStdString().c_str());
        }
        m_shaderProgram.link();
    }

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

void MGLModel::addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString &fileName)
{
    m_mapShaderTypeToShaderFile[type] = fileName;
}

QString MGLModel::getName()
{
    return m_name;
}




