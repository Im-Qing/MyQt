#ifndef MGLDEFINES_H
#define MGLDEFINES_H

#include <QVector2D>
#include <QVector3D>

namespace NS_MOpenGL
{
struct MGLVertex
{
    QVector3D pos;
    QVector3D color;
    QVector2D texture;
    int vertexFloatCount = 8;
};
}

#endif // MGLDEFINES_H
