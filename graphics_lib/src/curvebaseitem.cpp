#include "curvebaseitem.h"
#include "curvelineitem.h"

int CurveBaseItem::m_headerSliceHeight = 20;
CurveBaseItem *CurveBaseItem::createCurveItem(Curve *curve){
    QString curveType = curve->desc()->getParam("draw_type");
    if(curveType.indexOf("LINE") != -1)
        return new CurveLineItem(curve);
    else
        return nullptr;
}
uint CurveBaseItem::amountSaturation(uint index){
    return 0;
}
CurveBaseItem::CurveBaseItem(Curve *curve):
    m_curve(curve){
    m_isActive = false;
    m_positionInHeader = 0;
    m_pen = nullptr;
    m_isShow = true;
    m_brush = nullptr;
    m_curentWidthLine = 1;
    m_mainValue = nullptr;
    m_scale = 1;
    m_leftShift = 0;
}
void CurveBaseItem::setShow(bool isShow){
    m_isShow = isShow;
}
void CurveBaseItem::setScale(qreal scale){
    m_scale = scale;
}
void CurveBaseItem::setLeftShift(int leftShift){
    m_leftShift = leftShift;
}
void CurveBaseItem::setMainValue(MainValue *mainValue){
    m_mainValue = mainValue;
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
    m_limit = limit;
}
void CurveBaseItem::setPositionInHeader(int pos){
   m_positionInHeader = pos;
}

Curve *CurveBaseItem::getCurve(){
    return m_curve;
}
bool CurveBaseItem::isCrosses(QPoint point,int y){
    return false;
}
void CurveBaseItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom){

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
