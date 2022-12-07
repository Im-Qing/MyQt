#ifndef MOSGLINE_H
#define MOSGLINE_H
#include "MOsgNode.h"

namespace NS_MOsg
{

class MOsgScene;

class MOSG_EXPORT MOsgLine : public MOsgNode
{
    Q_OBJECT
public:
    explicit MOsgLine(int id, QObject *parent = nullptr);
public:
    void setLineColor(osg::Vec4 rgba);
    void setLineWidth(int width);
    void setLineVertexArray(const QList<MPos>& vex);
private:
    int m_id;
    osg::ref_ptr<osg::Geometry> m_pGeometry;
};
}

#endif // MOSGLINE_H
