#include "MModelTest.h"

MModelTest::MModelTest(int id, QObject *parent) : MGLModel(id, parent)
{

}

void MModelTest::paint(QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    //m_shaderProgram.setUniformValue("unColor", QVector3D(1.0, 0.0, 0.0));
    glDrawArrays(GL_QUADS, 0, 4);
}
