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
};
}

#endif // MOSGTEXT_H
