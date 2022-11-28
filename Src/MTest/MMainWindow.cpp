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
    m_pMOsgWidget = new MOsgWidget(m_pMOsgScene, this);
    m_pViewer = m_pMOsgWidget->getOsgViewer();
    ui->gridLayout->addWidget(m_pMOsgWidget);
    sample_cow();
    m_pMOsgScene->setOsgView(m_pMOsgWidget->getOsgViewer());

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

        osg::BoundingSphere bb = rot->getBound();
        qDebug()<<"radius : "<<bb.radius();
    }
    //显示文字
    if (false)
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
        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
        //首先定义四个点
        osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
        geom->setVertexArray( v.get() );
        v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
        v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
        v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
        v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );
//        //定义颜色数组
//        osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
//        geom->setColorArray( c.get() );
//        geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
//        c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
//        c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
//        c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
//        c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
        //定义纹理坐标
        osg::ref_ptr<osg::Image> spImage = osgDB::readImageFile("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
        osg::ref_ptr <osg::Texture2D> spTexture2D = new osg::Texture2D(spImage);
        osg::ref_ptr<osg::Vec2Array> spCoordArray = new osg::Vec2Array();
        spCoordArray->push_back(osg::Vec2(0.0, 1.0));
        spCoordArray->push_back(osg::Vec2(0.0, 0));
        spCoordArray->push_back(osg::Vec2(1.0, 0.0));
        spCoordArray->push_back(osg::Vec2(1.0, 1.0));

        geom->setTexCoordArray(0, spCoordArray);
        spTexture2D->setUnRefImageDataAfterApply(true);
        osg::ref_ptr<osg::StateSet> spStateSet = geom->getOrCreateStateSet();
        spStateSet->setTextureAttributeAndModes(0, spTexture2D);
        spStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        //要想看到png图片的透明效果，需要开启混合模式
        spStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
        spStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        //设置顶点关联方式
        geom->addPrimitiveSet(
                    new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

        //几何组结点
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        geode->addDrawable( geom.get() );
        m_pMOsgScene->addChild(geode);

        osg::BoundingBox bb = geode->getBoundingBox();
        qDebug()<<"x : "<<bb.xMax() - bb.xMin();
        qDebug()<<"y : "<<bb.yMax() - bb.yMin();
        qDebug()<<"z : "<<bb.zMax() - bb.zMin();

        //调整相机，使模型居中显示
        double radius = geode->getBoundingBox().xMax() - geode->getBoundingBox().xMin();
        double viewDistance = radius/5;//

        //方向向上
        osg::Vec3d up( 0.0,0.0,1.0 );//osg右x,前y,上z,opengl由osg绕x轴向外旋转90°,
        //
        osg::Vec3d viewDirection( 0.0,-1.0,0.5 );//
        //相机盯着的那个点（目标点，相当于靶心），不一定就是包围球的中点，也可以是场景的原点，这个看情况
        osg::Vec3d center = geode->getBound().center();
        //眼睛的位置=目标点+离目标点的距离
        osg::Vec3d eye = center + viewDirection * viewDistance;
        //相机设置矩阵
        //m_pViewer->getCameraManipulator()->setHomePosition(eye,center,up);
        m_pViewer->home();
    }
    //文字加模型，能设置模型尺寸
    //if (false)
    {
        //整个模型，文字加模型
        osg::ref_ptr<osg::Group> pModel = new osg::Group;
        m_pMOsgScene->addChild(pModel.get());

        //尺寸，长宽高
        float v = 0.3;
        float len = v;
        float width = v;
        float height = v;

        //lod节点
        osg::ref_ptr<osg::LOD> pLodNode = new osg::LOD;
        pModel->addChild(pLodNode.get());

        //3D模型
        {
            osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
            rot->addChild(pNode.get());
            osg::BoundingSphere bb = pNode->getBound();
            float scale = width / bb.radius();
            qDebug()<<"radius : "<<bb.radius();
            qDebug()<<"scale : "<<scale;
            rot->setScale(osg::Vec3(scale, scale, scale));
            pLodNode->addChild(rot.get(), 0, 10);
        }
        //图片
        {
            osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
            //首先定义四个点
            osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
            geom->setVertexArray( v.get() );
            v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
            v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
            v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
            v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );
            //定义纹理坐标
            osg::ref_ptr<osg::Image> spImage = osgDB::readImageFile("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
            osg::ref_ptr <osg::Texture2D> spTexture2D = new osg::Texture2D(spImage);
            osg::ref_ptr<osg::Vec2Array> spCoordArray = new osg::Vec2Array();
            spCoordArray->push_back(osg::Vec2(0.0, 1.0));
            spCoordArray->push_back(osg::Vec2(0.0, 0));
            spCoordArray->push_back(osg::Vec2(1.0, 0.0));
            spCoordArray->push_back(osg::Vec2(1.0, 1.0));

            geom->setTexCoordArray(0, spCoordArray);
            spTexture2D->setUnRefImageDataAfterApply(true);
            osg::ref_ptr<osg::StateSet> spStateSet = geom->getOrCreateStateSet();
            spStateSet->setTextureAttributeAndModes(0, spTexture2D);
            spStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
            //要想看到png图片的透明效果，需要开启混合模式
            spStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
            spStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
            //设置顶点关联方式
            geom->addPrimitiveSet(new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

            //几何组结点
            osg::ref_ptr<osg::Geode> geode = new osg::Geode;
            geode->addDrawable( geom.get() );

            osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
            rot->addChild(geode.get());
            rot->setAttitude(osg::Quat(osg::PI_2, osg::Vec3(0.0, 0.0, 0.0)));
            float textHeight = height;
            osg::BoundingBox bb = geode->getBoundingBox();
            qDebug()<<"x : "<<bb.xMax() - bb.xMin();
            qDebug()<<"y : "<<bb.yMax() - bb.yMin();
            qDebug()<<"z : "<<bb.zMax() - bb.zMin();
            float zScale = textHeight / (bb.zMax() - bb.zMin());
            //rot->setPosition(osg::Vec3(-(tarXWidth / 2), 0.0, -height));
            rot->setScale(osg::Vec3(zScale, zScale, zScale));

            pLodNode->addChild(rot.get(), 10, FLT_MAX);
        }
        //文字
        {
            osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
            rot->setAttitude(osg::Quat(osg::PI_2, osg::Vec3(0.0, 0.0, 0.0)));

            osg::Geode* geode = new osg::Geode;
            rot->addChild(geode);
            osgText::Font* font1 = osgText::readFontFile("Data/OpenSceneGraph-Data-3.0.0/fonts/FZSTK.TTF");
            osg::ref_ptr<osgText::Text> text = new osgText::Text;
            text->setFont(font1);
            text->setPosition(osg::Vec3(0.0, 0.0, 0.0));
            text->setCharacterSize(10.f);
            text->setAxisAlignment(osgText::Text::XZ_PLANE);
            //text->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX | osgText::Text::FILLEDBOUNDINGBOX);
            QString str = QString::fromLocal8Bit("徐凯旋宝宝");
            text->setText(str.toStdWString().c_str());
            geode->addDrawable(text);
            pModel->addChild(rot);

            float textHeight = height / 3;
            osg::BoundingBox bb = geode->getBoundingBox();
            qDebug()<<"x : "<<bb.xMax() - bb.xMin();
            qDebug()<<"y : "<<bb.yMax() - bb.yMin();
            qDebug()<<"z : "<<bb.zMax() - bb.zMin();
            float tarXWidth = ((bb.xMax() - bb.xMin()) / (bb.zMax() - bb.zMin()) * textHeight);
            float zScale = textHeight / (bb.zMax() - bb.zMin());
            float xScale = tarXWidth / (bb.xMax() - bb.xMin());
            qDebug()<<"xScale : "<<xScale;
            qDebug()<<"zScale : "<<zScale;
            rot->setPosition(osg::Vec3(-(tarXWidth / 2), 0.0, -height));
            rot->setScale(osg::Vec3(xScale, zScale, zScale));
        }
    }

    m_pViewer->home();
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

