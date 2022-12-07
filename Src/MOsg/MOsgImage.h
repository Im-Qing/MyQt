#ifndef MOSGIMAGE_H
#define MOSGIMAGE_H
#include "MOsgNode.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgImage : public MOsgNode
{
    Q_OBJECT
public:
    explicit MOsgImage(const QString& filePath, QObject *parent = nullptr);
    void setImageFile(const QString& filePath);
private:
    osg::ref_ptr<osg::Geometry> m_pGeom;
    osg::ref_ptr<osg::Texture2D> m_pTexture2D;
    osg::ref_ptr<osg::Image> m_pImage;
};
}

#endif // MOSGIMAGE_H
