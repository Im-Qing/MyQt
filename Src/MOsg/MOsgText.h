#ifndef MOSGTEXT_H
#define MOSGTEXT_H
#include "MOsg_global.h"
#include "MOsgNode.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgText : public MOsgNode
{
public:
    MOsgText(const QString& text, QObject *parent = nullptr);
public:
    void setText(const QString& text);
public:
    virtual const osg::BoundingBox& getBoundingBox() const;
private:
    osg::ref_ptr<osg::Geode> m_pGeode;
    osg::ref_ptr<osgText::Text> m_pTextNode;
};
}

#endif // MOSGTEXT_H
