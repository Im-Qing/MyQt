#pragma once
#include "MOsg_global.h"

#include <QObject>
#include <QVector3D>

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

#include "MOsgDefines.h"

namespace NS_MOsg
{
	class MOSG_EXPORT MOsgModel : public QObject
	{
		Q_OBJECT
	public:
		explicit MOsgModel(int id, QObject* parent = nullptr);
	public:
		void setName(const QString& name);
		void set2DImg(const QString& imgPath);
		void set3DModel(const QString& modelPath);
		void setPos(MGeoPos pos);
		void setScale(QVector3D xyzScale);
		void setRotate(const osg::Quat& quat);
	private:
		int m_modelId;
		QString m_modelName;
		QString m_2DImgPath;
		QString m_3DModelPath;

		osg::ref_ptr <osg::PositionAttitudeTransform> m_pTranNode;
		osg::ref_ptr<osg::LOD> m_pLodNode;

		osg::ref_ptr <osg::Node> m_p2DImgNode;
		osg::ref_ptr <osg::Node> m_p3DModelNode;
	};
}

