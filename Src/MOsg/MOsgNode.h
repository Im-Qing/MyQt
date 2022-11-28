#ifndef MOSGNODE_H
#define MOSGNODE_H
#include "MOsg_global.h"

#include <QObject>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgText/Text>

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
protected:
    osg::Node* get();
protected:
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pTransform;

    friend class MOsgScene;
};
}

#endif // MOSGNODE_H
