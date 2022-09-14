#include "MOsgEventHandler.h"

using namespace NS_MOsg;

MOsgEventHandler::MOsgEventHandler(QObject *parent) : QObject(parent), osgGA::GUIEventHandler()
{

}

osg::Vec3d MOsgEventHandler::screen2World(osg::Vec3 screenPoint)//将屏幕坐标转换到世界坐标
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    //osg::Vec3d vScreen(x,y, 0);
    osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    osg::Matrix invertVPW;
    invertVPW.invert(mVPW);
    vec3 = screenPoint * invertVPW;
    return vec3;
}
osg::Vec3d MOsgEventHandler::world2Screen(osg::Vec3 worldPoint)//世界到屏幕
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    vec3 = worldPoint * mVPW;
    return vec3;
}

osg::Vec3d MOsgEventHandler::world2Camera(osg::Vec3 worldPoint)//世界转相机
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    osg::Matrix mV = camera->getViewMatrix();
    vec3 = worldPoint * mV;
    return vec3;
}
osg::Vec3d MOsgEventHandler::camera2World(osg::Vec3 cameraPoint)//相机转世界
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    //osg::Vec3d vScreen(x,y, 0);
    osg::Matrix mV = camera->getViewMatrix();
    osg::Matrix invertmV;
    invertmV.invert(mV);
    vec3 = cameraPoint * invertmV ;
    return vec3;
}
osg::Vec3d MOsgEventHandler::screen2Camera(osg::Vec3 screenPoint)//屏幕转相机
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    osg::Matrix mPW = camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    osg::Matrix invertmPW;
    invertmPW.invert(mPW);
    vec3 = screenPoint * invertmPW;
    return vec3;
}
osg::Vec3d MOsgEventHandler::camera2Screen(osg::Vec3 cameraPoint)//相机转屏幕
{
    osg::Vec3d vec3;
    osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
    //osg::Vec3d vScreen(x,y, 0);
    osg::Matrix mPW = camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
    vec3 = cameraPoint * mPW;
    return vec3;
}

bool MOsgEventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
    if (!viewer) return false;

    switch(ea.getEventType())
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
    {
        qDebug()<<ea.getKey();
//        if (ea.getKey() == 0x61)
//        {
//            viewer ->getSceneData() ->asGroup() ->getChild(1) ->setNodeMask(0) ;
//            viewer ->getSceneData() ->asGroup() ->getChild(0) ->setNodeMask(1) ;
//        }
//        if (ea.getKey()== 0x62)
//        {
//            viewer ->getSceneData() ->asGroup() ->getChild(0) ->setNodeMask(0) ;
//            viewer ->getSceneData() ->asGroup() ->getChild(1) ->setNodeMask(1) ;
//        }
    }break;
    case osgGA::GUIEventAdapter::PUSH:
    {
        pick(ea.getX(), ea.getY(), viewer);
        //viewer->getCamera()->setViewMatrixAsLookAt(osg::Vec3d(10.0, 0.0, 3.0), osg::Vec3d(0.0, 0.0, 0.0), osg::Vec3d(0.0, 0.0, 1.0));
//        if(ea.getButton () == 4)
//        {
//            viewer ->getSceneData() ->asGroup() ->getChild(0) ->setNodeMask(0) ;
//            viewer ->getSceneData() ->asGroup() ->getChild(1) ->setNodeMask(0) ;
//        }
    }break;
    case osgGA::GUIEventAdapter::DOUBLECLICK:
    {
//        if(ea.getButton() == 1)
//        {
//            viewer ->getSceneData() ->asGroup() ->getChild(0) ->setNodeMask(1) ;
//            viewer ->getSceneData() ->asGroup() ->getChild(1) ->setNodeMask(1) ;
//        }
    }break;
    default:
        break;
    }

    return false;
}

void MOsgEventHandler::pick(float x, float y, osgViewer::Viewer* viewer)
{
    static bool enable = false;

    osgUtil::LineSegmentIntersector::Intersections intersections;
    if (viewer->computeIntersections(x, y, intersections))
    {
        qDebug()<<"intersections.szie(): "<<intersections.size();
        for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
            hitr != intersections.end();
            ++hitr)
        {
            if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
            {

                osg::NodePath np = hitr->nodePath;

                for (int i=np.size()-1; i>=0; --i)
                {
                    osgFX::Scribe* sc= dynamic_cast<osgFX::Scribe *>(np[i]);
                    if (sc!= nullptr)
                    {
                        if(sc ->getNodeMask() != 0)
                            sc ->setEnabled(enable) ;
                    }
                    osg::PositionAttitudeTransform* pat= dynamic_cast<osg::PositionAttitudeTransform *>(np[i]);
                    if(pat)
                    {
                        pat->setNodeMask(enable);
                    }
                }
            }
        }
    }

    enable = !enable;
}
