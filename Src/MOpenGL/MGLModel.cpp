#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLModel::MGLModel(QObject *parent) : QObject(parent)
{

}

void MGLModel::setVertices(const QVector<MGLVertex> &vertices)
{
    m_vertices = vertices;
    if(vertices.length()<0)
    {
        return;
    }
    //顶点分量值
    if(vertices[0].pos != ILLEGALVector3D)
        m_vertexWeightLen.setX(3);
    if(vertices[0].color != ILLEGALVector3D)
        m_vertexWeightLen.setY(3);
    if(vertices[0].texture != ILLEGALVector2D)
        m_vertexWeightLen.setZ(3);
    m_vertexFloatCount = m_vertexWeightLen.x() + m_vertexWeightLen.y() + m_vertexWeightLen.z();
    //转成float*
    if (m_pVertexBuffer)
        delete[] m_pVertexBuffer;
    m_pVertexBuffer = new float[m_vertices.count() * m_vertexFloatCount];
    int offset = 0;
    for (auto &vertex : m_vertices)
    {
        //位置顶点
        if(m_vertexWeightLen.x() != 0)      //分量不为0则赋值
        {
            m_pVertexBuffer[offset] = vertex.pos.x(); offset++;
            m_pVertexBuffer[offset] = vertex.pos.y(); offset++;
            m_pVertexBuffer[offset] = vertex.pos.z(); offset++;
        }
        //颜色顶点
        if(m_vertexWeightLen.y() != 0)      //分量不为0则赋值
        {
            m_pVertexBuffer[offset] = vertex.color.x(); offset++;
            m_pVertexBuffer[offset] = vertex.color.y(); offset++;
            m_pVertexBuffer[offset] = vertex.color.z(); offset++;
        }
        //纹理顶点
        if(m_vertexWeightLen.z() != 0)      //分量不为0则赋值
        {
            m_pVertexBuffer[offset] = vertex.texture.x(); offset++;
            m_pVertexBuffer[offset] = vertex.texture.y(); offset++;
        }
    }
}

void MGLModel::setTexture(const QString& imgSrc, int index)
{
    m_textures[index] = QOpenGLTexture::Target2D;
    m_textures[index].setData(QImage(imgSrc).mirrored());

    m_textures[index] = texture;
}

void MGLModel::setPos(const QVector3D &pos)
{
    m_pos = pos;
}

void MGLModel::setScale(const QVector3D &scale)
{
    m_scale = scale;
}

void MGLModel::setRotate(const QVector3D &rotate)
{
    m_rotate = rotate;
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
    m_vbo.allocate(m_pVertexBuffer, sizeof(m_pVertexBuffer));

    //着色器加载链接
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
    m_shaderProgram.link();

    //着色器解析规则
    m_shaderProgram.setAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), m_vertexWeightLen.x(), m_vertexFloatCount * sizeof(float));
    m_shaderProgram.enableAttributeArray("vPos");
    m_shaderProgram.setAttributeBuffer("vColor", GL_FLOAT, 3*sizeof(float), m_vertexWeightLen.y(), m_vertexFloatCount * sizeof(float));
    m_shaderProgram.enableAttributeArray("vColor");
    m_shaderProgram.setAttributeBuffer("vTexture", GL_FLOAT, 6*sizeof(float), m_vertexWeightLen.z(), m_vertexFloatCount * sizeof(float));
    m_shaderProgram.enableAttributeArray("vTexture");

    //纹理
    m_texture.create();                       //向GPU申请创建纹理对象
    m_texture.setData(QImage(":/Img/Res/Img/onetwo.jpg").mirrored());     //从QImage导入像素数据（内部会自动设置格式和分配存储）
    m_shaderProgram.setUniformValue("uTexture", 0);

    m_shaderProgram.release();
    m_vbo.release();
    m_vao.release();
}
