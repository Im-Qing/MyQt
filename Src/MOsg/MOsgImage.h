#ifndef MOSGIMAGE_H
#define MOSGIMAGE_H
#include "MOsgNode.h"

namespace NS_MOsg
{
class CallBack : public osg::StateSet::Callback
{
public:
    virtual void operator()(osg::StateSet* ss, osg::NodeVisitor* nv)
    {
        if(!ss) return;
//        osg::Texture2D* pTexture2D = dynamic_cast<osg::Texture2D*>(ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE));
//        qDebug()<<QString::fromStdString(pTexture2D->getImage()->getFileName());
//        //pTexture2D->getImage()->setFileName(pTexture2D->getImage()->getFileName());
//        pTexture2D->setImage(osgDB::readImageFile(pTexture2D->getImage()->getFileName()));
//        //ss->setTextureAttributeAndModes(0, pTexture2D);
//        //m_pGeom->getOrCreateStateSet()->setTextureAttributeAndModes(0, m_pTexture2D);
    }
};

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
