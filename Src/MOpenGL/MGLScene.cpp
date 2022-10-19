#include "MGLScene.h"
#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLScene::MGLScene(QObject *parent) : QObject(parent)
{

}

void MGLScene::addModel(MGLModel *model)
{
    QString modelName = model->getName();
    if(!m_mapNameToModel.contains(modelName))
    {
        m_mapNameToModel[modelName] = model;
        model->initialize();
    }
}

QList<MGLModel *> MGLScene::getAllModel()
{
    return m_mapNameToModel.values();
}
