#ifndef HEADERITEM_H
#define HEADERITEM_H
#include <QGraphicsItem>

class HeaderItem : public QGraphicsItem{
    QImage *m_img;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QRectF boundingRect()const override;
public:
    HeaderItem(QImage *img);
};

#endif // HEADERITEM_H
