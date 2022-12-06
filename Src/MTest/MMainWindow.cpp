#include "MMainWindow.h"
#include "ui_MMainWindow.h"

#include <QDebug>
#include <QTextCodec>

#include "MOsg/MOsgImage.h"
#include "MOsg/MOsgText.h"
#include "MOsg/MOsgModel.h"
#include "MOsg/MOsgLine.h"

MMainWindow::MMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MMainWindow)
{
    ui->setupUi(this);
    resize(1000, 600);

    m_pTimer = new QTimer(this);
    //m_pTimer->start(50);
    connect(m_pTimer, &QTimer::timeout,this,&MMainWindow::slot_timeout);

    m_pMOsgScene = new MOsgScene(false, this);
    m_pMOsgWidget = new MOsgWidget(m_pMOsgScene, this);
    m_pViewer = m_pMOsgWidget->getOsgViewer();
    ui->gridLayout->addWidget(m_pMOsgWidget);
    sample_cow();

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
    if (false)
    {
        //整个模型，文字加模型
        osg::ref_ptr<osg::Group> pModel = new osg::Group;
        m_pMOsgScene->addChild(pModel.get());

        //尺寸，长宽高
        float v_ = 1.0;
        float len = v_;
        float width = v_;
        float height = v_;
        float percent = 0.1;

        //lod节点
        osg::ref_ptr<osg::LOD> pLodNode = new osg::LOD;
        pModel->addChild(pLodNode.get());

        //3D模型
        {
            pNode->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
            pNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
            osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
            rot->addChild(pNode.get());

            osg::ComputeBoundsVisitor boundVisitor;
            pNode->accept(boundVisitor);
            osg::BoundingBox boundingBox = boundVisitor.getBoundingBox();

            float x__ = boundingBox.xMax() - boundingBox.xMin();
            float y__ = boundingBox.yMax() - boundingBox.yMin();
            float z__ = boundingBox.zMax() - boundingBox.zMin();
            float cx = boundingBox.center().x();
            float cy = boundingBox.center().y();
            float cz = boundingBox.center().z();

            qDebug()<<"x__: "<<x__;
            qDebug()<<"y__: "<<y__;
            qDebug()<<"z__: "<<z__;
            qDebug()<<"cx: "<<cx;
            qDebug()<<"cy: "<<cy;
            qDebug()<<"cz: "<<cz;


            float zScale = v_ / z__;
            qDebug()<<"zScale : "<<zScale;

            osg::BoundingSphere bb = pNode->getBound();
            float scale = v_ / bb.radius();
            qDebug()<<"radius : "<<bb.radius();
            qDebug()<<"scale : "<<scale;
            rot->setPosition(osg::Vec3(-0, 0, 0));
            rot->setScale(osg::Vec3(zScale, zScale, zScale));
            pLodNode->addChild(rot.get(), 0, 30);
        }
        //图片
        {
            osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
            //首先定义四个点
            osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
            geom->setVertexArray( v.get() );
            v->push_back( osg::Vec3( -0.5f, 0.f, -0.5f ) );
            v->push_back( osg::Vec3( 0.5f, 0.f, -0.5f ) );
            v->push_back( osg::Vec3( 0.5f, 0.f, 0.5f ) );
            v->push_back( osg::Vec3( -0.5f, 0.f, 0.5f ) );
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
            spStateSet->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
            //要想看到png图片的透明效果，需要开启混合模式
            spStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
            spStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
            //设置顶点关联方式
            geom->addPrimitiveSet(new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

            //几何组结点
            osg::ref_ptr<osg::Geode> geode = new osg::Geode;
            geode->addDrawable( geom.get() );
            pLodNode->addChild(geode.get(), 30, FLT_MAX);
        }
        //文字
        {
            osg::Geode* geode = new osg::Geode;
            geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
            osgText::Font* font1 = osgText::readFontFile("Data/OpenSceneGraph-Data-3.0.0/fonts/FZSTK.TTF");
            osg::ref_ptr<osgText::Text> text = new osgText::Text;
            text->setFont(font1);
            text->setCharacterSize(0.25f);
            text->setAxisAlignment(osgText::Text::XZ_PLANE);
            text->setAlignment(osgText::Text::CENTER_CENTER);
            //text->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX | osgText::Text::FILLEDBOUNDINGBOX);
            QString str = QString::fromLocal8Bit("徐凯旋宝宝");
            text->setText(str.toStdWString().c_str());
            geode->addDrawable(text);


            osg::BoundingBox boundingBox = geode->getBoundingBox();

            float x__ = boundingBox.xMax() - boundingBox.xMin();
            float y__ = boundingBox.yMax() - boundingBox.yMin();
            float z__ = boundingBox.zMax() - boundingBox.zMin();
            float cx = boundingBox.center().x();
            float cy = boundingBox.center().y();
            float cz = boundingBox.center().z();

            qDebug()<<"x__: "<<x__;
            qDebug()<<"y__: "<<y__;
            qDebug()<<"z__: "<<z__;
            qDebug()<<"cx: "<<cx;
            qDebug()<<"cy: "<<cy;
            qDebug()<<"cz: "<<cz;

            text->setPosition(osg::Vec3(0.0, 0.0, -(v_/2 + z__)));

//            osg::AutoTransform* at = new osg::AutoTransform;
//            at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
//            at->setAutoScaleToScreen(true);
//            at->setMinimumScale(0);
//            at->setMaximumScale(FLT_MAX);
//            //at->setPosition(osg::Vec3(0.0, 0.0, -(v_/2 + z__)));
//            at->addChild(geode);

            pModel->addChild(geode);
        }
    }
    //线
    if (false)
    {
        osg::ref_ptr<osg::Geode> geode = new osg::Geode;
        m_pMOsgScene->addChild(geode.get());
        //设置顶点数组
        osg::ref_ptr<osg::Vec3Array> vex = new osg::Vec3Array;
        vex->push_back(osg::Vec3(-3.0, 0.0, 0.0));
        vex->push_back(osg::Vec3(3.0, 0.0, 0.0));
        vex->push_back(osg::Vec3(0.0, 5.0, 0.0));
        vex->push_back(osg::Vec3(0.0, 0.0, 5.0));

        osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
        geometry->setVertexArray(vex);

        //设置颜色数组
        osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

        colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 0.5));
        geometry->setColorArray(colors);
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

        //设置顶点关联方式
        geometry->addPrimitiveSet(new osg::DrawArrays( osg::PrimitiveSet::LINE_LOOP, 0, 4 ) );

        //设置线宽
        osg::ref_ptr<osg::LineWidth> lw = new osg::LineWidth(6.0);
        geometry->getOrCreateStateSet()->setAttribute(lw, osg::StateAttribute::ON);
        geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

        geode->addDrawable(geometry);
    }

    //图片类测试
    if(false)
    {
        MOsgImage* pImage = new MOsgImage("", this);
        pImage->setImageFile("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
        m_pMOsgScene->addNode(pImage);
        pImage->setPos(osg::Vec3(0.0, 0.0, 0.0));
    }
    //文本类测试
    if(false)
    {
        MOsgText* pText = new MOsgText(QString::fromLocal8Bit("葵宝宝"));
        m_pMOsgScene->addNode(pText);
        pText->setPos(osg::Vec3(1.5, 0.0, 0.0));
    }
    //模型类测试
    if(false)
    {
        MOsgModel* pModel = new MOsgModel(1, this);
        pModel->setName(QString::fromLocal8Bit("葵宝宝"));
        pModel->set2DImg("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
        pModel->set3DModel("Data/OpenSceneGraph-Data-3.0.0/cow.osgt");
        m_pMOsgScene->addNode(pModel);
        pModel->setScale(osg::Vec3(2.0, 2.0, 2.0));
        pModel->setPos(osg::Vec3(4.0, 0.0, 0.0));
    }
    //线类测试
    if(false)
    {
        MOsgLine* pLine = new MOsgLine(1, this);
        m_pMOsgScene->addNode(pLine);
        //设置顶点数组
        osg::ref_ptr<osg::Vec3Array> vex = new osg::Vec3Array;
        vex->push_back(osg::Vec3(-3.0, 0.0, 0.0));
        vex->push_back(osg::Vec3(3.0, 0.0, 0.0));
        vex->push_back(osg::Vec3(0.0, 5.0, 0.0));
        vex->push_back(osg::Vec3(0.0, 0.0, 5.0));
        pLine->setLineVertexArray(vex);
        //设置颜色
        pLine->setLineColor(osg::Vec4(28.0/255, 116.0/255, 28.0/255, 1.0));
        //设置线宽
        pLine->setLineWidth(2);
    }
    //地球类测试
    //if(false)
    {
        //地球节点
        m_pMOsgScene->setEarthFilePath("Data/OpenSceneGraph-Data-3.0.0/Images/land_shallow_topo_2048.jpg");

        //在北京位置添加模型
        MOsgModel* pModel = new MOsgModel(1, this);
        pModel->setName(QString::fromLocal8Bit("葵宝宝"));
        pModel->set2DImg("Data/OpenSceneGraph-Data-3.0.0/Images/osg64.png");
        pModel->set3DModel("Data/OpenSceneGraph-Data-3.0.0/cow.osgt");
        m_pMOsgScene->addNode(pModel);
        pModel->setScale(osg::Vec3(300000.0f, 300000.0f, 300000.0f));
        pModel->setPos(osg::Vec3(116.23128, 40.22077, 200000.0));

        //绘制线
        MOsgLine* pLine = new MOsgLine(2, this);
        m_pMOsgScene->addNode(pLine);
        //设置顶点数组
        osg::ref_ptr<osg::Vec3Array> vex = new osg::Vec3Array;
        for(int i = -180; i<=180; i+=2)
        {
            vex->push_back(osg::Vec3(116.23128, i*1.0, 1000000.0));
        }
        pLine->setLineVertexArray(vex);
        //设置颜色
        pLine->setLineColor(osg::Vec4(1.0, 1.0, 0.0, 1.0));
        //设置线宽
        pLine->setLineWidth(2);
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

