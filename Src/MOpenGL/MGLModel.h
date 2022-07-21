#ifndef MGLMODEL_H
#define MGLMODEL_H

#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "MGLDefines.h"

namespace NS_MOpenGL
{
class MGLModel : public QObject, public QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MGLModel(QObject *parent = nullptr);
public:
    void setVertices(const QVector<MGLVertex> &vertices);
    void setTexture(QOpenGLTexture *texture, int index);
    void setPos(const QVector3D& pos);
    void setScale(const QVector3D& scale);
    void setRotate(const QVector3D& rotate);
public:
    void initialize();
    void paint();
private:
    QVector<MGLVertex> m_vertices;          //顶点
    QMap<int, QOpenGLTexture*> m_textures;  //纹理
    QVector3D m_pos;
    QVector3D m_scale;
    QVector3D m_rotate;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_shaderProgram;
    float *m_pVertexBuffer = nullptr;
};
}

#endif // MGLMODEL_H
