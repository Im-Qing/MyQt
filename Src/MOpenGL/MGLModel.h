#ifndef MGLMODEL_H
#define MGLMODEL_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>

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
    void setCurrentKey(int key){ m_currentKey = key; }

    int getId();
    QString getName();
    MGLScene *getScene();
public:
    void addShaderFromSourceFile(QOpenGLShader::ShaderType type, const QString& fileName);
    void addVertices(float* vertices, int nSize);
    void addAttributeBuffer (const QString& name, GLenum type, int offset, int tupleSize, int stride = 0);
    void addIndexs(unsigned int* indexs, int nSize);
    void addInstanceVertices(void* instanceVertices, int nSize);
    void addInstanceAttributeBuffer (int location, GLenum type, int offset, int tupleSize, int stride = 0);
    void addVertexAttribDivisor(int location, GLuint divisor);
    ///
    /// \brief addTexture2DFile
    /// \param index 纹理序号
    /// \param variableName 纹理在着色器中对应的变量名
    /// \param fileName
    ///
    void addTexture2DFile(int index, const QString& variableName, const QString& fileName);
    ///
    /// \brief addSkyBoxTexture
    /// \param index
    /// \param variableName
    /// \param fileNameList 按Right，Left，Top，Bottom，Front，Back顺序赋值
    ///
    void addSkyBoxTextureFile(int index, const QString& variableName, const QStringList& fileNameList);
protected:
    //真正的绘制函数，需要继承重写
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos) = 0;
    void resizeGL(int w, int h);
    QOpenGLShaderProgram* getShaderProgram(int key);
    void bind(int key);
    void release(int key);
    void bindFbo(int key = 0);
    void releaseFbo(int key = 0);
    ///
    /// \brief bindFboTexture
    /// \param shaderProgramkey 着色器程序的key值
    /// \param variableName 纹理在着色器中对应的变量名
    /// \param key fbo的key值
    ///
    void bindFboTexture(int shaderProgramkey, const QString& variableName, int key = 0);
private:
    void initialize();
    //由MGLWidget对象调用
    void paintGL(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
    void setScene(MGLScene* scene);
private:
    MGLScene *m_pScene;                     //关联的场景
    int m_id;                               //模型id
    QString m_name;                         //模型名称
    bool m_isInitializeFinished{false};     //是否初始化完成

    int m_currentKey{0};       //当前key，用于标识一组用于绘制同一个对象的数据（顶点数据、索引数据、着色器数据、纹理数据等）,默认为0
    QMap<int, QMap<QOpenGLShader::ShaderType, QString>> m_mapKeyToShaderTypeToShaderFile;       //着色器程序文件集合
    QMap<int, float*> m_mapKeyToVertexBuffer;               //模型顶点缓冲数据集合
    QMap<int, int> m_mapKeyToVertexBufferSize;              //模型顶点缓冲数据大小集合
    QMap<int, QMap<QString, MGLAttributeBufferPara>> m_mapKeyToNameToAttributeBufferPara;       //顶点数据buffer定义集合
    QMap<int, unsigned int*> m_mapKeyToIndexBuffer;         //模型元素缓冲数据集合
    QMap<int, int> m_mapKeyToIndexBufferSize;               //模型元素缓冲数据大小集合
    QMap<int, void*> m_mapKeyToInstanceVertexBuffer;               //实例化顶点缓冲数据集合
    QMap<int, int> m_mapKeyToInstanceVertexBufferSize;              //实例化顶点缓冲数据大小集合
    QMap<int, QMap<int, MGLAttributeBufferPara>> m_mapKeyToNameToInstanceAttributeBufferPara;       //实例化顶点数据buffer定义集合
    QMap<int, QMap<int, int>> m_mapKeyToNameToInstanceAttribDivisor;       //实例化顶点数据buffer定义集合
    QMap<int, QMap<int, QString>> m_mapKeyToIndexToVariableName;                                //纹理变量名集合
    QMap<int, QMap<int, QString>> m_mapKeyToIndexToTextureFile;                                 //纹理文件集合
    QMap<int, QMap<int, QStringList>> m_mapKeyToIndexToSkyBoxTextureFile;                       //天空盒纹理文件集合
    QMap<int, QMap<int, QOpenGLTexture*>> m_mapKeyToIndexToTextureData;                         //纹理数据集合
    //shaderProgram,vao,vbo,ebo,fbo
    QMap<int, QOpenGLShaderProgram*> m_mapKeyToShaderProgram;
    QMap<int, QOpenGLVertexArrayObject*> m_mapKeyToVao;
    QMap<int, QOpenGLBuffer> m_mapKeyToVbo;
    QMap<int, QOpenGLBuffer> m_mapKeyToEbo;
    QMap<int, QOpenGLBuffer> m_mapKeyToInstanceVbo;
    QOpenGLFramebufferObject* m_pFbo;

    friend class MGLScene;
    friend class MGLWidget;
};
}

#endif // MGLMODEL_H
