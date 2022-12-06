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
    explicit MOsgScene(bool asEarth, QObject *parent = nullptr);
public:
    void setEarthFilePath(const QString& filePath);
    void addNode(MOsgNode* node);
    bool isAsEarth(){ return m_asEarth; }
    ///
    /// \brief convertLatLongHeightToXYZ
    /// \param geoPos
    /// \return
    /// 经纬高转(x,y,z)，单位为(度，度，米)
    osg::Vec3 convertLatLongHeightToXYZ(const osg::Vec3& geoPos);
private:
    void test(const QString& filePath);
    osg::ref_ptr<osg::Node> createQuad();
    osg::ref_ptr<osg::Node> createShape();
private:
    bool m_asEarth{false};
    osg::ref_ptr<osg::CoordinateSystemNode> m_pCsn;

    friend class MOsgNode;
};
}

#endif // MOSGSCENE_H
