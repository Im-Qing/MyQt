#ifndef MOSGNODE_H
#define MOSGNODE_H
#include "MOsg_global.h"

#include <QObject>
#include <QDebug>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/PositionAttitudeTransform>
#include <osg/Program>
#include <osg/Shader>
#include <osg/Switch>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/StateSet>
#include <osg/ComputeBoundsVisitor>
#include <osg/Lod>
#include <osg/AutoTransform>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>

#include <osgDB/ReadFile>
#include <osgText/Text>
#include <osgFX/Scribe>

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
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pTransform;

    friend class MOsgScene;
};
}

#endif // MOSGNODE_H
