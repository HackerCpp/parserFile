#include "chartviewselectsegment.h"
#include <QDebug>
#include <QScopedPointer>


ChartViewSelectSegment::ChartViewSelectSegment(QWidget *parent)
    :QChartView(parent)
{
    m_isActiveLeftLine = m_isActiveRightLine = m_isActiveHLine = false;
    m_verticalLineLeft = new QGraphicsLineItem;
    m_verticalLineRight = new QGraphicsLineItem;
    m_horizontalLine = new QGraphicsLineItem;

    QPen f_penH(QPen(Qt::white,1,Qt::DashLine));
    QPen f_penV(QPen(Qt::yellow,2,Qt::DotLine));
    m_verticalLineLeft->setPen(f_penV);
    m_verticalLineLeft->setZValue(100);
    m_verticalLineRight->setPen(f_penV);
    m_verticalLineRight->setZValue(100);
    m_horizontalLine->setPen(f_penH);
    m_horizontalLine->setZValue(100);

    m_verticalLineLeft->setLine(width() / 3,0,width() / 3,height());
    m_verticalLineRight->setLine(width() - width()/3,0,width() - width()/3,height());
    m_horizontalLine->setLine(0,height() / 2,width(),height() / 2);
    if(scene()){
        scene()->addItem(m_verticalLineLeft);
        scene()->addItem(m_verticalLineRight);
        scene()->addItem(m_horizontalLine);
    }

}

void ChartViewSelectSegment::mousePressEvent(QMouseEvent *event){
    prevPoint = event->pos();
    if(event->button() == Qt::LeftButton){
        qreal f_errorCoord = 4;
        if(event->pos().x() >= m_verticalLineLeft->line().x1() - f_errorCoord &&
            event->pos().x() <= m_verticalLineLeft->line().x1() + f_errorCoord ){
            m_isActiveLeftLine = true;
        }
        else if(event->pos().x() >= m_verticalLineRight->line().x1() - f_errorCoord &&
                event->pos().x() <= m_verticalLineRight->line().x1() + f_errorCoord ){
            m_isActiveRightLine = true;

        }
        if(event->pos().y() >= m_horizontalLine->line().y1() - f_errorCoord &&
                event->pos().y() <= m_horizontalLine->line().y1() + f_errorCoord ){
            m_isActiveHLine = true;
        }
    }
    else if(event->button() == Qt::RightButton){
        int f_posX = event->pos().x();
        int f_posY = event->pos().y();
        m_verticalLineLeft->setLine(f_posX,0,f_posX,height());

        m_verticalLineRight->setLine(f_posX,0,f_posX,height());
        m_horizontalLine->setLine(0,f_posY,width(),f_posY);
        QPointF f_pos = event->pos();
        m_positionLeftLine = chart()->mapToValue(f_pos);
        m_positionRightLine = chart()->mapToValue(f_pos);
        m_positionHLine = chart()->mapToValue(f_pos);
    }
}

void ChartViewSelectSegment::mouseMoveEvent(QMouseEvent *event){
    QPoint f_delta = event->pos() - prevPoint;
    qreal f_errorCoord = 4;
    if(m_isActiveHLine){
        int f_newPosY = m_horizontalLine->line().y1() + f_delta.y();
        m_positionHLine = chart()->mapToValue(QPointF(0,f_newPosY));
        m_horizontalLine->setLine(0,f_newPosY,width(),f_newPosY);
    }
    if(m_isActiveLeftLine){
        int f_newPosX = m_verticalLineLeft->line().x1() + f_delta.x();
        m_positionLeftLine = chart()->mapToValue(QPointF(f_newPosX,0));
        m_verticalLineLeft->setLine(f_newPosX,0,f_newPosX,height());
    }
    else if(m_isActiveRightLine){
        int f_newPosX = m_verticalLineRight->line().x1() + f_delta.x();
        m_positionRightLine = chart()->mapToValue(QPointF(f_newPosX,0));
        m_verticalLineRight->setLine(f_newPosX,0,f_newPosX,height());
    }
    else if(((event->pos().x() >= m_verticalLineLeft->line().x1() - f_errorCoord &&
              event->pos().x() <= m_verticalLineLeft->line().x1() + f_errorCoord) ||
              (event->pos().x() >= m_verticalLineRight->line().x1() - f_errorCoord &&
                          event->pos().x() <= m_verticalLineRight->line().x1() + f_errorCoord)
              ) && (event->pos().y() >= m_horizontalLine->line().y1() - f_errorCoord &&
                    event->pos().y() <= m_horizontalLine->line().y1() + f_errorCoord)){
        setCursor(QCursor(Qt::SizeAllCursor));
    }
    else if((event->pos().x() >= m_verticalLineLeft->line().x1() - f_errorCoord &&
            event->pos().x() <= m_verticalLineLeft->line().x1() + f_errorCoord) ||
            (event->pos().x() >= m_verticalLineRight->line().x1() - f_errorCoord &&
                        event->pos().x() <= m_verticalLineRight->line().x1() + f_errorCoord)
            ){
        setCursor(QCursor(Qt::SplitHCursor));
    }
    else if(event->pos().y() >= m_horizontalLine->line().y1() - f_errorCoord &&
            event->pos().y() <= m_horizontalLine->line().y1() + f_errorCoord){
        setCursor(QCursor(Qt::SplitVCursor));
    }
    else{
        setCursor(QCursor(Qt::ArrowCursor));
    }
    prevPoint = event->pos();
}

void ChartViewSelectSegment::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event)
    if(m_isActiveLeftLine){
        m_isActiveLeftLine = false;
    }
    if(m_isActiveRightLine){
        m_isActiveRightLine = false;
    }
    if(m_isActiveHLine){
        m_isActiveHLine = false;
    }

}

qreal ChartViewSelectSegment::posLeftLine(){
    return   m_positionLeftLine.x() < m_positionRightLine.x() ? m_positionLeftLine.x() : m_positionRightLine.x();
}

qreal ChartViewSelectSegment::posRightLine(){
    return   m_positionLeftLine.x() > m_positionRightLine.x() ? m_positionLeftLine.x() : m_positionRightLine.x();
}

void ChartViewSelectSegment::resize(){
    int f_leftLineX = chart()->mapToPosition(m_positionLeftLine).x();
    int f_rightLineX = chart()->mapToPosition(m_positionRightLine).x();
    int f_vertY = chart()->mapToPosition(m_positionHLine).y();
    m_verticalLineLeft->setLine(f_leftLineX,0,f_leftLineX,height());
    m_verticalLineRight->setLine(f_rightLineX,0,f_rightLineX,height());
    m_horizontalLine->setLine(0,f_vertY,width(),f_vertY);

}
