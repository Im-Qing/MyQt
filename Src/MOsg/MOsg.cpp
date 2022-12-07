#include "MOsg.h"

using namespace NS_MOsg;

MOsg::MOsg()
{
    m_pCsn = new osg::CoordinateSystemNode;
    m_pCsn->setEllipsoidModel(new osg::EllipsoidModel());
}

osg::Vec3 MOsg::convertLatLongHeightToXYZ(const MPos& geoPos)
{
    osg::Vec3 xyz;

    double lon = geoPos.m_x;
    double lat = geoPos.m_y;
    lon = -(180 - lon);
    double height = geoPos.m_z;
    double X,Y,Z;
    m_pCsn->getEllipsoidModel()->convertLatLongHeightToXYZ( osg::DegreesToRadians(lat), osg::DegreesToRadians(lon), height, X, Y, Z);
    xyz.set(X, Y, Z);

    return xyz;
}
