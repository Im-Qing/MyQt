/*****************************************************************
* 文件名称： MString.h
* 说   明： 字符串相关功能
* 作   者： 王嘟嘟
* 日   期： 2022-06-13 20:29:44
* 版   本： v1.0
* 版权所有： Copyright By 王嘟嘟, All Rights Reserved
******************************************************************/

#ifndef MSTRING_H
#define MSTRING_H

#include "mcore_global.h"

#include <QString>

namespace NS_MCore
{
class MCORESHARED_EXPORT MString
{
public:
    explicit MString();
public:
    /**
     * @brief 判断输入的字符串是否为全英文
     * @param str
     * @return true:全英文  false:非全英文
     */
    bool isFullEnglish(const QString& str);
};
}

#endif // MSTRING_H
