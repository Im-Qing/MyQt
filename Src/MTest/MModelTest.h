#ifndef MMODELTEST_H
#define MMODELTEST_H

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

#endif // MMODELTEST_H
