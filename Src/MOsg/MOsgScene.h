#ifndef MOSGSCENE_H
#define MOSGSCENE_H

#include "MOsg_global.h"

#include <QObject>

#include <osgDB/ReadFile>

namespace NS_MOsg
{
class MOSG_EXPORT MOsgScene : public QObject , public osg::Group
{
    Q_OBJECT
public:
    explicit MOsgScene(QObject *parent = nullptr);
public:
    void addNode(const QString& filePath);
private:

};
}

#endif // MOSGSCENE_H
