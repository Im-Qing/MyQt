#include "MOsgModel.h"

using namespace NS_MOsg;

NS_MOsg::MOsgModel::MOsgModel(int id, QObject* parent) : MOsgNode(parent)
, m_modelId(id)
{
    m_pLodNode = new osg::LOD;
    //图片节点
    m_p2DImgNode = new MOsgImage("");
    m_pLodNode->addChild(m_p2DImgNode->get(), 10, FLT_MAX);
    //3d模型
    m_p3DModelNodeRot = new osg::PositionAttitudeTransform;
    m_p3DModelNode = new osg::Node;
    m_p3DModelNodeRot->addChild(m_p3DModelNode.get());
    m_pLodNode->addChild(m_p3DModelNodeRot.get(), 0, 10);
    //文本
    m_pTextNode = new MOsgText("", this);
    //加入到变换节点
    m_pTransform->addChild(m_pLodNode.get());
    m_pTransform->addChild(m_pTextNode->get());
}

void NS_MOsg::MOsgModel::setName(const QString& name)
{
	m_modelName = name;
    m_pTextNode->setText(name);
    osg::BoundingBox boundingBox = m_pTextNode->getBoundingBox();

    float x__ = boundingBox.xMax() - boundingBox.xMin();
    float y__ = boundingBox.yMax() - boundingBox.yMin();
    float z__ = boundingBox.zMax() - boundingBox.zMin();
    float cx = boundingBox.center().x();
    float cy = boundingBox.center().y();
    float cz = boundingBox.center().z();

//    qDebug()<<"x__: "<<x__;
//    qDebug()<<"y__: "<<y__;
//    qDebug()<<"z__: "<<z__;
//    qDebug()<<"cx: "<<cx;
//    qDebug()<<"cy: "<<cy;
//    qDebug()<<"cz: "<<cz;

    float v_ = 1.0;
    m_pTextNode->setPos(osg::Vec3(0.0, 0.0, -(v_/2 + z__)));
}

void NS_MOsg::MOsgModel::set2DImg(const QString& imgPath)
{
	m_2DImgPath = imgPath;
    m_p2DImgNode->setImageFile(imgPath);
}

void NS_MOsg::MOsgModel::set3DModel(const QString& modelPath)
{
    m_3DModelPath = modelPath;
    m_p3DModelNodeRot->removeChild(m_p3DModelNode.get());
    m_p3DModelNode = osgDB::readNodeFile(modelPath.toStdString());
    osg::ComputeBoundsVisitor boundVisitor;
    m_p3DModelNode->accept(boundVisitor);
    osg::BoundingBox boundingBox = boundVisitor.getBoundingBox();

    float x__ = boundingBox.xMax() - boundingBox.xMin();
    float y__ = boundingBox.yMax() - boundingBox.yMin();
    float z__ = boundingBox.zMax() - boundingBox.zMin();
    float cx = boundingBox.center().x();
    float cy = boundingBox.center().y();
    float cz = boundingBox.center().z();

//    qDebug()<<"x__: "<<x__;
//    qDebug()<<"y__: "<<y__;
//    qDebug()<<"z__: "<<z__;
//    qDebug()<<"cx: "<<cx;
//    qDebug()<<"cy: "<<cy;
//    qDebug()<<"cz: "<<cz;

    float v_ = 1.0;
    float zScale = v_ / z__;
//    qDebug()<<"zScale : "<<zScale;
    m_p3DModelNodeRot->setPosition(osg::Vec3(0, 0, 0));
    m_p3DModelNodeRot->setScale(osg::Vec3(zScale, zScale, zScale));
    m_p3DModelNodeRot->addChild(m_p3DModelNode.get());
}

