#include "MMainWindow.h"
#include "ui_MMainWindow.h"

#include <QDebug>
#include <QTextCodec>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgText/Text>
#include <osg/DrawPixels>

#include "locale.h"

MMainWindow::MMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMainWindow)
{
    ui->setupUi(this);
    resize(1000, 600);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(50);
    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);

    m_pMOsgScene = new MOsgScene(this);
    m_pMOsgView = new MOsgView(m_pMOsgScene, this);
    m_pViewer = m_pMOsgView->getOsgViewer();
    ui->gridLayout->addWidget(m_pMOsgView);
    sample_cow();
    m_pMOsgScene->setOsgView(m_pMOsgView->getOsgViewer());

    connect(ui->actiontest1, &QAction::triggered, this, &MMainWindow::slot_test1);
    connect(ui->actiontest2, &QAction::triggered, this, &MMainWindow::slot_test2);
}

MMainWindow::~MMainWindow()
{
    delete ui;
}

void MMainWindow::sample_cow()
{
    //添加状态事件
    m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
    //窗口大小变化事件
    m_pViewer->addEventHandler(new osgViewer::WindowSizeHandler);
    //添加一些常用状态设置
    m_pViewer->addEventHandler(new osgViewer::StatsHandler);
    //添加一些操作器
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
        keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
        keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
        keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
        keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());
        m_pViewer->setCameraManipulator(keyswitchManipulator.get());
    }
    //添加路径记录
    m_pViewer->addEventHandler(new osgViewer::RecordCameraPathHandler);


    osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile("Data/OpenSceneGraph-Data-3.0.0/cow.osgt");

    //tran
    if(false)
    {
        osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
        rot->setPosition(osg::Vec3(2.0, 5.0, 0.0));
        rot->setAttitude(osg::Quat(osg::PI_2, osg::Vec3(0.0, 1.0, 1.0)));
        rot->setScale(osg::Vec3(0.1, 0.1, 0.1));
        rot->addChild(pNode.get());
        m_pMOsgScene->addChild(rot.get());
    }
    //显示文字
    //if (false)
    {
        osgText::Font* font1 = osgText::readFontFile("Data/OpenSceneGraph-Data-3.0.0/fonts/FZSTK.TTF");
        osg::Geode* geode = new osg::Geode;
        m_pMOsgScene->addChild(geode);

        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setFont(font1);
        text->setPosition(osg::Vec3(3.0, 0.0, 0.0));
        text->setCharacterSize(50.f);
        text->setAxisAlignment(osgText::Text::XZ_PLANE);
        //text->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX | osgText::Text::FILLEDBOUNDINGBOX);

        QString str = QString::fromLocal8Bit("qwer显示文字");


        text->setText(str.toStdWString().c_str());
        geode->addDrawable(text);
    }
    //显示图片
    if (false)
    {
        osg::Geode* geode = new osg::Geode();

        osg::StateSet* stateset = geode->getOrCreateStateSet();

        osg::ref_ptr<osg::Image> image = osgDB::readRefImageFile("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
        if (image)
        {
            osg::Texture2D* texture = new osg::Texture2D;
            texture->setImage(image);
            texture->setMaxAnisotropy(8);
            stateset->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
        }

        osg::Material* material = new osg::Material;
        stateset->setAttribute(material);

        // the globe
        geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.2f,0.0f,0.0f),2*2)));

        m_pMOsgScene->addChild(geode);
    }
}

void MMainWindow::slot_timeout()
{
    
}

void MMainWindow::slot_test1(bool)
{
    sample_cow();
}

void MMainWindow::slot_test2(bool)
{

}

