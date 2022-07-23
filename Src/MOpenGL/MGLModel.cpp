#include "MGLModel.h"

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

MGLModel::MGLModel(QObject *parent) : QObject(parent)
  , m_texture(QOpenGLTexture::Target2D)
  , m_texture1(QOpenGLTexture::Target2D)
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

void MGLModel::setVertices(float *vertices, int nSize)
{
    m_pVertexBuffer = vertices;
    m_vertexBufferSize = nSize;
}

void MGLModel::setTexture(const QString& imgSrc, int index)
{
    m_texturesImgsrc[index] = imgSrc;
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
    m_vbo.allocate(m_pVertexBuffer, m_vertexBufferSize);

    //着色器加载链接
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/GLSL/Res/GLSL/vertex.glsl");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/GLSL/Res/GLSL/fragment.glsl");
    m_shaderProgram.link();

    //着色器解析规则
    m_shaderProgram.setAttributeBuffer("vPos", GL_FLOAT, 0*sizeof(float), 3, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vPos");
    m_shaderProgram.setAttributeBuffer("vNormal", GL_FLOAT, 3*sizeof(float), 3, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vNormal");
    m_shaderProgram.setAttributeBuffer("vTextureCoords", GL_FLOAT, 6*sizeof(float), 2, 8*sizeof(float));
    m_shaderProgram.enableAttributeArray("vTextureCoords");

    //纹理
    m_texture.create();
    m_texture.setData(QImage(m_texturesImgsrc[0]).mirrored());
    m_texture1.create();
    m_texture1.setData(QImage(m_texturesImgsrc[1]).mirrored());

    m_shaderProgram.release();
    m_vbo.release();
    m_vao.release();
}

void MGLModel::paint(QMatrix4x4 modelMat, QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos, bool isObject)
{
    m_vao.bind();
    m_shaderProgram.bind();

    m_shaderProgram.setUniformValue("material.diffuse", 0);
    m_shaderProgram.setUniformValue("material.specular", 1);
    m_texture.bind(0);
    m_texture1.bind(1);

    m_shaderProgram.setUniformValue("model", modelMat);
    m_shaderProgram.setUniformValue("view", viewMat);
    m_shaderProgram.setUniformValue("projection", projectionMat);

    m_shaderProgram.setUniformValue("isObject", isObject);
    if(isObject)
    {
        glm::vec3 lightColor;
        lightColor.x = sin(QTime::currentTime().second() * 2.0f);
        lightColor.y = sin(QTime::currentTime().second() * 0.7f);
        lightColor.z = sin(QTime::currentTime().second() * 1.3f);
        m_shaderProgram.setUniformValue("light.color", lightColor.x, lightColor.y, lightColor.z);
        m_shaderProgram.setUniformValue("light.color", 1.0f, 1.0f, 1.0f);
        m_shaderProgram.setUniformValue("light.cutOff", glm::cos(glm::radians(12.5f)));
    }
    else
        m_shaderProgram.setUniformValue("light.color", QVector3D(1.0f, 1.0f, 1.0f));

    m_shaderProgram.setUniformValue("light.position", cameraPos);
    m_shaderProgram.setUniformValue("light.direction", QVector3D(-0.0f, -0.0f, -1.f));

    m_shaderProgram.setUniformValue("viewPos", cameraPos);

    m_shaderProgram.setUniformValue("material.ambientStrength",  0.2f);
    m_shaderProgram.setUniformValue("material.diffuseStrength",  1.0f);
    m_shaderProgram.setUniformValue("material.specularStrength", 1.f);
    m_shaderProgram.setUniformValue("material.shininess", 16.0f);

    if(isObject)
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
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    m_texture1.release();
    m_texture.release();
    m_shaderProgram.release();
    m_vao.release();
}

QMatrix4x4 MGLModel::glmMat4ToQMat4(glm::mat4 mat4)
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


