#pragma once
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
#include <osg/ProxyNode>
#include <osg/CoordinateSystemNode>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#include <osgText/Text>
#include <osgFX/Scribe>

namespace NS_MOsg
{
    struct MGeoPos      //经纬高坐标
    {
        double lon;     //度
        double lat;     //度
        double height;  //km
    };
}
