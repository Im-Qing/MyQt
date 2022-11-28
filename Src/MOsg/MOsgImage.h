#ifndef MOSGIMAGE_H
#define MOSGIMAGE_H
#include "MOsg_global.h"
#include "MOsgNode.h"

namespace NS_MOsg
{
class MOSG_EXPORT MOsgImage : public MOsgNode
{
    Q_OBJECT
public:
    explicit MOsgImage(const QString& filePath, QObject *parent = nullptr);
};
}

#endif // MOSGIMAGE_H
