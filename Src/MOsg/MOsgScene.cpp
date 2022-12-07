#include "MOsgScene.h"
#include "MOsgNode.h"

using namespace NS_MOsg;

char vertexShader[] = {
    "varying vec4 color;\n"
    "void main(void ){\n"
        "color = gl_Vertex;\n"
        "gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;\n"
    "}\n"
};
char fragShader[] = {
    "varying vec4 color;\n"
    "uniform vec4 mainColor;\n"
    "void main(void){\n"
    "	//gl_FragColor = clamp(color,0.0,1.0);\n"
    "   //color = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "	gl_FragColor = color;\n"
    "}\n"
};

MOsgScene::MOsgScene(QObject *parent) : QObject(parent) , osg::Group()
{
    setName("root");
}

void MOsgScene::addNode(MOsgNode *node)
{
    addChild(node->get());
}

void MOsgScene::test(const QString &filePath)
{
    //节点访问器
    if(false)
    {
        osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/axes.osgt");
        addChild(pNode.get());
        VertexExtractor ivea;
        pNode->accept(ivea);
    }

    //lod
    if(false)
    {
        osg::ref_ptr<osg::LOD> pNode = new osg::LOD;
        addChild(pNode.get());

        osg::ref_ptr<osg::Node> pNode1 = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/axes.osgt");
        pNode->addChild(pNode1.get(), 20, FLT_MAX);

        osg::ref_ptr<osg::Node> pNode2 = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt");
        pNode->addChild(pNode2.get(), 0, 20);
    }

    //代理节点
    if(false)
    {
        osg::ref_ptr<osg::ProxyNode> pNode = new osg::ProxyNode;
        addChild(pNode.get());

        pNode->setFileName(0, "../../Data/OpenSceneGraph-Data-3.0.0/axes.osgt");
        pNode->setFileName(1, "../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt");
    }

    //draw四边形
    if(false)
    {
        addChild(createQuad());
    }

    //内置几何体
    if(false)
    {
        addChild(createShape());
    }


    //pick
    if(false)
    {
//        MOsgEventHandler* pMOsgEventHandler = new MOsgEventHandler(this);
//        m_pViewer->addEventHandler(pMOsgEventHandler);
//        osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cessna.osgt") ;
//        osg::ref_ptr < osg::PositionAttitudeTransform > rot = new osg::PositionAttitudeTransform;
//        rot->setPosition(osg::Vec3(0.0, 0.0, 0.0));
//        rot->setAttitude(osg::Quat(osg::PI_2, osg::Vec3(0.0, 0.0, 1.0)));
//        rot ->addChild(cessna.get()) ;
//        addChild(rot.get());
//        osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt") ;
//        osg::ref_ptr<osgFX::Scribe> sc = new osgFX::Scribe();
//        sc->setWireframeColor(osg::Vec4(1, 0, 0, 1));
//        sc->setWireframeLineWidth(10);
//        sc->addChild(cow.get());
//        addChild(sc.get());
    }

    //着色器
    if(false)
    {
        osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt") ;
        osg::StateSet * ss = cow->getOrCreateStateSet();
        osg::Program * program = new osg::Program;
        program->addShader(new osg::Shader(osg::Shader::FRAGMENT,fragShader));
        program->addShader(new osg::Shader(osg::Shader::VERTEX,vertexShader));

        osg::ref_ptr<osg::Uniform> mainColor = new osg::Uniform("mainColor", osg::Vec4(1.0, 0.0, 1.0, 1.0));
        mainColor->setUpdateCallback(new MMainColorCallback);
        ss->addUniform(mainColor.get());

        ss->setAttributeAndModes(program/*,osg::StateAttribute::ON*/);
        addChild(cow.get());
    }


    //更新回调
    if(false)
    {
        osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt") ;
        osg::ref_ptr < osg::PositionAttitudeTransform > pat = new osg::PositionAttitudeTransform;
        pat->setUpdateCallback(new MRotateCallBack);
        //pat->addUpdateCallback(new InfoCallback);
        pat->addChild(cow.get());
        addChild(pat.get());
    }

    //更新回调
    if(false)
    {
        osg::ref_ptr<osg::Switch> pSw = new osg::Switch();

        osg::ref_ptr<osg::Node> pNode1 = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/cow.osgt");
        osg::ref_ptr < osg::MatrixTransform> trans = new osg::MatrixTransform ;
        trans ->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5)*osg::Matrix::translate(0, 0, 4)) ;
        trans ->addChild(pNode1.get()) ;
        pSw->addChild(trans.get(), false);

        osg::ref_ptr<osg::Node> pNode2 = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/glider.osgt");
        osg::ref_ptr < osg::MatrixTransform> scale = new osg::MatrixTransform ;
        scale ->setMatrix(osg::Matrix::scale(2.5, 2.5, 2.5)*osg::Matrix::translate(0, 0, -4)) ;
        scale ->addChild(pNode2.get()) ;
        pSw->addChild(scale.get(), false);

        osg::ref_ptr<osg::Node> pNode3 = osgDB::readNodeFile("../../Data/OpenSceneGraph-Data-3.0.0/robot.osg");
        osg::ref_ptr < osg::MatrixTransform > rot1 = new osg::MatrixTransform ;
        rot1 ->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0), 1, 0, 0)*osg::Matrix::scale(1, 1,
        1)*osg::Matrix::translate(4, 0, -2)) ;
        rot1 ->addChild(pNode3.get()) ;
        pSw->addChild(rot1.get(), false);

        //绘制正方形
        pSw->addChild(createQuad(), false);

        //绘制几何体
        pSw->addChild(createShape(), true);

        addChild(pSw.get());
    }
}

osg::ref_ptr<osg::Node> MOsgScene::createQuad()
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    //首先定义四个点
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    geom->setVertexArray( v.get() );
    v->push_back( osg::Vec3( -1.f, 0.f, -1.f ) );
    v->push_back( osg::Vec3( 1.f, 0.f, -1.f ) );
    v->push_back( osg::Vec3( 1.f, 0.f, 1.f ) );
    v->push_back( osg::Vec3( -1.f, 0.f, 1.f ) );
    //定义颜色数组
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    geom->setColorArray( c.get() );
    geom->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    c->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
    c->push_back( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
    //定义法线
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    geom->setNormalArray( n.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
    n->push_back( osg::Vec3( 0.f, -1.f, 0.f ) );
    //设置顶点关联方式
    geom->addPrimitiveSet(
    new osg::DrawArrays( osg::PrimitiveSet::QUADS, 0, 4 ) );

    //几何组结点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geom.get() );

    return geode.get();
}

osg::ref_ptr<osg::Node> MOsgScene::createShape()
{
    //几何组结点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    float radius = 0.08f;
    float height = 0.1f;

    osg::TessellationHints* hints = new osg::TessellationHints;
    hints->setDetailRatio(5.f);
    geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f,0.0f,0.0f),radius),hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.2f,0.0f,0.0f),2*radius),hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(0.4f,0.0f,0.0f),radius,height),hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0.60f,0.0f,0.0f),radius,height),hints));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(0.80f,0.0f,0.0f),radius,height),hints));
    return geode.get();
}
