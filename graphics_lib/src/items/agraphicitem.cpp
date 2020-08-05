#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem::AGraphicItem(ICurve *curve,BoardForTrack *board)
    : m_curve(curve),m_drawObject(nullptr), m_board(board),m_currentMainValue(nullptr)
{
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;

    m_fontLegend = QFont("Times", 15, QFont::Bold);
    m_heightLegend = QFontMetrics(m_fontLegend).height();
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

int AGraphicItem::mainIndexFromScene(QPointF point){
    /*if(mainValueMinimum() > point.y() || mainValueMaximum() < point.y()){
        return qQNaN();
    }*/
    if(!currentMainValue()){
        return -1;
    }
    uint index = 0;
    for(index = 1; index < currentMainValue()->size() - 1; ++index){
       if(mainValue(index) > point.y()  && mainValue(index + 1) < point.y() ||
           mainValue(index) < point.y()  && mainValue(index + 1) > point.y()){
           return index;// > 2?i - 2 : 0;
       }
    }
    return index;
}
qreal AGraphicItem::valueFromScenePoint(QPointF point){
    int f_index = mainIndexFromScene(point);
    if(f_index == -1)
        return qQNaN();
    return m_curve->data(f_index);
}

qreal AGraphicItem::maximumFromScenePoints(QPointF pointBegin,QPointF pointEnd){

    int f_indexBegin = mainIndexFromScene(pointBegin);
    int f_indexEnd = mainIndexFromScene(pointEnd);
    if(f_indexEnd == -1 || f_indexBegin == -1)
        return qQNaN();
    if(f_indexBegin > f_indexEnd){
        int f_index = f_indexBegin;
        f_indexBegin = f_indexEnd;
        f_indexEnd = f_index;
    }
    qreal f_maximum =  -std::numeric_limits<double>::max();
    //qreal f_minimum = std::numeric_limits<double>::max();
    for(int index = f_indexBegin * m_curve->sizeOffset(); index <= f_indexEnd * m_curve->sizeOffset(); ++index){
        f_maximum = std::max(m_curve->data(index),f_maximum);
        //f_minimum = std::min(m_curve->data(index),f_minimum);
    }
    return f_maximum;
}

qreal AGraphicItem::minimumFromScenePoints(QPointF pointBegin,QPointF pointEnd){
    int f_indexBegin = mainIndexFromScene(pointBegin);
    int f_indexEnd = mainIndexFromScene(pointEnd);
    if(f_indexEnd == -1 || f_indexBegin == -1)
        return qQNaN();
    if(f_indexBegin > f_indexEnd){
        int f_index = f_indexBegin;
        f_indexBegin = f_indexEnd;
        f_indexEnd = f_index;
    }
    //qreal f_maximum = -std::numeric_limits<double>::max();
    qreal f_minimum = std::numeric_limits<double>::max();
    for(int index = f_indexBegin * m_curve->sizeOffset(); index <= f_indexEnd * m_curve->sizeOffset(); ++index){
        //f_maximum = std::max(m_curve->data(index),f_maximum);
        f_minimum = std::min(m_curve->data(index),f_minimum);
    }
    return f_minimum;
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
