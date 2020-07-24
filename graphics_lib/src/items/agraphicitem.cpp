#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem::AGraphicItem(ICurve *curve,BoardForTrack *board)
    : m_curve(curve),m_drawObject(nullptr), m_board(board),m_currentMainValue(nullptr)
{
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;
    m_recordPointDepth = qIsNaN(curve->recordPoint()) ? 0 : curve->recordPoint();
}

AGraphicItem::AGraphicItem(CustomObject *drawObject,BoardForTrack *board)
    : m_curve(nullptr),m_drawObject(drawObject), m_board(board),m_currentMainValue(nullptr){
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;
    m_recordPointDepth = 0;

}

AGraphicItem::AGraphicItem(const AGraphicItem &other){
    if(&other == this)
        return;
    m_itemInfo = nullptr;
    m_curve = ICurve::curveCreater(*other.m_curve);
    m_board = other.m_board;
    m_isActive = other.m_isActive;
    m_positionHeaderArea = other.m_positionHeaderArea;
    m_heightHeaderArea = other.m_heightHeaderArea;
    m_recordPointDepth = other.m_recordPointDepth;
}

AGraphicItem::~AGraphicItem(){
}
void AGraphicItem::updateParam(int pictureWidth){
    Q_UNUSED(pictureWidth)
    if(!m_curve || !m_board)
        return;
    m_recordPointDepth = m_curve->recordPoint();
    m_currentMainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    m_currentRecordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    m_currentRecordPoint = qIsNaN(m_currentRecordPoint) ? 0 : m_currentRecordPoint;
    m_currentScaleMainValue = m_board->scale();
}

qreal AGraphicItem::topValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    qreal f_recordPoint = m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint()) * 1000;
    //qDebug() << m_curve->mnemonic() << (f_mainValue->minimum() + f_recordPoint) * m_board->scale();
    //qDebug() << f_mainValue->minimum() << f_recordPoint << (f_mainValue->minimum() + f_recordPoint) * m_board->scale() << m_curve->mnemonic();
    return (f_mainValue->minimum() + f_recordPoint) * m_board->scale();
}

qreal AGraphicItem::bottomValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    qreal f_recordPoint =  m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint()) * 1000;
    //qDebug() << f_mainValue->maximum() << f_recordPoint << (f_mainValue->maximum() + f_recordPoint) * m_board->scale() << m_curve->mnemonic();
    return (f_mainValue->maximum() + f_recordPoint) * m_board->scale();
}


void AGraphicItem::paint(QPainter *per,QPainter *perHead,QRectF visibleRect,
                         int &position,bool *flag){
    /*if(m_itemInfo->visible(AItem::BOARD_LEGEND_VIEW)){

    }*/

    if(m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        drawHeader(perHead,position,flag);
        drawBody(per,visibleRect,flag);
    }
}
QPair<QString,qreal> AGraphicItem::mainValueFromScene(QPointF point){
    qreal f_divider = m_board->isDrawTime() ? 600000 :  1000;
    QString f_unit = m_board->isDrawTime() ? "min" : "m";
    qreal f_value = point.y() / m_currentScaleMainValue / f_divider;
    return QPair<QString,qreal>(f_unit,f_value);
}
inline qreal AGraphicItem::mainValue(int index){
    return (m_currentMainValue->data(index) + m_currentRecordPoint) * m_currentScaleMainValue;
}

inline qreal AGraphicItem::mainValueMinimum(){
     return (m_currentMainValue->minimum() + m_currentRecordPoint) * m_currentScaleMainValue;
}
inline qreal AGraphicItem::mainValueMaximum(){
     return (m_currentMainValue->maximum() + m_currentRecordPoint) * m_currentScaleMainValue;
}
