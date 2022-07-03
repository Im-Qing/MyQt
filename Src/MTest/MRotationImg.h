#ifndef MROTATIONIMG_H
#define MROTATIONIMG_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class MRotationImg : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MRotationImg(const QString& imgSrc, QWidget *parent = nullptr);
    ~MRotationImg();
public:
    void setImgSize(int w, int h);
    void setImgRotation(qreal angle);
private:
    QGraphicsScene* m_pScene;
    QGraphicsRectItem* m_pItem;
    QString m_imgSrc;
};

#endif // MROTATIONIMG_H
