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
    ~MGLModel();
public:
    void setName(const QString& name);
    void setVertices(float* vertices, int nSize);
    void setIndexs(unsigned int* indexs, int nSize);

    int getId();
    QString getName();
    MGLScene *getScene();
public:
    void addAttributeBuffer (const QString& name, GLenum type, int offset, int tupleSize, int stride = 0);
    void addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString& fileName);
    ///
    /// \brief addTextureFile
    /// \param index 纹理序号
    /// \param variableName 纹理在着色器中对应的变量名
    /// \param fileName
    ///
    void addTextureFile(int index, const QString& variableName, const QString& fileName);
protected:
    //真正的模型绘制函数，需要继承重写
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos) = 0;
    QOpenGLShaderProgram* getShaderProgram(){ return &m_shaderProgram; }
private:
    void initialize();
    //由MGLWidget对象调用
    void paintGL(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
    void setScene(MGLScene* scene);
    void bindTextures();
    void releaseTextures();
private:
    MGLScene *m_pScene;

    int m_id;                               //模型id
    QString m_name;                         //模型名称
    bool m_isInitializeFinished{false};     //是否初始化完成
    float* m_pVertexBuffer = nullptr;       //模型顶点缓冲数据
    int m_vertexBufferSize;                 //模型顶点缓冲数据大小
    unsigned int* m_pIndexBuffer = nullptr;        //模型元素缓冲数据
    int m_indexBufferSize;                         //模型元素缓冲数据大小
    QMap<QOpenGLShader::ShaderType, QString> m_mapShaderTypeToShaderFile;       //着色器程序文件集合
    QMap<QString, MGLAttributeBufferPara> m_mapNameToAttributeBufferPara;       //顶点数据buffer定义集合
    QMap<int, QString> m_mapIndexToVariableName;                                //纹理变量名集合
    QMap<int, QString> m_mapIndexToTextureFile;                                 //纹理文件集合
    QMap<int, QOpenGLTexture*> m_mapIndexToTextureData;                         //纹理数据集合

    //vao,vbo,shaderProgram
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLBuffer m_ebo;
    QOpenGLShaderProgram m_shaderProgram;

    friend class MGLScene;
    friend class MGLWidget;
};
}

#endif // MGLMODEL_H
