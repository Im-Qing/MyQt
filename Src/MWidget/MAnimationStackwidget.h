/*****************************************************************
* 文件名称： MAnimationStackwidget.h
* 说   明： 带有切换动画的栈式窗口
* 作   者： 王嘟嘟
* 日   期： 2022-06-13 20:34:21
* 版   本： v1.0
* 版权所有： Copyright By 王嘟嘟, All Rights Reserved
******************************************************************/

#ifndef MANIMATIONSTACKWIDGET_H
#define MANIMATIONSTACKWIDGET_H

#include "mwidget_global.h"

#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

namespace NS_MWidget
{
class MWIDGETSHARED_EXPORT MAnimationStackwidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit MAnimationStackwidget(QWidget *parent = nullptr);
    ~MAnimationStackwidget();
public:
    //下一页
    void swipeForward();
    //前一页
    void swipeNext();
public slots:
    void slot_valueChanged(const QVariant &value);
    void slot_animationFinished();
protected:
    void paintEvent(QPaintEvent *event);
private:
    void paintPrevious(QPainter &, int);
    void paintNext(QPainter &, int);
private:
    QPropertyAnimation* m_pSwipeAnimation;      //切换动画
    bool m_isAnimation = false;                 //是否正在动画
    QVariant m_currentValue;                    //被Animation动画改变的值
    int m_nextPageIndex;
    int         widgetCount;
    int m_preOrNext;            //0:上一页  1:下一页
};
}

#endif // MANIMATIONSTACKWIDGET_H
