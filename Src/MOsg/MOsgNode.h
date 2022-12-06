#ifndef MOSGNODE_H
#define MOSGNODE_H

#include "MOsgDefines.h"

namespace NS_MOsg
{

class MOsgScene;

class MOSG_EXPORT MOsgNode : public QObject
{
public:
    MOsgNode(QObject *parent = nullptr);
public:
    void setPos(const osg::Vec3& pos);
    void setScale(const osg::Vec3& scale);
    void setRotate(const osg::Quat& quat);
public:
    osg::Node* get();
    virtual const osg::BoundingBox& getBoundingBox() const;
protected:
    void setScene(MOsgScene* osgScene){ m_pOsgScene = osgScene; }
protected:
    MOsgScene* m_pOsgScene{nullptr};
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pTransform;

    friend class MOsgScene;
};
}

#endif // MOSGNODE_H
