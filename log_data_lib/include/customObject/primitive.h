#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <QList>
#include <QPointF>

enum DrawType{DRAW_NONE,DRAW_LINE,DRAW_LINE_PATH,
              DRAW_CIRCLE,DRAW_RECTANGLE,DRAW_POINT,DRAW_TEXT};

class Primitive{
    DrawType m_drawType;
    QList<QPointF> *m_points;
public:
    Primitive();
    ~Primitive();

    void setDrawType(DrawType type){m_drawType = type;}
    void setPoints(QList<QPointF> *points);
    void addPoint(QPointF point);

    DrawType type(){return m_drawType;}
};











#endif
