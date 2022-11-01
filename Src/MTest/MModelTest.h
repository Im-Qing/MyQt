#ifndef MMODELTEST_H
#define MMODELTEST_H

#include <QDateTime>

#include "MOpenGL/MGLModel.h"

using namespace NS_MOpenGL;

class MModelTest : public QObject
{
    Q_OBJECT
public:
    MModelTest(QObject *parent = nullptr);
public:
    MGLModel* getModel();
private:
    int m_modelId;
};

//三角形、四边形、立方体等
class MModelShape : public MGLModel
{
    Q_OBJECT
public:
    MModelShape(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//纹理
class MModelTexture : public MGLModel
{
    Q_OBJECT
public:
    MModelTexture(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//变换
class MModelTransform : public MGLModel
{
    Q_OBJECT
public:
    MModelTransform(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//模板测试
class MModelStencilTest : public MGLModel
{
    Q_OBJECT
public:
    MModelStencilTest(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//混合
class MModelBlend : public MGLModel
{
    Q_OBJECT
public:
    MModelBlend(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//帧缓冲
class MModelFBO : public MGLModel
{
    Q_OBJECT
public:
    MModelFBO(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//天空盒
class MModelSkyBox : public MGLModel
{
    Q_OBJECT
public:
    MModelSkyBox(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//实例化(绘制大量的模型,经过测试，如果用循环来绘制10万个模型时，会出现明显卡顿，而使用实例化则不会)
class MModelInstance : public MGLModel
{
    Q_OBJECT
public:
    MModelInstance(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

//环境映射(反射、折射)
class MModelEnvironmentMap : public MGLModel
{
    Q_OBJECT
public:
    MModelEnvironmentMap(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

#endif // MMODELTEST_H


