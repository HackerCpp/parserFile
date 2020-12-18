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
    m_modeCountedDepth = 0;
}

AGraphicItem::AGraphicItem(CustomObject *drawObject,BoardForTrack *board)
    : m_curve(nullptr),m_drawObject(drawObject), m_board(board),m_currentMainValue(nullptr){
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;
    m_recordPointDepth = 0;
    m_modeCountedDepth = 0;

}

AGraphicItem::AGraphicItem(const AGraphicItem &other){
    if(&other == this)
        return;
    m_itemInfo = other.m_itemInfo;
    m_curve = ICurve::curveCreater(*other.m_curve);
    m_board = other.m_board;
    m_isActive = other.m_isActive;
    m_positionHeaderArea = other.m_positionHeaderArea;
    m_heightHeaderArea = other.m_heightHeaderArea;
    m_recordPointDepth = other.m_recordPointDepth;
}

void AGraphicItem::updateParam(int pictureWidth){
    Q_UNUSED(pictureWidth)
    if(!m_curve || !m_board)
        return;
    m_recordPointDepth = m_curve->recordPoint();
    m_currentMainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    m_currentRecordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth);
    m_currentRecordPoint = qIsNaN(m_currentRecordPoint) ? 0 : m_currentRecordPoint;
    m_currentScaleMainValue = m_board->scale();
}

qreal AGraphicItem::topValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    if(!f_mainValue)
        return 0;
    qreal f_recordPoint = m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint());
    qreal f_result = (f_mainValue->minimum() + f_recordPoint) * m_board->scale();
    return f_result;
}

qreal AGraphicItem::bottomValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    if(!f_mainValue)
        return 0;
    qreal f_recordPoint =  m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint());
    qreal f_result = (f_mainValue->maximum() + f_recordPoint) * m_board->scale();
    return f_result;
}

void AGraphicItem::setDepthCoeff(QVector<qreal> f_coeffs){
    QString f_str = QString::number(f_coeffs.size());
    foreach(auto coeff,f_coeffs){
        f_str += (":" + QString::number(coeff));
    }
    m_curve->desc()->setParam("shift_depth",f_str);
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

int AGraphicItem::mainIndexFromScenePoint(QPointF point){
    if(!currentMainValue() || !currentMainValue()->size()){
        return -1;
    }
    int f_mainSize = currentMainValue()->size();
    if(mainValue(0) < mainValue(f_mainSize - 1)){
        for(uint index = 0; index < currentMainValue()->size() - 1; ++index){
           if(mainValue(index) <= point.y()  && mainValue(index + 1) >= point.y()){
               return index;
           }
        }
        return point.y() <= mainValue(0) ? 0 : f_mainSize + 1;
    }
    else{
        for(uint index  = f_mainSize - 1; index > 0; --index){
           if(mainValue(index) <= point.y()  && mainValue(index - 1) >= point.y()){
               qreal f_aver = (mainValue(index - 1) +  mainValue(index)) / 2;
               return point.y() < f_aver ? index : index - 1;
           }
        }
        return point.y() >= mainValue(0) ? 0 : f_mainSize - 1;
    }

}

qreal AGraphicItem::valueFromScenePoint(QPointF point){
    int f_index = mainIndexFromScenePoint(point);
    if(f_index == -1)
        return qQNaN();
    m_curve->load();
    qreal f_result = m_curve->data(f_index);
    return f_result;
}

qreal AGraphicItem::maximumFromScenePoints(QPointF pointBegin,QPointF pointEnd){
    int f_indexBegin = mainIndexFromScenePoint(pointBegin);
    int f_indexEnd = mainIndexFromScenePoint(pointEnd);
    if(f_indexEnd == -1 || f_indexBegin == -1)
        return qQNaN();

    if(f_indexBegin > f_indexEnd){
        int f_index = f_indexBegin;
        f_indexBegin = f_indexEnd;
        f_indexEnd = f_index;
    }
    m_curve->load();
    qreal f_maximum =  -std::numeric_limits<double>::max();
    for(int index = f_indexBegin * m_curve->sizeOffset(); index <= f_indexEnd * m_curve->sizeOffset(); ++index)
        f_maximum = std::max(m_curve->data(index),f_maximum);
    m_curve->unload();
    return f_maximum;
}

qreal AGraphicItem::minimumFromScenePoints(QPointF pointBegin,QPointF pointEnd){

    int f_indexBegin = mainIndexFromScenePoint(pointBegin);
    int f_indexEnd = mainIndexFromScenePoint(pointEnd);
    if(f_indexEnd == -1 || f_indexBegin == -1)
        return qQNaN();

    if(f_indexBegin > f_indexEnd){
        int f_index = f_indexBegin;
        f_indexBegin = f_indexEnd;
        f_indexEnd = f_index;
    }
    m_curve->load();
    qreal f_minimum = std::numeric_limits<double>::max();
    for(int index = f_indexBegin * m_curve->sizeOffset(); index <= f_indexEnd * m_curve->sizeOffset(); ++index)
        f_minimum = std::min(m_curve->data(index),f_minimum);
    m_curve->unload();
    return f_minimum;
}

QPair<QString,qreal> AGraphicItem::mainValueFromScene(QPointF point){
    qreal f_divider = m_board->isDrawTime() ? 600000 :  1000;
    QString f_unit = m_board->isDrawTime() ? "min" : "m";
    qreal f_value = point.y() / m_currentScaleMainValue / f_divider;
    return QPair<QString,qreal>(f_unit,f_value);
}

inline qreal AGraphicItem::mainValue(int index){
    qreal f_depth;
    if(m_modeCountedDepth == 3){
        f_depth = (m_currentMainValue->data(index) * m_currentMainValue->data(index)) * k_a +
                m_currentMainValue->data(index) * k_b + k_c;
    }
    else if(m_modeCountedDepth == 2){
        f_depth = m_currentMainValue->data(index) * k_a + k_b;
    }
    else if(m_modeCountedDepth == 1){
        f_depth = m_currentMainValue->data(index) + k_b;
    }
    else
       f_depth = m_currentMainValue->data(index);
    return (f_depth + m_currentRecordPoint) * m_currentScaleMainValue;
}

inline qreal AGraphicItem::mainValueMinimum(){
    qreal f_minimum;
    if(m_modeCountedDepth == 3)
        f_minimum = (m_currentMainValue->minimum() * m_currentMainValue->minimum()) * k_a +
                m_currentMainValue->minimum() * k_b + k_c;
    else if(m_modeCountedDepth == 2){
        f_minimum = m_currentMainValue->minimum() * k_a + k_b;
    }
    else if(m_modeCountedDepth == 1){
        f_minimum = m_currentMainValue->minimum() + k_b;
    }
    else
       f_minimum = m_currentMainValue->minimum();
     return (f_minimum + m_currentRecordPoint) * m_currentScaleMainValue;
}

inline qreal AGraphicItem::mainValueMaximum(){
    qreal f_maximum;
    if(m_modeCountedDepth == 3)
        f_maximum = (m_currentMainValue->maximum() * m_currentMainValue->maximum()) * k_a +
                m_currentMainValue->maximum() * k_b + k_c;
    else if(m_modeCountedDepth == 2){
        f_maximum = m_currentMainValue->maximum() * k_a + k_b;
    }
    else if(m_modeCountedDepth == 1){
        f_maximum = m_currentMainValue->maximum() + k_b;
    }
    else
       f_maximum = m_currentMainValue->maximum();
     return (f_maximum + m_currentRecordPoint) * m_currentScaleMainValue;
}
