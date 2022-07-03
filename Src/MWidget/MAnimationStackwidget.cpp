#include "MAnimationStackwidget.h"

using namespace NS_MWidget;

MAnimationStackwidget::MAnimationStackwidget(QWidget *parent) :
    QStackedWidget(parent)
{
    m_pSwipeAnimation = new QPropertyAnimation(this, QByteArray());
    m_pSwipeAnimation->setDuration(250);
    m_pSwipeAnimation->setEasingCurve(QEasingCurve::InQuad);
    connect(m_pSwipeAnimation, &QPropertyAnimation::valueChanged, this, &MAnimationStackwidget::slot_valueChanged);
    connect(m_pSwipeAnimation, &QPropertyAnimation::finished, this, &MAnimationStackwidget::slot_animationFinished);
}

MAnimationStackwidget::~MAnimationStackwidget()
{

}

void MAnimationStackwidget::swipeForward()
{
    int curentPageIndex = currentIndex();
    m_nextPageIndex = curentPageIndex-1;
    //如果正在动画，那么return
    if( m_isAnimation )
    {
        return;
    }
    m_preOrNext = 0;
    m_isAnimation = true;
    //隐藏当前的widget
    widget(curentPageIndex)->hide();
    //开始动画并设置间隔和开始、结束值
    QRect g = geometry();
    int width = g.width();
    m_pSwipeAnimation->setStartValue(0);
    m_pSwipeAnimation->setEndValue(width);
    m_pSwipeAnimation->start();
}

void MAnimationStackwidget::swipeNext()
{
    //如果正在动画，那么return
    if( m_isAnimation )
    {
        return;
    }
    m_preOrNext = 1;
    m_isAnimation = true;
    widgetCount = count();
    int c = currentIndex();
    //计算下一页的索引
    m_nextPageIndex = (c + 1) % widgetCount;
    //隐藏当前的widget
    widget(c)->hide();
    //开始动画并设置间隔和开始、结束值
    QRect g = geometry();
    int x = g.x();
    int width = g.width();
    m_pSwipeAnimation->setStartValue(width);
    m_pSwipeAnimation->setEndValue(0);
    m_pSwipeAnimation->start();
}

void MAnimationStackwidget::slot_valueChanged(const QVariant &value)
{
    m_currentValue = value;
    update();
}

void MAnimationStackwidget::slot_animationFinished()
{
    m_isAnimation = false;
    widget(currentIndex())->show();
    setCurrentIndex(m_nextPageIndex);
}

void MAnimationStackwidget::paintEvent(QPaintEvent *event)
{
    if( m_isAnimation )
    {
        QPainter paint(this);
        int currentIndex = this->currentIndex();
        //绘制当前Widget
        paintPrevious(paint, currentIndex);
        //绘制下一个widget
        paintNext(paint, m_nextPageIndex);
    }
}

void MAnimationStackwidget::paintPrevious(QPainter &paint, int)
{
    //获得当前页面的Widget
    QWidget *w = widget(currentIndex());
    QPixmap pixmap(w->size());
    //将Widget的内容渲染到QPixmap对象中，即将Widget变成一张图片
    w->render(&pixmap);
    QRect r = w->geometry();
    //绘制当前的Widget
    double value = m_currentValue.toDouble();
    if(m_preOrNext == 0)
    {
        QRectF r1(value, 0.0, r.width() - value, r.height());
        QRectF r2(0, 0.0, r.width() - value, r.height());
        paint.drawPixmap(r1, pixmap, r2);
    }
    else if(m_preOrNext == 1)
    {
        QRectF r1(0.0, 0.0, value, r.height());
        QRectF r2(r.width() - value, 0, value, r.height());
        paint.drawPixmap(r1, pixmap, r2);
    }
}

void MAnimationStackwidget::paintNext(QPainter &paint, int)
{
    QWidget *nextWidget = widget(m_nextPageIndex);
    QRect r = geometry();
    //这行代码不加会有bug，第一次切换的时候，QStackedWidget并没有为child分配大小
    nextWidget->resize(r.width(), r.height());
    QPixmap nextPixmap(nextWidget->size());
    nextWidget->render(&nextPixmap);
    double value = m_currentValue.toDouble();
    if(m_preOrNext == 0)
    {
        QRectF r1(0, 0.0, value, r.height());
        QRectF r2(r.width() - value, 0.0, value, r.height());
        paint.drawPixmap(r1, nextPixmap, r2);
    }
    else if(m_preOrNext == 1)
    {
        QRectF r1(value, 0.0, r.width() - value, r.height());
        QRectF r2(0.0, 0.0, r.width() - value, r.height());
        paint.drawPixmap(r1, nextPixmap, r2);
    }
}
