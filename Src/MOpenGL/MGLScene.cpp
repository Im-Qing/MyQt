#include "MGLScene.h"
#include "MGLWidget.h"
#include "MGLModel.h"

using namespace NS_MOpenGL;

MGLScene::MGLScene(QObject *parent) : QObject(parent)
{

}

void MGLScene::addModel(MGLModel *model)
{
    int modelId = model->getId();
    if(!m_mapIdToModel.contains(modelId))
    {
        m_mapIdToModel[modelId] = model;
        model->setScene(this);
        model->initialize();
    }
}

QList<MGLModel *> MGLScene::getAllModel()
{
    return m_mapIdToModel.values();
}

void MGLScene::setGLWidget(MGLWidget *glWidget)
{
    m_pGLWidget = glWidget;
}

