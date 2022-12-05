#include "MOsgText.h"

using namespace NS_MOsg;

NS_MOsg::MOsgText::MOsgText(const QString &text, QObject *parent) : MOsgNode(parent)
{
    m_pGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font = osgText::readFontFile("Data/OpenSceneGraph-Data-3.0.0/fonts/FZSTK.TTF");
    m_pTextNode = new osgText::Text;
    m_pTextNode->setFont(font);
    m_pTextNode->setPosition(osg::Vec3(0.0, 0.0, 0.0));
    m_pTextNode->setCharacterSize(0.25f);
    m_pTextNode->setAxisAlignment(osgText::Text::XZ_PLANE);
    m_pTextNode->setAlignment(osgText::Text::CENTER_CENTER);
    //pText->setDrawMode(osgText::Text::TEXT | osgText::Text::ALIGNMENT | osgText::Text::BOUNDINGBOX | osgText::Text::FILLEDBOUNDINGBOX);
    m_pTextNode->setText(text.toStdWString().c_str());
    m_pGeode->addDrawable(m_pTextNode.get());
    //加到变换节点
    m_pTransform->addChild(m_pGeode.get());
}

void MOsgText::setText(const QString &text)
{
    m_pTextNode->setText(text.toStdWString().c_str());
}

const osg::BoundingBox &MOsgText::getBoundingBox() const
{
    return m_pGeode->getBoundingBox();
}
