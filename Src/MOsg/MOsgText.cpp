#include "MOsgText.h"

using namespace NS_MOsg;

NS_MOsg::MOsgText::MOsgText(const QString &text, QObject *parent) : MOsgNode(parent)
{
    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font = osgText::readFontFile("Data/OpenSceneGraph-Data-3.0.0/fonts/FZSTK.TTF");
    osg::ref_ptr<osgText::Text> pText = new osgText::Text;
    pText->setFont(font);
    pText->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    pText->setCharacterSize(10.f);
    pText->setAxisAlignment(osgText::Text::XZ_PLANE);
    //pText->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX | osgText::Text::FILLEDBOUNDINGBOX);
    pText->setText(text.toStdWString().c_str());
    pGeode->addDrawable(pText.get());
    //加到变换节点
    m_pTransform->addChild(pGeode.get());
}
