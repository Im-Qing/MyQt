#include "MOsgLine.h"
#include "MOsgScene.h"

using namespace NS_MOsg;

NS_MOsg::MOsgLine::MOsgLine(int id, QObject *parent) : MOsgNode(parent)
  ,m_id(id)
{
    m_pGeometry = new osg::Geometry;
    //设置颜色数组
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 0.5));
    m_pGeometry->setColorArray(colors);
    m_pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    //设置线宽
    osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(6.0);
    m_pGeometry->getOrCreateStateSet()->setAttribute(lw, osg::StateAttribute::ON);
    m_pGeometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    //几何节点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(m_pGeometry);
    //加入到变换节点
    m_pTransform->addChild(geode.get());
}

void MOsgLine::setLineColor(osg::Vec4 rgba)
{
    //设置颜色数组
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(rgba);
    m_pGeometry->setColorArray(colors);
    m_pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void MOsgLine::setLineWidth(int width)
{
    //设置线宽
    osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(width);
    m_pGeometry->getOrCreateStateSet()->setAttribute(lw, osg::StateAttribute::ON);
}

void MOsgLine::setLineVertexArray(const QList<MPos>& vex)
{
    MOsg mosg;
    //设置顶点数组
    osg::ref_ptr<osg::Vec3Array> vex1 = new osg::Vec3Array;
    for(int i = 0; i<vex.size(); i++)
    {
        MPos pos = vex[i];
        if(pos.m_isGeoPos)
        {
            osg::Vec3 pos1 = mosg.convertLatLongHeightToXYZ(pos);
            vex1->push_back(pos1);
        }
        else
        {
            vex1->push_back(osg::Vec3(pos.m_x, pos.m_y, pos.m_z));
        }
    }
    m_pGeometry->setVertexArray(vex1);
    //设置顶点关联方式
    osg::ref_ptr<osg::PrimitiveSet> primitiveSet = new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, vex.size());
    m_pGeometry->addPrimitiveSet(primitiveSet);
}
