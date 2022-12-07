#ifndef MOSGNODE_H
#define MOSGNODE_H

#include "MOsgDefines.h"
#include "MOsg.h"

namespace NS_MOsg
{

class MOsgScene;

class MOSG_EXPORT MOsgNode : public QObject
{
public:
    MOsgNode(QObject *parent = nullptr);
public:
    void setPos(const MPos& pos);
    void setScale(const osg::Vec3& scale);
    void setRotate(const osg::Quat& quat);
public:
    osg::Node* get();
    virtual const osg::BoundingBox& getBoundingBox() const;
protected:
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pTransform;

    friend class MOsgScene;
};
}

#endif // MOSGNODE_H
