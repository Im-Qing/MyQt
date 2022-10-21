#ifndef MGLSCENE_H
#define MGLSCENE_H

#include <QObject>
#include <QMap>

#include "MOpenGL.h"

namespace NS_MOpenGL
{

class MGLWidget;
class MGLModel;

class MOPENGL_EXPORT MGLScene : public QObject, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    MGLScene(QObject *parent = nullptr);
public:
    void addModel(MGLModel* model);
public:
    QList<MGLModel*> getAllModel();
private:
    void setGLWidget(MGLWidget* glWidget);

    MGLWidget* getGLWidget(){ return m_pGLWidget; };
private:
    MGLWidget* m_pGLWidget = nullptr;
    QMap<int,MGLModel*> m_mapIdToModel;

    friend class MGLWidget;
    friend class MGLModel;
};
}

#endif // MGLSCENE_H
