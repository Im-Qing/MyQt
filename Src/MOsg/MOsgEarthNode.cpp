#include "MOsgEarthNode.h"

using namespace NS_MOsg;

NS_MOsg::MOsgEarthNode::MOsgEarthNode(QObject *parent) : MOsgNode (parent)
{

}

void MOsgEarthNode::setEarthFilePath(const QString &filePath)
{
    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(5.0f);

    osg::ShapeDrawable* sd = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0,0.0,0.0), osg::WGS_84_RADIUS_POLAR), hints);
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(sd);

    geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readRefImageFile(filePath.toStdString())));

    m_pCsn = new osg::CoordinateSystemNode;
    m_pCsn->setEllipsoidModel(new osg::EllipsoidModel());
    m_pCsn->addChild(geode);
    //加入到变换节点
    m_pTransform->addChild(m_pCsn.get());
}

void MOsgEarthNode::addNode(MOsgNode *node)
{
    m_pCsn->addChild(node->get());
}
