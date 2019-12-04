#include "curvebaseitem.h"
#include "curvelineitem.h"

CurveBaseItem *CurveBaseItem::createCurveItem(Curve *curve){
    QString curveType = curve->desc()->getParam("draw_type");
    if(curveType.indexOf("LINE") != -1)
        return new CurveLineItem(curve);
    else
        return nullptr;

}
bool CurveBaseItem::setScale(qreal scale){
    m_curve->setScale(scale);
}
qreal CurveBaseItem::topTime(){
    return m_curve->getTime()->minimum();
}
qreal CurveBaseItem::bottomTime(){
    return m_curve->getTime()->maximum();
}
qreal CurveBaseItem::topDepth(){
    return m_curve->getDepth()->minimum();
}
qreal CurveBaseItem::bottomDepth(){
    return m_curve->getDepth()->maximum();
}
void CurveBaseItem::setWidthLine(int widthLine){
    m_curentWidthLine = widthLine;
    m_pen->setWidth(m_curentWidthLine);
    emit updateL();
}
void CurveBaseItem::setLimit(int limit){
    m_curve->setLimit(limit);
}
CurveBaseItem::CurveBaseItem(Curve *curve):
    m_curve(curve){
    m_pen = nullptr;
    m_brush = nullptr;
    m_curentWidthLine = 2;
}
Curve *CurveBaseItem::getCurve(){
    return m_curve;
}
bool CurveBaseItem::isCrosses(QPoint point,int y){
    return false;
}
void CurveBaseItem::paint(QPainter *painter,qreal y){

}
void CurveBaseItem::setActive(bool active){
    m_isActive = active;
    if(m_pen){
        if(m_isActive)
            m_pen->setWidth(m_curentWidthLine + 5);
        else
            m_pen->setWidth(m_curentWidthLine);
    }
}
bool CurveBaseItem::isActive(){
    return m_isActive;
}
QRectF CurveBaseItem::boundingRect() const{

}
