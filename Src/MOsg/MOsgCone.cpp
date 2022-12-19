#include "MOsgCone.h"

using namespace NS_MOsg;

MOsgCone::MOsgCone(QObject *parent) : MOsgNode(parent)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    //半径
    float radius = 0.1f;
    //高度
    float height = 1.6f;

    //精细度
    osg::TessellationHints* hints1 = new osg::TessellationHints();
    //设置精细度
    hints1->setDetailRatio(0.8f);

    //创建圆锥体
    osg::Cone *cone = new osg::Cone(osg::Vec3(100.0f, 0.0f, 0.0f), radius, height);
    osg::ShapeDrawable *draw1 = new osg::ShapeDrawable(cone, hints1);

    //设置圆锥透明效果
    osg::ref_ptr<osg::StateSet> stateset=geode->getOrCreateStateSet();
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    //设置圆锥网格模型
    osg::ref_ptr<osg::PolygonMode> polyMode=new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
    stateset->setAttribute(polyMode);

    //设置圆锥的颜色，第四个参数0.25表示不透明度，0表示完全透明，1表示完全不透明
    draw1->setColor(osg::Vec4(0.0,1.0,0.0,1.0));

    geode->addDrawable(draw1);

    //加入到变换节点
    m_pTransform->addChild(geode.get());
}
