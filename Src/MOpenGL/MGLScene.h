#ifndef MGLSCENE_H
#define MGLSCENE_H

#include <QObject>
#include <QMap>

#include "MOpenGL.h"

namespace NS_MOpenGL
{

class MGLModel;

class MOPENGL_EXPORT MGLScene : public QObject
{
    Q_OBJECT

public:
    MGLScene(QObject *parent = nullptr);
public:
    void addModel(MGLModel* model);
public:
    QList<MGLModel*> getAllModel();
private:
    QMap<QString,MGLModel*> m_mapNameToModel;
};
}

#endif // MGLSCENE_H
