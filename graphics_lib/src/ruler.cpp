#include "ruler.h"
#include <QPainter>
#include "QGraphicsSceneMouseEvent"
#include <QGraphicsScene>

Ruler::Ruler(BoardForTrack *board):
    m_board(board){
    setZValue(100);
    m_positionX = 0;
    uint f_pictureHeight = m_board->pictureHeight();
    uint f_pixelPerMm = m_board->pixelPerMm();
    m_width = 20 * f_pixelPerMm;
    m_curentPixmap = new QImage(m_width,f_pictureHeight,QImage::Format_ARGB4444_Premultiplied);
    m_doublePixMap = new QImage(m_width,f_pictureHeight,QImage::Format_ARGB4444_Premultiplied);
}

void Ruler::mousePressEvent(QGraphicsSceneMouseEvent *event){
    m_prevPoint = event->pos();
}

void Ruler::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::prepareGeometryChange();
    m_positionX -= (m_prevPoint - event->pos()).x();
    m_positionX = m_positionX > 0?m_positionX:0;
    m_prevPoint = event->pos();
    /*scene()->*/update();
}

void Ruler::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
}



void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(!m_curentPixmap)
        return;
    painter->drawImage(boundingRect(),*m_curentPixmap);
}

void Ruler::run(){
    QPainter f_painter(m_doublePixMap);
    m_doublePixMap->fill(0x9000);

    qreal f_width = m_doublePixMap->width();
    qreal f_height = m_doublePixMap->height();
    QPen f_pen(Qt::white,1);
    f_painter.setPen(f_pen);
    qreal f_step = 10 * m_board->pixelPerMm();
    qreal mm5 = 5 * m_board->pixelPerMm();
    for(qreal i = f_step - fmod(m_visibilitySquare.y(),f_step);i < f_height;i += f_step){
        f_painter.drawLine(QPointF(0,i),QPointF(mm5,i));
        f_painter.drawLine(QPointF(f_width - mm5,i),QPointF(f_width,i));
        qreal f_number = (m_visibilitySquare.y() + m_board->top() + (i + m_board->offsetUp())) / m_board->scale() / 10000;
        f_painter.drawText(QRectF(mm5,i - 10,f_step,20),Qt::AlignHCenter|Qt::AlignVCenter,QString::number(f_number));
        if(m_endRedraw)
            return;
    }
    f_step = 1 * m_board->pixelPerMm();
    qreal mm4 = 2 * m_board->pixelPerMm();
    f_painter.setPen(QPen(Qt::white,0.8));
    for(qreal i = f_step - fmod(m_visibilitySquare.y(),f_step);i < f_height;i += f_step){
        f_painter.drawLine(QPointF(0,i),QPointF(mm4,i));
        f_painter.drawLine(QPointF(f_width - mm4,i),QPointF(f_width,i));
        if(m_endRedraw)
            return;
    }
    swapPixMap();
}

void Ruler::resizePictures(){
    if(m_doublePixMap){delete m_doublePixMap;m_doublePixMap = nullptr;}
    if(m_doublePixMap){delete m_curentPixmap;m_curentPixmap = nullptr;}
    uint f_pictureHeight = m_board->pictureHeight();
    m_curentPixmap = new QImage(m_width,f_pictureHeight,QImage::Format_ARGB4444_Premultiplied);
    m_doublePixMap = new QImage(m_width,f_pictureHeight,QImage::Format_ARGB4444_Premultiplied);
    redraw();
}

QRectF Ruler::boundingRect()const{
    return QRect(m_visibilitySquare.x() + m_positionX,m_visibilitySquare.y() - m_board->offsetUp(),m_width,m_curentPixmap->height());
}
