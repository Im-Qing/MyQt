#pragma once
#include "MOsgNode.h"
#include "MOsgImage.h"
#include "MOsgText.h"

namespace NS_MOsg
{
    class MOSG_EXPORT MOsgModel : public MOsgNode
	{
		Q_OBJECT
	public:
		explicit MOsgModel(int id, QObject* parent = nullptr);
	public:
		void setName(const QString& name);
		void set2DImg(const QString& imgPath);
		void set3DModel(const QString& modelPath);
	private:
		int m_modelId;
		QString m_modelName;
		QString m_2DImgPath;
		QString m_3DModelPath;

        osg::ref_ptr<osg::LOD> m_pLodNode;
        MOsgImage* m_p2DImgNode;
        osg::ref_ptr<osg::PositionAttitudeTransform> m_p3DModelNodeRot;
        osg::ref_ptr<osg::Node> m_p3DModelNode;
        MOsgText* m_pTextNode;
	};
}

