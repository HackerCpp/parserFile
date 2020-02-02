#include "curvebaseitem.h"
#include "curvelineitem.h"
#include "curvewaveitem.h"

int CurveBaseItem::m_headerSliceHeight = 20;
CurveBaseItem *CurveBaseItem::createCurveItem(Curve *curve){
    QString curveType = curve->desc()->getParam("draw_type");
    if(curveType.indexOf("LINE") != -1)
        return new CurveLineItem(curve);
    else if(curveType.indexOf("ACOUSTIC") != -1)
        return  new CurveWaveItem(curve);
    else
        return nullptr;
}
void CurveBaseItem::drawHeader(QPainter *painterHeader){
    //*************Paint Header*******************
    if(!painterHeader)
        return;
    int width = painterHeader->device()->width();
    painterHeader->setFont(QFont("Arial Black",8,10));
    painterHeader->setPen(*m_pen);
    if(!m_isActive)
       painterHeader->setBrush(QBrush(QColor(250,250,250,250)));
    else
       painterHeader->setBrush(QBrush(QColor(200,250,200,200)));
    painterHeader->drawRect(QRect(10,m_positionInHeader *m_headerSliceHeight,width - 20,m_headerSliceHeight));
    //painterHeader->setPen(*m_pen);
    painterHeader->drawText(QRect(15,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignLeft|Qt::AlignVCenter,QString::number(m_mainValue->indexBegin()));
    painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width - 15,m_headerSliceHeight),Qt::AlignRight|Qt::AlignVCenter,QString::number(1));
    painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->getMnemonic());
    //painterHeader->drawLine(QPoint(0,m_positionInHeader *m_headerSliceHeight),QPoint(width,m_positionInHeader *m_headerSliceHeight));
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
    emit updateL(QPointF(),QPointF(),true);
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
    QImage image(static_cast<int>(m_limit),3000,QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));
    QPainter p(&image);
    QPainter paintHeader;
    bool pr = false;
    paint(&p,nullptr,y,y+1500,&pr);
    return image.pixel(QPoint(point.x(),point.y() + 1000));
}
void CurveBaseItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag){

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
