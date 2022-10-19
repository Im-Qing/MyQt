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

#define ILLEGALVector3D QVector3D(-100, -100, -100)
#define ILLEGALVector2D QVector2D(-100, -100)

namespace NS_MOpenGL
{
struct MGLVertex
{
    QVector3D pos = ILLEGALVector3D;        //如果是非法值，则表示没有位置顶点
    QVector3D color = ILLEGALVector3D;      //如果是非法值，则表示没有颜色顶点
    QVector2D texture = ILLEGALVector2D;    //如果是非法值，则表示没有纹理顶点
};
}

#endif // MGLDEFINES_H
