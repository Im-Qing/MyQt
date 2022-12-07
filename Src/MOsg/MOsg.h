#ifndef MOSG_H
#define MOSG_H

#include "MOsgDefines.h"

namespace NS_MOsg
{
class MOsg
{
public:
    MOsg();
public:
    ///
    /// \brief convertLatLongHeightToXYZ
    /// \param geoPos
    /// \return
    /// 经纬高(单位为度，度，米)转(x,y,z)
    osg::Vec3 convertLatLongHeightToXYZ(const MPos& geoPos);
private:
    osg::ref_ptr<osg::CoordinateSystemNode> m_pCsn;
};
}

#endif // MOSG_H
