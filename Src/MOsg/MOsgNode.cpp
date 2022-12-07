#include "MOsgNode.h"
#include "MOsgScene.h"

using namespace NS_MOsg;

MOsgNode::MOsgNode(QObject *parent) : QObject(parent)
{
    m_pTransform = new osg::PositionAttitudeTransform;
}

void MOsgNode::setPos(const MPos &pos)
{
    MOsg mosg;
    osg::Vec3 pos1(pos.m_x, pos.m_y, pos.m_z);
    if(pos.m_isGeoPos)
    {
        pos1 = mosg.convertLatLongHeightToXYZ(pos);
    }
    m_pTransform->setPosition(pos1);
}

void MOsgNode::setScale(const osg::Vec3 &scale)
{
    m_pTransform->setScale(scale);
}

void MOsgNode::setRotate(const osg::Quat &quat)
{
    m_pTransform->setAttitude(quat);
}

osg::Node *MOsgNode::get()
{
    return m_pTransform.get();
}

const osg::BoundingBox &MOsgNode::getBoundingBox() const
{
    return osg::BoundingBox();
}
