#include "agraphictrack.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>



void AGraphicTrack::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;
    ptr = m_curentHeader;
    m_curentHeader = m_doubleHeader;
    m_doubleHeader = ptr;
    ptr = nullptr;
    toSetTheLocationOfTheImageAfterDrawing();
}

void AGraphicTrack::init(){
     m_items = new QList<AGraphicItem*>;
     m_visibilitySquare.setRect(0,0,2000,2000);
     m_border = nullptr;
     m_isLeftBorderClick = m_isRightBorderClick = m_isLeftCurvesClick
      =  m_isRightCurvesClick = m_isLeftHeaderClick = m_isOpenCloseClick = false;
     m_isOpen = true;
     m_positionOfTheBorder = 0;
     m_boundingRect = QRectF(0,0,2000,2000);
     connect(this,&AGraphicTrack::finished,this,&AGraphicTrack::sceneUpdate);
}

AGraphicTrack::AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves,BoardForTrack *board)
    : m_board(board), m_track(track){
    init();
}

AGraphicTrack::~AGraphicTrack(){

}
void AGraphicTrack::addIteam(AGraphicItem* item){
    if(!m_items || !item)
    return;
    if(item->itemInfo()->type() == ACU)
        m_items->push_front(item);
    else
        m_items->push_back(item);
}
void AGraphicTrack::clearItems(){
    if(m_items)
        m_items->clear();
}
qreal AGraphicTrack::topValue(){
    if(!m_items){
        return 0;
    }
    qreal f_minimum = 0xffffffffffffffff;
    foreach(auto value,*m_items){
        f_minimum = f_minimum < value->topValue() ? f_minimum : value->topValue();
    }
    return f_minimum;
}

qreal AGraphicTrack::bottomValue(){
    if(!m_items){
        return 0;
    }
    qreal f_maximum = -999999999999999999;
    foreach(auto value,*m_items){
        f_maximum = f_maximum > value->bottomValue() ? f_maximum : value->bottomValue();
    }
    return f_maximum;
}

void AGraphicTrack::mousePressEvent(QGraphicsSceneMouseEvent *event){
    m_prevPoint = event->scenePos();
    if(is_openCloseClick(m_prevPoint)){
        openCloseClickHandler(m_prevPoint);
        m_isOpenCloseClick = true;
        return;
    }
    if(m_isOpen){
        if(event->button() == Qt::LeftButton){
            if(is_borderClick(m_prevPoint)){
                borderLeftClickHandler(m_prevPoint);
                m_isLeftBorderClick = true;
            }
            else if(is_headerClick(m_prevPoint)){
                headerLeftClickHandler(m_prevPoint);
                m_isLeftHeaderClick = true;
            }
            else if(is_CurvesClick(m_prevPoint)){
                curvesLeftClickHandler(m_prevPoint);
                m_isLeftCurvesClick = true;
            }
        }
        else if(event->button() == Qt::RightButton){
            if(is_borderClick(m_prevPoint)){
                borderRightClickHandler(m_prevPoint);
                m_isRightBorderClick = true;
            }
            else if(is_CurvesClick(m_prevPoint)){
                curvesRightClickHandler(m_prevPoint);
                m_isRightCurvesClick = true;
            }
        }
    }
}

void AGraphicTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isLeftBorderClick){
        borderLeftMoveHandler(f_curentPoint);
    }
    else if(m_isRightBorderClick){
        borderRightMoveHandler(f_curentPoint);
    }
    else if(m_isLeftHeaderClick){
        headerLeftMoveHandler(f_curentPoint);
    }
    else if(m_isLeftCurvesClick){
        curvesLeftMoveHandler(f_curentPoint);
    }
    else if(m_isRightCurvesClick){
        curvesRightMoveHandler(f_curentPoint);
    }
    m_prevPoint = f_curentPoint;
}

void AGraphicTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isLeftBorderClick){
        m_isLeftBorderClick = m_isOpenCloseClick = false;
        borderLeftReleaseHandler(f_curentPoint);
    }
    if(m_isRightBorderClick){
        m_isRightBorderClick = m_isOpenCloseClick = false;
        borderRightReleaseHandler(f_curentPoint);
    }
    else if(m_isLeftHeaderClick){
        m_isLeftHeaderClick = false;
        headerLeftReleaseHandler(f_curentPoint);
    }
    else if(m_isLeftCurvesClick){
        m_isLeftCurvesClick = false;
        curvesLeftReleaseHandler(f_curentPoint);
    }
    else if(m_isRightCurvesClick){
        m_isRightCurvesClick = false;
        curvesRightReleaseHandler(f_curentPoint);
    }
    //m_isBorderClick = m_isCurvesClick = m_isHeaderClick = m_isOpenCloseClick = false;
}

void AGraphicTrack::sceneUpdate(){
    if(m_needToRedraw){
        m_needToRedraw = false;
        m_endRedraw = false;
        start(QThread::InheritPriority);
    }
    else
        scene()->update();
}
