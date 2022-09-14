#ifndef MOSGEVENTHANDLER_H
#define MOSGEVENTHANDLER_H

#include "MOsg_global.h"

#include <QObject>
#include <QDebug>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include <osg/PositionAttitudeTransform>
#include <osg/NodeVisitor>
#include <osg/Geometry>

#include <iostream>

namespace NS_MOsg
{

class MOSG_EXPORT MOsgEventHandler : public QObject, public osgGA::GUIEventHandler
{
    Q_OBJECT
public:
    explicit MOsgEventHandler(QObject *parent = nullptr);
public:
    osg::Vec3d screen2World(osg::Vec3 screenPoint);
    osg::Vec3d world2Screen(osg::Vec3 worldPoint);
    osg::Vec3d world2Camera(osg::Vec3 worldPoint);
    osg::Vec3d camera2World(osg::Vec3 cameraPoint);
    osg::Vec3d screen2Camera(osg::Vec3 screenPoint);
    osg::Vec3d camera2Screen(osg::Vec3 cameraPoint);
private:
    virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    void pick(float x, float y, osgViewer::Viewer* viewer);
private:
    osgViewer::Viewer* viewer;
};

class MRotateCallBack: public osg::NodeCallback
{
 public:
    MRotateCallBack():_rotateZ(0.0) {}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
        if (pat)
        {
            osg::Quat quat(osg::DegreesToRadians(_rotateZ), osg::Z_AXIS);
            pat->setAttitude(quat);
            _rotateZ += 0.5;
        }
        traverse(node, nv);
    }

private:
    double _rotateZ;
};

class MInfoCallback: public osg::NodeCallback
{
public:

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
        if (pat)
        {
            double angle = 0.0;
            osg::Vec3 axis;
            pat->getAttitude().getRotate(angle, axis);
            //qDebug() << "Node is rotating around the(" << axis << ")axis," <<osg::RadiansToDegrees(angle)<<" degrees"<<std::endl;
        }
        traverse(node, nv);
    }
};

class MMainColorCallback: public osg::Uniform::Callback
{
public:
    MMainColorCallback(){}
    virtual void operator()( osg::Uniform* uniform, osg::NodeVisitor* nv)
    {
        osg::Vec4 color;
        uniform->get(color);

        float x_ = color.x();
        float y_ = color.y();
        x_ -= 0.001;
        y_ += 0.001;
        if(x_ <= 0)
            x_ = 1.0;
        if(y_ >= 1.0)
            y_ = 1.0;
        color.set(x_, y_, color.z(), color.w());

        uniform->set(color);
    }

private:
    float m_redValue = 1.0;
};

class VertexExtractor : public osg::NodeVisitor
{
public:
    //所有的顶点
    osg::ref_ptr<osg::Vec3Array> extracted_verts;
    //构造函数，选择向下遍历全孩子的方式
    VertexExtractor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
    {
        extracted_verts = new osg::Vec3Array;
    }
    //apply
    void apply( osg::Node& node )
    {
        qDebug()<<node.className();
        traverse(node);
    }
    //apply
    void apply( osg::Geode& geode )
    {
        qDebug()<<"Geode";
        //看看有多少可绘制结点
        for( unsigned int i=0; i < geode.getNumDrawables(); ++i )
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>( geode.getDrawable(i) );
            if( !geom )
                continue;
            //得到可绘制结点的顶点序列
            osg::Vec3Array* verts = dynamic_cast<osg::Vec3Array*>( geom->getVertexArray() );
            if( !verts )
                continue;
            //把顶点序列插入到顶点集中以便输出
            extracted_verts->insert( extracted_verts->end(), verts->begin(), verts->end() );
        }
        traverse(geode);
    }
    void apply(osg::Billboard& node)
    {
        qDebug()<<"Billboard";
        traverse(node);
    }
    void apply(osg::Drawable& node)
    {
        qDebug()<<"Drawable";
        traverse(node);
    }
};

}

#endif // MOSGEVENTHANDLER_H
