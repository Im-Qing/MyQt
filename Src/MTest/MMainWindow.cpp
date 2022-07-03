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

//    m_pRotationImg = new MRotationImg("://Res/invite_people_nor.svg", this);
//    m_pRotationImg->setImgSize(30,30);
//    ui->gridLayout_2->addWidget(m_pRotationImg);

//    m_pTimer = new QTimer(this);
//    m_pTimer->start(50);
//    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);
}

MMainWindow::~MMainWindow()
{
    delete ui;
}

void MMainWindow::slot_timeout()
{
    static float angle = 0.0;
    m_pRotationImg->setImgRotation(angle);
    angle += 10;
}

