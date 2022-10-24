#include "MMainWindow.h"
#include "ui_MMainWindow.h"

#include <QDebug>

MMainWindow::MMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMainWindow)
{
    ui->setupUi(this);
    resize(800, 600);

    //场景
    m_pGLScene = new MGLScene(this);
    //视图
    m_pGLWidget = new MGLWidget(m_pGLScene, this);
    ui->gridLayout->addWidget(m_pGLWidget);
    //模型
    m_pGLModelTest = new MModelTest(this);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(50);

    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);
    connect(ui->actiontest1, &QAction::triggered, this, &MMainWindow::slot_test1);
    connect(ui->actiontest2, &QAction::triggered, this, &MMainWindow::slot_test2);

    slot_test1(true);
}

MMainWindow::~MMainWindow()
{
    delete ui;
}

void MMainWindow::slot_timeout()
{

}

void MMainWindow::slot_test1(bool)
{
    //添加模型
    m_pGLScene->addModel(m_pGLModelTest->getModel());
    //刷新
    m_pGLWidget->update();
}

void MMainWindow::slot_test2(bool)
{

}

