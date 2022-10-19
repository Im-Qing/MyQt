#ifndef MGLSCENE_H
#define MGLSCENE_H

#include <QObject>
#include <QMap>

namespace NS_MOpenGL
{

class MGLModel;

class MGLScene : public QObject
{
    Q_OBJECT

public:
    MGLScene(QObject *parent = nullptr);
public:
    void addModel(MGLModel* model);
private:
    QMap<QString,MGLModel*> m_mapNameToModel;
};
}

#endif // MGLSCENE_H
