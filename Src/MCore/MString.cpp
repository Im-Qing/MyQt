#include "MString.h"

using namespace NS_MCore;

MString::MString()
{

}

bool NS_MCore::MString::isFullEnglish(const QString& str)
{
    QByteArray ba = str.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if((*s>='A' && *s<='Z') || (*s>='a' && *s<='z') || *s ==  ' ')
        {
        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}
