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
    void setCurrentPosition(QPointF newPos);

    int width(){return m_rect.width();}
    int height(){return m_rect.height();}

    int left();
    int right();
    int top();
    int bottom();

    QPointF lefTop(){return QPointF(m_rect.x(),m_rect.y());}
    QPointF rightDown(){return QPointF(m_rect.x() + m_rect.width(),m_rect.y() + m_rect.height());}

    virtual QRectF boundingRect()const override{return m_rect;}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
};

#endif // SELECTINGAREA_H
