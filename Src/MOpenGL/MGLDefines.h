#ifndef MGLDEFINES_H
#define MGLDEFINES_H

#include <QMatrix4x4>
#include <QDebug>
#include <QVector2D>
#include <QVector3D>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gltypes.h>

namespace NS_MOpenGL
{
struct MGLAttributeBufferPara
{
    QString name;
    GLenum type;
    int offset;
    int tupleSize;
    int stride;
};
}

#endif // MGLDEFINES_H
