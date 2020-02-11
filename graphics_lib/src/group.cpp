#include "group.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QTime>
#include <QGraphicsSceneMouseEvent>
#include "tabcurvesettings.h"
#include <QApplication>

//int Group::m_headerTopOffset = 0;
Group::Group(int leftX,int rightX,int *headerTopOffset){
     m_settings = new TabGroupSettings;
     m_curves = new QVector<CurveBaseItem*>;
     m_leftX = leftX;
     m_rightX = rightX;
     m_headerTopOffset = headerTopOffset;
     m_curentPixmap = new QImage(m_rightX - m_leftX,6000,QImage::Format_RGB32);
     m_doublePixMap = new QImage(m_rightX - m_leftX,6000,QImage::Format_RGB32);
     m_curentHeader = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
     m_doubleHeader = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);

     m_visibilitySquare = new QRectF(0,0,0,0);
     connect(this,&BaseGroup::leftPositionChanged,this,&Group::resize);
     connect(this,&BaseGroup::rightPositionChanged,this,&Group::resize);
     m_del = false;
}
void Group::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;

    ptr = m_curentHeader;
    m_curentHeader = m_doubleHeader;
    m_doubleHeader = ptr;
    ptr = nullptr;
    m_topPositionPicture =static_cast<int>(m_visibilitySquare->y() - 1000);
}
void Group::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap){
        painter->drawImage(QRect(m_leftX,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
        painter->drawImage(QRect(m_leftX,(m_visibilitySquare->y() + *m_headerTopOffset) > m_visibilitySquare->y() + m_visibilitySquare->height()?m_visibilitySquare->y()+m_visibilitySquare->height() - 50:(m_visibilitySquare->y() + *m_headerTopOffset),m_rightX - m_leftX,m_curentHeader->height()),*m_curentHeader);
    }
    else
        qDebug() << "null";
}

void Group::resize(int position){
    m_del = true;
    wait();
    delete m_curentPixmap;
    delete m_doublePixMap;
    delete m_curentHeader;
    delete m_doubleHeader;
    m_curentPixmap = new QImage(m_rightX - m_leftX,6000,QImage::QImage::Format_RGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,6000,QImage::QImage::Format_RGB32);
    m_curentHeader = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_doubleHeader = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    int limit = m_rightX - m_leftX;
    foreach(auto value,*m_curves){
        value->setLimit(limit);
    }
    redraw();
}

void Group::updateP(QPointF leftUp,QPointF rightDown,bool forceARedraw){
    if(forceARedraw){
       redraw();
       return;
    }
    if(leftUp.x() > m_rightX || rightDown.x() < m_leftX)
        return;
    /*if(m_topPositionPicture + 3000 > rightDown.y() + 400 & m_topPositionPicture < leftUp.y() - 400)
        return;*/
    m_visibilitySquare->setTopLeft(leftUp);
    m_visibilitySquare->setBottomRight(rightDown);
    redraw();
}

void Group::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = static_cast<int>(event->scenePos().x());
    int y = static_cast<int>(event->scenePos().y());
    Qt::MouseButton btn = event->button();
    if(event->scenePos().y() >= (m_visibilitySquare->y()) + *m_headerTopOffset + 20 &&
        event->scenePos().y() <= (m_visibilitySquare->y() + *m_headerTopOffset + m_sizeVisibleItem * 20 + 20))
    {
        m_prevPoint = event->scenePos();
        if(btn == Qt::RightButton){
            int index = (event->scenePos().y() - m_visibilitySquare->y() - *m_headerTopOffset - 20)/20;
            int i = 0;
            foreach (auto value, *m_curves){
                if(value->isShow() ){
                    if(i==index){
                        value->setActive(true);
                        m_settings->addCurve(value);
                        m_settings->show();
                        start();
                    }
                    ++i;
                }
            }
        }
        else{
           m_settings->hideL();
        }
        m_isMoveHeader = true;
        return;
    }
    if(btn == Qt::LeftButton){
        m_settings->hideL();
        if(m_curves->isEmpty())
            return;
        foreach(auto curve,*m_curves){
            if(curve->isCrosses(QPoint(x - m_leftX,static_cast<int>(y - m_visibilitySquare->y())),m_visibilitySquare->y())){
                curve->setActive(true);
            }
            else{
                curve->setActive(false);
            }
        }
    }
    else if(btn == Qt::RightButton){
        if(m_curves->isEmpty())
            return;
        foreach(auto curve,*m_curves){
            if(curve->isShow()){
                if(curve->isCrosses(QPoint(x - m_leftX,static_cast<int>(y - m_visibilitySquare->y())),m_visibilitySquare->y())){
                    curve->setActive(true);
                    m_settings->addCurve(curve);
                    m_settings->show();
                }
                else{
                    curve->setActive(false);
                }
            }
        }
    }
    redraw();
}
void Group::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isMoveHeader){
        *m_headerTopOffset += static_cast<int>(event->scenePos().y() - m_prevPoint.y());
        *m_headerTopOffset = *m_headerTopOffset < -(m_curves->size() *20) + 5?-(m_sizeVisibleItem *20) + 5:*m_headerTopOffset;
        *m_headerTopOffset = *m_headerTopOffset > m_visibilitySquare->height()-50?m_visibilitySquare->height()-50:*m_headerTopOffset;
        m_prevPoint = event->scenePos();
        scene()->update();
    }
}
void Group::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    m_isMoveHeader = false;
}
void Group::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->scenePos().y() >= (m_visibilitySquare->y()) + *m_headerTopOffset + 20 &&
        event->scenePos().y() <= (m_visibilitySquare->y() + *m_headerTopOffset + m_sizeVisibleItem * 20 + 20)){
        /*int index = (event->scenePos().y() - m_visibilitySquare->y() - m_headerTopOffset - 20)/20;
        if(index < m_curves->size()){
            m_curves->data()[index]->setActive(true);
            start();
        }*/
    }

}
void Group::addCurve(CurveBaseItem *curve){
    int limit = m_rightX - m_leftX;
    curve->setLimit(limit);
    if(m_curves)
        m_curves->push_back(curve);
    m_sizeVisibleItem = m_curves->size();
    curve->setPositionInHeader(m_sizeVisibleItem);
    connect(curve,&CurveBaseItem::updateL,this,&Group::updateP);

}

void Group::run(){
    //QTime time = QTime::currentTime();
    QPainter painter(m_doublePixMap);
    QPainter painterHeader(m_doubleHeader);
    m_doubleHeader->fill(0);
    m_doublePixMap->fill(0xffffff);
    int i = 1;
    m_del = false;
    foreach (auto value, *m_curves){
        if(m_del)
            return;
        if(value->isShow()){            
            value->setPositionInHeader(i);
            value->paint(&painter,&painterHeader,m_visibilitySquare->y(),m_visibilitySquare->y()+m_visibilitySquare->height(),&m_del);
            ++i;
        }
        if(m_del)
            return;
    }
    m_sizeVisibleItem = i;
    swapPixMap();
    //qDebug() << time.msecsTo( QTime::currentTime() );
}
