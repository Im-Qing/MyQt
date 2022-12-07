#include "MOsgCone.h"

using namespace NS_MOsg;

MOsgCone::MOsgCone(QObject *parent) : MOsgNode(parent)
{
    //创建圆锥几何体
    osg::ref_ptr<osg::Cone>  cone=new osg::Cone;
    osg::ref_ptr<osg::ShapeDrawable> shap=new osg::ShapeDrawable(cone);
    osg::ref_ptr<osg::Geode> geode=new osg::Geode;
    geode->addDrawable(shap);

    //设置圆锥高
    cone->setHeight(20000);
    //设置圆锥地面半径
    cone->setRadius(1000);

    //设置圆锥的颜色，第四个参数0.25表示不透明度，0表示完全透明，1表示完全不透明
    shap->setColor(osg::Vec4(1.0,0.0,0.0,0.25));

    //设置圆锥透明效果
    osg::ref_ptr<osg::StateSet> stateset=geode->getOrCreateStateSet();
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    //设置圆锥网格模型
    osg::ref_ptr<osg::PolygonMode> polyMode=new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
    stateset->setAttribute(polyMode);

    //使圆锥由默认的z轴方向旋转到(1.0,1.0,1.0)方向
    osg::Quat quat;
    //根据两个向量计算四元数
    quat.makeRotate(osg::Z_AXIS,osg::Vec3(1.0,1.0,1.0));
    cone->setRotation(quat);

    //加入到变换节点
    m_pTransform->addChild(geode.get());
}
