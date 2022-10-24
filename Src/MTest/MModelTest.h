#ifndef MMODELTEST_H
#define MMODELTEST_H

#include "MOpenGL/MGLModel.h"

using namespace NS_MOpenGL;

class MModelShape;

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

//三角形、四边形等
class MModelShape : public MGLModel
{
    Q_OBJECT
public:
    MModelShape(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

#endif // MMODELTEST_H
