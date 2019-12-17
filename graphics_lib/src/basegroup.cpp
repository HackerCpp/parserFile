#include "basegroup.h"

//int BaseGroup::m_top = -10;
//int BaseGroup::m_bottom = 2000;

BaseGroup::BaseGroup(){
    m_leftX = 0;
    m_rightX = 0;
    m_visibilitySquare = nullptr;
    m_curentPixmap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    setZValue(0);
    connect(this,&BaseGroup::finished,this,&BaseGroup::sceneUpdate);
    connect(&timer,&QTimer::timeout,this,&BaseGroup::updateTimer);
}
void BaseGroup::updateTimer(){
    timer.stop();
    start();
}
void BaseGroup::setRightPosition(int rightPosition){
    m_rightX = rightPosition;
    emit rightPositionChanged(m_rightX);
}
int BaseGroup::getRightX(){
    return m_rightX;
}
void BaseGroup::setLeftPosition(int leftPosition){
    m_leftX = leftPosition;
    emit leftPositionChanged(m_leftX);
}
void BaseGroup::shift(int leftPosition){
    QGraphicsItem::prepareGeometryChange();
    m_rightX = leftPosition + m_rightX - m_leftX + 10;
    m_leftX = leftPosition + 10;
    emit rightPositionChanged(m_rightX);
}
QRectF BaseGroup::boundingRect()const{
    return QRectF(m_leftX,m_top,m_rightX - m_leftX,m_bottom - m_top);
}
void BaseGroup::setTopAndBottom(qreal top,qreal bottom){
    m_top = top;
    m_bottom = bottom;
}
void BaseGroup::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;
    ptr = nullptr;
    //scene()->update();
}
void BaseGroup::sceneUpdate(){
    scene()->update();
}
void BaseGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){}
void BaseGroup::run(){}
void BaseGroup::updateP(QPointF leftUp,QPointF rightDown){
    if(leftUp.x() > m_rightX || rightDown.x() < m_leftX)
        return;
    timer.stop();
    wait();
    m_visibilitySquare->setTopLeft(leftUp);
    m_visibilitySquare->setBottomRight(rightDown);
    start();
    //timer.start(2);
}
