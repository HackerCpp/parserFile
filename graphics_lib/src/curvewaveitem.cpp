#include "curvewaveitem.h"

CurveWaveItem::CurveWaveItem(Curve *curve)
    :CurveBaseItem(curve){
    m_pen = new QPen(QColor(qrand()%255,qrand()%255,qrand()%255),3);
    m_brush = new QBrush(QColor(qrand()%255,qrand()%255,qrand()%255));
    m_drawingMode = WAVE;
}

void CurveWaveItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag){
    if(!m_mainValue)
        return;
    if(painterHeader){
        int width = painterHeader->device()->width();
        painterHeader->setPen(QPen());
        painterHeader->drawRect(QRect(10,m_positionInHeader *m_headerSliceHeight,width - 20,m_headerSliceHeight));
        painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->getMnemonic());
    }
    uint indexBegin = m_mainValue->indexBegin();
    if(indexBegin == m_mainValue->size())
        return;
    uint quantityElem = m_curve->quantiytElements() / m_curve->sizeOfType();
    //for(uint i = indexBegin; i < quantityElem)

//qDebug() << m_curve->quantiytElements() <<"  " <<  m_curve->getSize();

    //Рисуем заголовок
    drawHeader(painterHeader);
}
bool CurveWaveItem::isCrosses(QPoint point,int y){

}
qreal CurveWaveItem::operator[](int index){

}
uint CurveWaveItem::amountSaturation(uint index){

}
CurveWaveItem::~CurveWaveItem(){

}
