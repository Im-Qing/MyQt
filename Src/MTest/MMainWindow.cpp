#include "MMainWindow.h"
#include "ui_MMainWindow.h"

#include <QDebug>

MMainWindow::MMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMainWindow)
{
    ui->setupUi(this);
    resize(1000, 600);

    m_pMGLWidget = new MGLWidget(this);
    ui->gridLayout->addWidget(m_pMGLWidget);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(50);
    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);

    connect(ui->actiontest1, &QAction::triggered, this, &MMainWindow::slot_test1);
    connect(ui->actiontest2, &QAction::triggered, this, &MMainWindow::slot_test2);
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

}

void MMainWindow::slot_test2(bool)
{

}

