#include "MGLModel.h"
#include "MGLScene.h"
#include "MGLWidget.h"

using namespace NS_MOpenGL;

MGLModel::MGLModel(int id, QObject *parent) : QObject(parent)
  , m_id(id)
{

}

MGLModel::~MGLModel()
{

}

void MGLModel::setName(const QString &name)
{
    m_name = name;
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

void MGLModel::addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString &fileName)
{
    m_mapKeyToShaderTypeToShaderFile[m_currentKey][type] = fileName;
}

void MGLModel::addVertices(float* vertices, int nSize)
{
    m_mapKeyToVertexBuffer[m_currentKey] = vertices;
    m_mapKeyToVertexBufferSize[m_currentKey] = nSize;
}

void MGLModel::addAttributeBuffer(const QString& name, GLenum type, int offset, int tupleSize, int stride)
{
    MGLAttributeBufferPara attributeBufferPara;
    attributeBufferPara.name = name;
    attributeBufferPara.type = type;
    attributeBufferPara.offset = offset;
    attributeBufferPara.tupleSize = tupleSize;
    attributeBufferPara.stride = stride;
    m_mapKeyToNameToAttributeBufferPara[m_currentKey][name] = attributeBufferPara;
}

void MGLModel::addIndexs(unsigned int* indexs, int nSize)
{
    m_mapKeyToIndexBuffer[m_currentKey] = indexs;
    m_mapKeyToIndexBufferSize[m_currentKey] = nSize;
}

void MGLModel::addTexture2DFile(int index, const QString& variableName, const QString &fileName)
{
    m_mapKeyToIndexToVariableName[m_currentKey][index] = variableName;
    m_mapKeyToIndexToTextureFile[m_currentKey][index] = fileName;
}

void MGLModel::addSkyBoxTextureFile(int index, const QString &variableName, const QStringList &fileNameList)
{
    m_mapKeyToIndexToVariableName[m_currentKey][index] = variableName;
    m_mapKeyToIndexToSkyBoxTextureFile[m_currentKey][index] = fileNameList;

    QOpenGLTexture *pTexture=new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    QImage posX = QImage(fileNameList[0]).convertToFormat(QImage::Format_RGB888); //Right，默认读取的纹理为32位RGB，不符合CubeMap的要求，必须转为24位RGB。
    QImage negX = QImage(fileNameList[1]).convertToFormat(QImage::Format_RGB888); //Left
    QImage posY = QImage(fileNameList[2]).convertToFormat(QImage::Format_RGB888); //Top
    QImage negY = QImage(fileNameList[3]).convertToFormat(QImage::Format_RGB888); //Bottom
    QImage posZ = QImage(fileNameList[4]).convertToFormat(QImage::Format_RGB888); //Front
    QImage negZ = QImage(fileNameList[5]).convertToFormat(QImage::Format_RGB888); //Back
    pTexture->setSize(posX.width(),posX.width(),posX.depth());
    pTexture->setFormat(QOpenGLTexture::RGBFormat);
    pTexture->allocateStorage(QOpenGLTexture::RGB,QOpenGLTexture::UInt8);
    //不明白为什么这几个值跟文档的不一样，怎么就差了2，文档斜的差1的
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posX.bits());
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posY.bits());
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)posZ.bits());
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negX.bits());
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negY.bits());
    pTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void*)negZ.bits());
    pTexture->setMinificationFilter(QOpenGLTexture::Linear);   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    pTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    pTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    pTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // pTexture->setWrapMode(QOpenGLTexture::DirectionR, QOpenGLTexture::ClampToEdge);
    m_mapKeyToIndexToTextureData[m_currentKey][index] = pTexture;
}

void MGLModel::resizeGL(int w, int h)
{
    delete m_pFbo;
    m_pFbo = new QOpenGLFramebufferObject(w,h,QOpenGLFramebufferObject::Depth);
}

QOpenGLShaderProgram *MGLModel::getShaderProgram(int key)
{
    if(m_mapKeyToShaderProgram.contains(key))
    {
        return m_mapKeyToShaderProgram[key];
    }
    return nullptr;
}

void MGLModel::bind(int key)
{
    m_mapKeyToVao[key]->bind();
    m_mapKeyToShaderProgram[key]->bind();
    //纹理
    QMapIterator<int, QString> iter(m_mapKeyToIndexToVariableName[key]);
    while (iter.hasNext())
    {
        iter.next();
        int index = iter.key();
        m_mapKeyToShaderProgram[key]->setUniformValue(m_mapKeyToIndexToVariableName[key][index].toStdString().c_str(), index);
        m_mapKeyToIndexToTextureData[key][index]->bind(index);
    }
}

void MGLModel::release(int key)
{
    m_mapKeyToShaderProgram[key]->release();
    m_mapKeyToVao[key]->release();
    //纹理
    QMapIterator<int, QOpenGLTexture*> iter(m_mapKeyToIndexToTextureData[key]);
    while (iter.hasNext())
    {
        iter.next();
        iter.value()->release();
    }
}

void MGLModel::bindFbo(int key)
{
    //m_pFbo->takeTexture();
    m_pFbo->bind();
}

void MGLModel::releaseFbo(int key)
{
    m_pFbo->release();
}

void MGLModel::bindFboTexture(int shaderProgramkey, const QString &variableName, int key)
{
    if(m_mapKeyToShaderProgram.contains(shaderProgramkey))
    {
        m_mapKeyToShaderProgram[key]->setUniformValue(variableName.toStdString().c_str(), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_pFbo->texture());
    }
}

void MGLModel::initialize()
{
    MGLWidget* pGLWidget = m_pScene->getGLWidget();
    if(!m_isInitializeFinished && pGLWidget && pGLWidget->context())
    {
        //初始化着色器、顶点、纹理等数据
        QMapIterator<int, QMap<QOpenGLShader::ShaderType, QString>> iter(m_mapKeyToShaderTypeToShaderFile);
        while (iter.hasNext())
        {
            iter.next();
            int key = iter.key();
            //着色器程序链接
            {
                m_mapKeyToShaderProgram[key] = new QOpenGLShaderProgram(this);
                m_mapKeyToShaderProgram[key]->create();
                m_mapKeyToShaderProgram[key]->bind();
                QMapIterator<QOpenGLShader::ShaderType, QString> iter1(iter.value());
                while (iter1.hasNext())
                {
                    iter1.next();
                    m_mapKeyToShaderProgram[key]->addShaderFromSourceFile(iter1.key(), iter1.value());
                }
                m_mapKeyToShaderProgram[key]->link();
            }
            //顶点缓冲数据和索引缓冲数据
            {
                //vao
                m_mapKeyToVao[key] = new QOpenGLVertexArrayObject(this);
                m_mapKeyToVao[key]->create();
                m_mapKeyToVao[key]->bind();
                //vbo
                m_mapKeyToVbo[key] = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
                m_mapKeyToVbo[key].create();
                m_mapKeyToVbo[key].bind();
                if(!m_mapKeyToVertexBuffer[key])
                {
                    qDebug()<<"vertexBuffer is nullptr, key = " << key;
                    continue;
                }
                m_mapKeyToVbo[key].allocate(m_mapKeyToVertexBuffer[key], m_mapKeyToVertexBufferSize[key]);
                //ebo
                if(m_mapKeyToIndexBuffer.contains(key) && m_mapKeyToIndexBuffer[key])
                {
                    m_mapKeyToEbo[key] = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
                    m_mapKeyToEbo[key].create();
                    m_mapKeyToEbo[key].bind();
                    m_mapKeyToEbo[key].setUsagePattern(QOpenGLBuffer::StaticDraw);
                    m_mapKeyToEbo[key].allocate(m_mapKeyToIndexBuffer[key], m_mapKeyToIndexBufferSize[key]);
                }
            }
            //顶点数据规则
            {
                QMapIterator<QString, MGLAttributeBufferPara> iter1(m_mapKeyToNameToAttributeBufferPara[key]);
                while (iter1.hasNext())
                {
                    iter1.next();
                    QString name = iter1.key();
                    MGLAttributeBufferPara para = iter1.value();
                    m_mapKeyToShaderProgram[key]->setAttributeBuffer(name.toStdString().c_str(), para.type, para.offset, para.tupleSize, para.stride);
                    m_mapKeyToShaderProgram[key]->enableAttributeArray(name.toStdString().c_str());
                }
            }
            //帧缓冲
            {
                m_pFbo = new QOpenGLFramebufferObject(pGLWidget->size(),QOpenGLFramebufferObject::Depth);
            }
            //纹理数据
            if(m_mapKeyToIndexToTextureFile.contains(key))
            {
                QMapIterator<int, QString> iter1(m_mapKeyToIndexToTextureFile[key]);
                while (iter1.hasNext())
                {
                    iter1.next();
                    int index = iter1.key();
                    QString textureFile = iter1.value();
                    m_mapKeyToIndexToTextureData[key][index] = new QOpenGLTexture(QImage(textureFile).mirrored());
                }
            }
            //release
            {
                m_mapKeyToVbo[key].release();
                m_mapKeyToVao[key]->release();
                m_mapKeyToShaderProgram[key]->release();
            }
        }
        //初始化gl函数库
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
        paint(viewMat, projectionMat, cameraPos);
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





