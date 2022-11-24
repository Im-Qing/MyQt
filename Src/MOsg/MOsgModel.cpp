#include "MOsgModel.h"

using namespace NS_MOsg;

NS_MOsg::MOsgModel::MOsgModel(int id, QObject* parent) : QObject(parent)
, m_modelId(id)
{

}

void NS_MOsg::MOsgModel::setName(const QString& name)
{
	m_modelName = name;
}

void NS_MOsg::MOsgModel::set2DImg(const QString& imgPath)
{
	m_2DImgPath = imgPath;
}

void NS_MOsg::MOsgModel::set3DModel(const QString& modelPath)
{
	m_3DModelPath = modelPath;
}

void NS_MOsg::MOsgModel::setPos(MGeoPos pos)
{
}

void NS_MOsg::MOsgModel::setScale(QVector3D xyzScale)
{
}

void NS_MOsg::MOsgModel::setRotate(const osg::Quat& quat)
{
}
