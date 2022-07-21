#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLModel::MGLModel(QObject *parent) : QObject(parent)
{

}

void MGLModel::setVertices(const QVector<MGLVertex> &vertices)
{
    m_vertices = vertices;
    //转成float*
    if (m_pVertexBuffer)
        delete[] m_pVertexBuffer;
    m_pVertexBuffer = new float[m_vertices.count() * MGLVertex().vertexFloatCount];
    int offset = 0;
    for (auto &vertex : m_vertices)
    {
        m_pVertexBuffer[offset] = vertex.pos.x(); offset++;
        m_pVertexBuffer[offset] = vertex.pos.y(); offset++;
        m_pVertexBuffer[offset] = vertex.pos.z(); offset++;
        m_pVertexBuffer[offset] = vertex.texture.x(); offset++;
        m_pVertexBuffer[offset] = vertex.texture.y(); offset++;
    }
}

void MGLModel::setTexture(QOpenGLTexture *texture, int index)
{
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
