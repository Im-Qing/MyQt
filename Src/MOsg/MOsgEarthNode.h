#ifndef MOSGEARTHNODE_H
#define MOSGEARTHNODE_H
#include "MOsgNode.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgEarthNode : public MOsgNode
{
public:
    MOsgEarthNode(QObject *parent = nullptr);
public:
    void setEarthFilePath(const QString& filePath);
    void addNode(MOsgNode* node);
private:
    osg::ref_ptr<osg::CoordinateSystemNode> m_pCsn;
};
}

#endif // MOSGEARTHNODE_H
