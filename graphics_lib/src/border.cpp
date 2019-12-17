#include "border.h"

Border::Border(int position,int leftLimiter){
    m_leftLimiter = leftLimiter;
    m_scale = 1;
    m_width = 10;
    m_isMove = false;
    m_movingX = 0;
    m_leftX = position;
    m_rememberPosition = m_leftX;
    m_isClose = false;
    m_rightX = position + m_width;
    m_curentPixmap = new QImage(m_width,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_width,2000,QImage::Format_ARGB32);
    m_collapseTab = new QImage(m_width,m_width,QImage::Format_ARGB32);
    m_expandTab = new QImage(m_width,m_width,QImage::Format_ARGB32);

    QPainter p(m_collapseTab);
    m_collapseTab->fill(QColor(255,255,255,255));
    p.setPen(QPen(QColor(0,0,0,255),2));
    p.drawLine(QPoint(3,m_collapseTab->height()/2),QPoint(m_collapseTab->width()-3,m_collapseTab->height()/2));
    p.setPen(QPen(QColor(0,0,0,255),0.5));
    p.drawRect(QRect(0,0,m_width - 1,m_width - 1));

    QPainter pr(m_expandTab);
    m_expandTab->fill(QColor(255,255,255,255));
    pr.setPen(QPen(QColor(0,0,0,255),2));
    pr.drawLine(QPoint(3,m_expandTab->height()/2),QPoint(m_expandTab->width()-3,m_expandTab->height()/2));
    pr.drawLine(QPoint(m_expandTab->width()/2,3),QPoint(m_expandTab->width()/2,m_expandTab->height()-3));
    pr.setPen(QPen(QColor(0,0,0,255),0.5));
    pr.drawRect(QRect(0,0,m_width - 1,m_width - 1));

    m_visibilitySquare = new QRectF(0,0,0,0);
    setZValue(100);
    m_curentIsClose = m_collapseTab;
}
void Border::shift(int leftPosition){
    QGraphicsItem::prepareGeometryChange();
    m_leftLimiter += leftPosition - m_leftX;
    m_leftX = leftPosition;
    m_rightX = m_leftX + m_width;
    emit rightPositionChanged(m_rightX);
}
void Border::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap){
        painter->drawImage(QRect(m_leftX,m_visibilitySquare->y() - 500,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
        painter->drawImage(QRect(m_leftX,m_visibilitySquare->y(),m_collapseTab->width(),m_collapseTab->height()),*m_curentIsClose);
    }
     else
        qDebug() << "null";
}

void Border::run(){
    m_doublePixMap->fill(QColor(240,240,240,0));
    QPainter p(m_doublePixMap);
    p.setPen(QPen(QColor(0,0,0,0),1));
    if(m_isMove)
        p.setBrush(QColor(0,255,0,150));
    else
        p.setBrush(QColor(0,0,0,150));
    p.drawRect(0,0,m_rightX - m_leftX,m_doublePixMap->height());
    swapPixMap();
}

void Border::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = static_cast<int>(event->scenePos().x());
    int y = static_cast<int>(event->scenePos().y());
    Qt::MouseButton btn = event->button();
    if(btn == Qt::LeftButton){
        if(x >= m_leftX && x <= m_rightX){
            QGraphicsItem::prepareGeometryChange();
            if(y < m_visibilitySquare->y() + m_width){
                m_isClose = !m_isClose;
                m_curentIsClose = m_isClose?m_expandTab:m_collapseTab;
                if(m_isClose){
                    m_rememberPosition = m_leftX - m_leftLimiter;
                    m_leftX -= m_rememberPosition;
                }
                else{
                    m_leftX += m_rememberPosition;
                }
                m_rightX = m_leftX + m_width;
                emit leftPositionChanged(m_leftX);
                emit rightPositionChanged(m_rightX);
                scene()->update();
            }
            if(m_isClose)
                return;

            m_prevPoint = event->scenePos();
            m_isMove = true;
        }
    }
    else if(btn == Qt::RightButton){
        qDebug() << "rightBtnBorder";
    }
}

void Border::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    wait();
    if(m_isMove){
        QGraphicsItem::prepareGeometryChange();
        m_leftX += static_cast<int>(event->scenePos().x() - m_prevPoint.x());
        m_leftX = m_leftX < m_leftLimiter?m_leftLimiter:m_leftX;
        m_rightX = m_leftX + m_width;
        start();
        //emit leftPositionChanged(m_leftX);
        //emit rightPositionChanged(m_rightX);
        m_prevPoint = event->scenePos();
    }
}
void Border::updateP(QPointF leftUp,QPointF rightDown){
    wait();
    QGraphicsItem::prepareGeometryChange();
    m_visibilitySquare->setTopLeft(leftUp);
    m_visibilitySquare->setBottomRight(rightDown);
    start(QThread::HighestPriority);
}

void Border::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    wait();
    m_isMove = false;
    emit leftPositionChanged(m_leftX);
    emit rightPositionChanged(m_rightX);
    start();
}
