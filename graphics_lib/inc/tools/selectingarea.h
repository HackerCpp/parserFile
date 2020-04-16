#ifndef SELECTINGAREA_H
#define SELECTINGAREA_H
#include <QGraphicsItem>

class SelectingArea : public QGraphicsItem
{
    QRectF m_rect;
public:
    SelectingArea(QRectF rect);
    ~SelectingArea();

    void setWidth(int newWidth){m_rect.setWidth(newWidth);}
    void setHeight(int newHeight){m_rect.setHeight(newHeight);}
    void setPosition(QPointF newPos){QGraphicsItem::prepareGeometryChange();m_rect.setX(newPos.x());m_rect.setY(newPos.y());}

    int width(){return m_rect.width();}
    int height(){return m_rect.height();}

    int left();
    int right();
    int top();
    int bottom();

    virtual QRectF boundingRect()const override{return m_rect;}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
};

#endif // SELECTINGAREA_H
