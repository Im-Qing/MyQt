#ifndef MOSGSCENE_H
#define MOSGSCENE_H

#include "MOsgDefines.h"
#include "MOsgEventHandler.h"

namespace NS_MOsg
{

class MOsgNode;

class MOSG_EXPORT MOsgScene : public QObject , public osg::Group
{
    Q_OBJECT
public:
    explicit MOsgScene(QObject *parent = nullptr);
public:
    void addNode(MOsgNode* node);
    void test(const QString& filePath);
private:
    osg::ref_ptr<osg::Node> createQuad();
    osg::ref_ptr<osg::Node> createShape();
private:

    friend class MOsgNode;
};
}

#endif // MOSGSCENE_H
