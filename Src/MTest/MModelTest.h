#ifndef MMODELTEST_H
#define MMODELTEST_H

#include "MOpenGL/MGLModel.h"

using namespace NS_MOpenGL;

class MModelTest : public MGLModel
{
    Q_OBJECT
public:
    MModelTest(int id, QObject *parent = nullptr);
protected:
    virtual void paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos);
};

#endif // MMODELTEST_H
