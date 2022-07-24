#include "MOsgScene.h"

using namespace NS_MOsg;

MOsgScene::MOsgScene(QObject *parent) : QObject(parent) , osg::Group()
{
    setName("root");
}

void MOsgScene::addNode(const QString &filePath)
{
    osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile(filePath.toStdString());
    addChild(pNode.get());
}
