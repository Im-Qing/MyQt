#include "MRotationImg.h"

MRotationImg::MRotationImg(const QString& imgSrc, QWidget *parent) :
    QGraphicsView(parent)
    ,m_imgSrc(imgSrc)
{
    setStyleSheet("background:transparent; border:transparent;");

    m_pScene = new QGraphicsScene(this);
    setScene(m_pScene);

    setRenderHint(QPainter::Antialiasing);     //绘图抗锯齿
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //去掉滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignCenter);

    m_pItem = new QGraphicsRectItem();
    m_pItem->setPen(QPen(Qt::NoPen));
    m_pScene->addItem(m_pItem);

    setImgSize(40, 40);
}

MRotationImg::~MRotationImg()
{

}

void MRotationImg::setImgSize(int w, int h)
{
    m_pItem->setRect(0, 0, w, h);
    QPixmap pixmap(m_imgSrc);
    m_pItem->setBrush(QBrush(pixmap.scaled(w, h)));
}

void MRotationImg::setImgRotation(qreal angle)
{
    QRectF rect = m_pItem->rect();
    m_pItem->setTransformOriginPoint(QPointF(rect.x(), rect.y())+QPointF(rect.width()/2, rect.height()/2));
    m_pItem->setRotation(angle);
}
