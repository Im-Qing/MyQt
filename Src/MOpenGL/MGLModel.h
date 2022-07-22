#ifndef MGLMODEL_H
#define MGLMODEL_H

#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setVertices(float *vertices);
    void setTexture(const QString& imgSrc, int index);
    void setPos(const QVector3D& pos);
    void setScale(const QVector3D& scale);
    void setRotate(const QVector3D& rotate);
public:
    void initialize();
    void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat);
private:
    QMatrix4x4 glmMat4ToQMat4(glm::mat4 mat4);
private:
    QVector<MGLVertex> m_vertices;               //顶点
    QMap<int, QString> m_texturesImgsrc;         //纹理图片
    QMap<int, QOpenGLTexture*> m_textures;       //纹理
    QVector3D m_pos;
    QVector3D m_scale;
    QVector3D m_rotate;

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_shaderProgram;
    float *m_pVertexBuffer = nullptr;
    QVector3D m_vertexWeightLen = QVector3D(0, 0, 0);            //顶点各分量的float长度（位置，颜色，纹理），如果这三个顶点数据都有的话则值为(3, 3, 2)
    int m_vertexFloatCount;
};
}

#endif // MGLMODEL_H
