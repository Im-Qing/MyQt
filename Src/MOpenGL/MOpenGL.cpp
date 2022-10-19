#include "MOpenGL.h"

using namespace NS_MOpenGL;

MOpenGL::MOpenGL()
{
}

QMatrix4x4 MOpenGL::glmMat4ToQMat4(glm::mat4 mat4)
{
    QMatrix4x4 matRes;

    for(int c = 0; c < 4; c++)
    {
        QVector4D row;
        row.setX(mat4[0][c]);
        row.setY(mat4[1][c]);
        row.setZ(mat4[2][c]);
        row.setW(mat4[3][c]);
        matRes.setRow(c, row);
    }

    return matRes;
}
