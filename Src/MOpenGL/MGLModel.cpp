#include "MGLModel.h"
#include "MGLScene.h"
#include "MGLWidget.h"

using namespace NS_MOpenGL;

MGLModel::MGLModel(int id, QObject *parent) : QObject(parent)
  , m_id(id)
  , m_vbo(QOpenGLBuffer::VertexBuffer)
  , m_ebo(QOpenGLBuffer::IndexBuffer)
{

}

void MGLModel::setName(const QString &name)
{
    m_name = name;
}

void MGLModel::setVertices(float* vertices, int nSize)
{
    m_pVertexBuffer = vertices;
    m_vertexBufferSize = nSize;
}

void MGLModel::setIndexs(unsigned int* indexs, int nSize)
{
    m_pIndexBuffer = indexs;
    m_indexBufferSize = nSize;
}

int MGLModel::getId()
{
    return m_id;
}

QString MGLModel::getName()
{
    return m_name;
}

MGLScene *MGLModel::getScene()
{
    return m_pScene;
}

void MGLModel::addAttributeBuffer(const QString& name, GLenum type, int offset, int tupleSize, int stride)
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

void MGLModel::initialize()
{
    MGLWidget* pGLWidget = m_pScene->getGLWidget();
    if(!m_isInitializeFinished && pGLWidget && pGLWidget->context())
    {
        m_vao.create();
        m_vbo.create();
        m_ebo.create();
        m_shaderProgram.create();

        m_vao.bind();
        m_vbo.bind();
        m_ebo.bind();
        m_shaderProgram.bind();

        //顶点缓冲数据
        if(!m_pVertexBuffer)
        {
            qDebug()<<"vertexBuffer is nullptr";
            return;
        }
        m_vbo.allocate(m_pVertexBuffer, m_vertexBufferSize);
        //索引缓冲数据
        if(m_pIndexBuffer)
        {
            //m_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
            m_ebo.allocate(m_pIndexBuffer, m_indexBufferSize);
        }
        else
        {
            qDebug()<<"indexBuffer is nullptr";
        }
        //着色器程序文件链接
        {
            QMapIterator<QOpenGLShader::ShaderType, QString> iter(m_mapShaderTypeToShaderFile);
            while (iter.hasNext())
            {
                iter.next();
                m_shaderProgram.addShaderFromSourceFile(iter.key(), iter.value());
            }
            m_shaderProgram.link();
        }
        //顶点数据规则
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
        }

        m_shaderProgram.release();
        m_ebo.release();
        m_vbo.release();
        m_vao.release();

        initializeOpenGLFunctions();
        m_isInitializeFinished = true;
    }
    else
    {
        qDebug() << "m_isInitializeFinished = " << m_isInitializeFinished;
        qDebug() << "pGLWidget = " << pGLWidget;
    }

    qDebug() << QString("initialize model res = %1, modelId = %2").arg(m_isInitializeFinished).arg(m_id);
}

void MGLModel::paintGL(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    if(m_isInitializeFinished)
    {
        m_vao.bind();
        m_shaderProgram.bind();
        paint(viewMat, projectionMat, cameraPos);
        m_shaderProgram.release();
        m_vao.release();
    }
    else
    {
        qDebug() << QString("paint model fail, m_isInitializeFinished = %1, modelId = %2").arg(m_isInitializeFinished).arg(getId());
    }
}

void MGLModel::setScene(MGLScene* scene)
{
    m_pScene = scene;
}




