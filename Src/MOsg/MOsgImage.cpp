#include "MOsgImage.h"

using namespace NS_MOsg;

MOsgImage::MOsgImage(const QString& filePath, QObject *parent) : MOsgNode(parent)
{
    osg::ref_ptr<osg::Geometry> pGeom = new osg::Geometry;
    //首先定义四个点
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    pGeom->setVertexArray(v.get());
    v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
    v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
    v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
    v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );
    //定义纹理坐标
    osg::ref_ptr<osg::Vec2Array> spCoordArray = new osg::Vec2Array();
    spCoordArray->push_back(osg::Vec2(0.0, 1.0));
    spCoordArray->push_back(osg::Vec2(0.0, 0));
    spCoordArray->push_back(osg::Vec2(1.0, 0.0));
    spCoordArray->push_back(osg::Vec2(1.0, 1.0));
    pGeom->setTexCoordArray(0, spCoordArray);
    //纹理图片
    osg::ref_ptr<osg::Image> pImage = osgDB::readImageFile(filePath.toStdString());
    osg::ref_ptr <osg::Texture2D> spTexture2D = new osg::Texture2D(pImage);
    spTexture2D->setUnRefImageDataAfterApply(true);
    osg::ref_ptr<osg::StateSet> spStateSet = pGeom->getOrCreateStateSet();
    spStateSet->setTextureAttributeAndModes(0, spTexture2D);
    spStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    //要想看到png图片的透明效果，需要开启混合模式
    spStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
    spStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    //设置顶点关联方式
    pGeom->addPrimitiveSet(new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );
    //几何组结点
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    pGeode->addDrawable(pGeom.get());
    //加入到变换节点
    m_pTransform->addChild(pGeode.get());
}

