#include "primitive.h"

Primitive::Primitive()
    :m_drawType(DRAW_NONE),m_points(nullptr)
{

}

void Primitive::setPoints(QList<QPointF> *points){
    if(m_points){delete m_points; m_points = nullptr;}
    m_points = points;
}

void Primitive::addPoint(QPointF point){
    if(!m_points)
        m_points = new QList<QPointF>();
    m_points->push_back(point);
}

Primitive::~Primitive(){
    if(m_points){delete m_points; m_points = nullptr;}
}
