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
    struct MPos      //坐标
    {
        bool m_isGeoPos = false;      //是否是经纬高坐标，若为true，则x,y,z分别表示经度(度)，纬度(度)，高度(米)
        double m_x;
        double m_y;
        double m_z;

        MPos(double x, double y, double z, bool isGeoPos = false)
        {
            m_x = x;
            m_y = y;
            m_z = z;
            m_isGeoPos = isGeoPos;
        }
    };
}
