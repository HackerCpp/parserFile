#include "group.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QTime>
#include <QGraphicsSceneMouseEvent>
#include "tabcurvesettings.h"

int Group::m_headerTopOffset = 0;
Group::Group(int leftX,int rightX){
     m_settings = new TabGroupSettings;
     m_curves = new QVector<CurveBaseItem*>;
     m_leftX = leftX;
     m_rightX = rightX;
     m_headerTopOffset = 200;
     m_curentPixmap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
     m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
     m_curentHeader = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
     m_curentHeader->fill(QColor(0,0,0,0));
     m_visibilitySquare = new QRectF(0,0,0,0);
     connect(this,&BaseGroup::leftPositionChanged,this,&Group::resize);
     connect(this,&BaseGroup::rightPositionChanged,this,&Group::resize);
}

void Group::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap){
        painter->drawImage(QRect(m_leftX,static_cast<int>(m_visibilitySquare->y() - 500),m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
        painter->drawImage(QRect(m_leftX,(m_visibilitySquare->y() + m_headerTopOffset) > m_visibilitySquare->y() + m_visibilitySquare->height()?m_visibilitySquare->y()+m_visibilitySquare->height() - 50:(m_visibilitySquare->y() + m_headerTopOffset),m_rightX - m_leftX,m_curentHeader->height()),*m_curentHeader);
        painter->setPen(QPen(Qt::black,2));
        painter->drawLine(QPoint(m_leftX,m_visibilitySquare->y()),QPoint(m_leftX,m_visibilitySquare->y() + m_visibilitySquare->height()));
    }
    else
        qDebug() << "null";
}

void Group::setDrawTypeTime(){
    foreach(auto value,*m_curves){
        value->getCurve()->setMainTime();
    }
}

void Group::setDrawTypeDepth(){
    foreach(auto value,*m_curves){
        value->getCurve()->setMainDepth();
    }
}
void Group::resize(int position){
    wait();
    delete m_curentPixmap;
    delete m_doublePixMap;
    m_curentPixmap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    int limit = m_rightX - m_leftX;
    foreach(auto value,*m_curves){
        value->setLimit(limit);
    }
    start();
}
void Group::updateP(QPointF leftUp,QPointF rightDown){
    if(leftUp.x() > m_rightX || rightDown.x() < m_leftX)
        return;
    wait();
    m_visibilitySquare->setTopLeft(leftUp);
    m_visibilitySquare->setBottomRight(rightDown);
    start();
}
void Group::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = static_cast<int>(event->scenePos().x());
    int y = static_cast<int>(event->scenePos().y());
    Qt::MouseButton btn = event->button();
    if(btn == Qt::LeftButton){
        m_settings->hideL();
        if(event->scenePos().y() >= (m_visibilitySquare->y()) + m_headerTopOffset + 15 &&
            event->scenePos().y() <= (m_visibilitySquare->y() + m_headerTopOffset + m_curves->size() * 15 + 15)){
            m_prevPoint = event->scenePos();
            m_isMoveHeader = true;
        }
        else{
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
    }
    else if(btn == Qt::RightButton){
        if(m_curves->isEmpty())
            return;
        foreach(auto curve,*m_curves){
            if(curve->isCrosses(QPoint(x - m_leftX,static_cast<int>(y - m_visibilitySquare->y())),m_visibilitySquare->y())){
                curve->setActive(true);
                //TabCurveSettings *settings = new TabCurveSettings(curve);
                m_settings->addCurve(curve);
                m_settings->show();
            }
            else{
                curve->setActive(false);
            }
        }
    }
    start();
}
void Group::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    wait();
    if(m_isMoveHeader){
        m_headerTopOffset += event->scenePos().y() - m_prevPoint.y();
        m_headerTopOffset = m_headerTopOffset < -(m_curves->size() *15) + 5?-(m_curves->size() *15) + 5:m_headerTopOffset;
        m_headerTopOffset = m_headerTopOffset > m_visibilitySquare->height()-50?m_visibilitySquare->height()-50:m_headerTopOffset;
        m_prevPoint = event->scenePos();
        scene()->update();
    }
}
void Group::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    m_isMoveHeader = false;
}

void Group::addCurve(CurveBaseItem *curve){
    int limit = m_rightX - m_leftX;
    curve->setLimit(limit);
    if(m_curves)
        m_curves->push_back(curve);
    QPainter *painter = new QPainter(m_curentHeader);
    painter->setFont(QFont("Arial Black",10,100));
    painter->setPen(QPen());
    painter->setBrush(QBrush(QColor(250,250,250,220)));
    painter->drawRect(QRect(0,m_curves->size() *15,m_rightX - m_leftX,15));
    painter->setPen(*curve->getPen());
    painter->drawText(QRect(0,m_curves->size() *15,m_rightX - m_leftX,15),Qt::AlignHCenter|Qt::AlignVCenter,curve->getCurve()->getMnemonic());
    painter->drawLine(QPoint(0,m_curves->size() *15),QPoint(m_rightX - m_leftX,m_curves->size() *15));
    delete painter;
    connect(curve,&CurveBaseItem::updateL,this,&Group::updatePL);
}
void Group::updatePL(){
    wait();
    start();
}
void Group::run(){
    QPainter painter(m_doublePixMap);
    m_doublePixMap->fill(QColor(0,0,0,0));
    foreach (auto value, *m_curves){
        value->paint(&painter,m_visibilitySquare->y());
    }
    swapPixMap();
}
