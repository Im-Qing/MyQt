#include "MModelTest.h"

MModelTest::MModelTest(int id, QObject *parent) : MGLModel(id, parent)
{

}

void MModelTest::paint(QMatrix4x4 modelMat, QMatrix4x4 viewMat, QMatrix4x4 projectionMat, QVector3D cameraPos)
{
    if(isInitializeFinished())
    {
        m_vao.bind();
        m_shaderProgram.bind();

        //m_shaderProgram.setUniformValue("unColor", QVector3D(1.0, 0.0, 0.0));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        m_shaderProgram.release();
        m_vao.release();
    }
    else
    {
        qDebug() << QString("paint model fail, m_isInitializeFinished = %1, modelId = %2").arg(isInitializeFinished()).arg(getId());
    }
}
