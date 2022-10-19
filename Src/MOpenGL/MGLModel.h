#ifndef MGLMODEL_H
#define MGLMODEL_H

#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QTime>

#include "MOpenGL.h"

namespace NS_MOpenGL
{

class MGLScene;

class MGLModel : public QObject, public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MGLModel(const QString& name, QObject *parent = nullptr);
public:
    void initialize();
    virtual void paint(QMatrix4x4 modelMat, QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
public:
    void setVertices(float *vertices, int nSize);
    void setAttributeBuffer (const char *name, GLenum type, int offset, int tupleSize, int stride = 0);
    bool addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString& fileName);
public:
    QString getName();
private:
    QString m_name;     //模型名称
    float *m_pVertexBuffer = nullptr;       //模型顶点数据
    int m_vertexBufferSize;     //模型顶点数据大小
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_shaderProgram;
};
}

#endif // MGLMODEL_H
