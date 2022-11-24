#ifndef MOSGSCENE_H
#define MOSGSCENE_H

#include "MOsg_global.h"

#include "MOsgModel.h"
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
