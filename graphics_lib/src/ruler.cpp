#include "ruler.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>

Ruler::Ruler(int width){
    m_scale = 1;
    m_isMove = false;
    m_movingX = 0;
    m_leftX = 0;
    m_rightX = width + 100;
    m_x = 0;m_y = 0;
    m_curentPixmap = new QImage(100,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(100,2000,QImage::Format_ARGB32);
    m_visibilitySquare = new QRectF(0,0,0,0);
    setZValue(100);
}

void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(boundingRect().x(),(m_visibilitySquare->y() - fmod(m_visibilitySquare->y(),50))-100,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
     else
        qDebug() << "null";
}

void Ruler::run(){
    m_doublePixMap->fill(QColor(240,240,240,0));
    QPainter p(m_doublePixMap);
    p.setPen(QPen(QColor(0,0,0,200),1));
    p.setBrush(QColor(0,0,0,200));
    p.drawRect(0,0,100,m_doublePixMap->height());
    p.setFont(QFont("calibri",10));
    p.setPen(QColor(Qt::white));
    for(int i = 0;i < 2000;i += 50){
       p.drawText(QRect(0,i - 22,100,40),Qt::AlignHCenter|Qt::AlignVCenter,QString::number(((m_visibilitySquare->y() - fmod(m_visibilitySquare->y(),50))+i - 100)/m_scale,'g'));
       p.drawLine(QPoint(0,i),QPoint(12,i));
       p.drawLine(QPoint(88,i),QPoint(100,i));
       for(int j = 10;j < 50;j+=10){
           p.drawLine(QPoint(0,i + j),QPoint(6,i + j));
           p.drawLine(QPoint(94,i + j),QPoint(100,i + j));
       }
    }
    swapPixMap();
}

void Ruler::setScale(qreal scale){
    m_scale = scale;
}

void Ruler::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Qt::MouseButton btn = event->button();
    if(btn == Qt::LeftButton){
        m_prevPoint = event->scenePos();
        m_isMove = true;
    }
    else if(btn == Qt::RightButton){
        emit rightMouseClick();
    }
}

void Ruler::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isMove){
        QGraphicsItem::prepareGeometryChange();
        m_movingX += static_cast<int>(event->scenePos().x() - m_prevPoint.x());
        m_prevPoint = event->scenePos();
        m_movingX = m_movingX < 0?0:m_movingX;
        m_movingX = m_movingX > m_visibilitySquare->width() - 120?m_visibilitySquare->width()-120:m_movingX;
        //start();
        scene()->update();
    }
}
void Ruler::updateP(QPointF leftUp,QPointF rightDown,bool forceARedraw){
    if(forceARedraw){
       redraw();
       return;
    }
    QGraphicsItem::prepareGeometryChange();
    m_visibilitySquare->setTopLeft(leftUp);
    int x = m_visibilitySquare->x()<m_leftX?m_leftX:m_visibilitySquare->x();
    m_visibilitySquare->setX(x);
    m_visibilitySquare->setBottomRight(rightDown);
    redraw();
}
void Ruler::setSize(QRectF rect){
    m_del = true;
    wait();
    m_rightX = static_cast<int>(rect.width());
    start();
}
QRectF Ruler::boundingRect()const{
    return QRectF((m_visibilitySquare->x() + m_movingX) > m_rightX - 100?m_rightX-100:(m_visibilitySquare->x() + m_movingX),m_top,100,m_bottom - m_top);
}
void Ruler::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){  
    m_isMove = false;
}
