#ifndef MOSGSCENE_H
#define MOSGSCENE_H

#include "MOsg_global.h"

#include <QObject>

#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osg/Switch>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osgFX/Scribe>
#include <osg/Program>
#include <osg/Shader>

#include "MOsgEventHandler.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgScene : public QObject , public osg::Group
{
    Q_OBJECT
public:
    explicit MOsgScene(QObject *parent = nullptr);
public:
    void addNode(const QString& filePath);
    void setOsgView(osgViewer::Viewer* viewer){ m_pViewer = viewer; }
private:
    osg::ref_ptr<osg::Node> createQuad();
    osg::ref_ptr<osg::Node> createShape();
private:
    osgViewer::Viewer* m_pViewer;
};
}

#endif // MOSGSCENE_H
