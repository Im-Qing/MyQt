#ifndef MGLMODEL_H
#define MGLMODEL_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "MOpenGL.h"

namespace NS_MOpenGL
{

class MGLScene;
class MGLWidget;

class MOPENGL_EXPORT MGLModel : public QObject , protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MGLModel(int id, QObject *parent = nullptr);
public:
    void setName(const QString& name);
    void setVertices(float *vertices, int nSize);

    int getId();
    QString getName();
    MGLScene *getScene();
public:
    void addAttributeBuffer (const QString& name, GLenum type, int offset, int tupleSize, int stride = 0);
    void addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString& fileName);
protected:
    void initialize();
    virtual void paint(QMatrix4x4 modelMat, QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos) = 0;
    bool isInitializeFinished(){ return m_isInitializeFinished; }
private:
    void setScene(MGLScene* scene);
private:
    MGLScene *m_pScene;

    int m_id;                               //模型id
    QString m_name;                         //模型名称
    bool m_isInitializeFinished{false};     //是否初始化完成
    float* m_pVertexBuffer = nullptr;       //模型顶点数据
    int m_vertexBufferSize;                 //模型顶点数据大小
    QMap<QOpenGLShader::ShaderType, QString> m_mapShaderTypeToShaderFile;       //着色器程序文件集合
    QMap<QString, MGLAttributeBufferPara> m_mapNameToAttributeBufferPara;       //顶点数据buffer定义集合
protected:
    //vao,vbo,shaderProgram
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_shaderProgram;

    friend class MGLScene;
    friend class MGLWidget;
};
}

#endif // MGLMODEL_H
