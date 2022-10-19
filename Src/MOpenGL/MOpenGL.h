#ifndef MOPENGL_H
#define MOPENGL_H

#include "MOpenGL_global.h"
#include "MGLDefines.h"

namespace NS_MOpenGL
{
class MOPENGL_EXPORT MOpenGL
{
public:
    MOpenGL();
public:
    static QMatrix4x4 glmMat4ToQMat4(glm::mat4 mat4);
};
}

#endif // MOPENGL_H
