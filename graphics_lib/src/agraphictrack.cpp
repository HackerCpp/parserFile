#include "agraphictrack.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>



void AGraphicTrack::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;
    /*ptr = m_curentHeader;
    m_curentHeader = m_doubleHeader;
    m_doubleHeader = ptr;*/
    ptr = nullptr;
    toSetTheLocationOfTheImageAfterDrawing();
}

void AGraphicTrack::init(){
     m_items = new QList<AGraphicItem*>;
     m_visibilitySquare.setRect(0,0,2000,2000);
     m_border = nullptr;
     m_isBorderClick = m_isCurvesClick = m_isHeaderClick = m_isOpenCloseClick = false;
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
        if(is_borderClick(m_prevPoint)){
            borderClickHandler(m_prevPoint);
            m_isBorderClick = true;
        }
        else if(is_headerClick(m_prevPoint)){
            headerClickHandler(m_prevPoint);
            m_isHeaderClick = true;
        }
        else if(is_CurvesClick(m_prevPoint)){
            curvesClickHandler(m_prevPoint);
            m_isCurvesClick = true;
        }
    }
}

void AGraphicTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isBorderClick){
        borderMoveHandler(f_curentPoint);
    }
    else if(m_isHeaderClick){
        headerMoveHandler(f_curentPoint);
    }
    else if(m_isCurvesClick){
        curvesMoveHandler(f_curentPoint);
    }
    m_prevPoint = f_curentPoint;
}

void AGraphicTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isBorderClick){
        m_isBorderClick = m_isOpenCloseClick = false;
        borderReleaseHandler(f_curentPoint);
    }
    else if(m_isHeaderClick){
        m_isHeaderClick = false;
        headerReleaseHandler(f_curentPoint);
    }
    else if(m_isCurvesClick){
        m_isCurvesClick = false;
        curvesReleaseHandler(f_curentPoint);
    }
    //m_isBorderClick = m_isCurvesClick = m_isHeaderClick = m_isOpenCloseClick = false;
}

void AGraphicTrack::sceneUpdate(){
    if(m_needToRedraw){
        m_needToRedraw = false;
        start(QThread::InheritPriority);
    }
    else
        scene()->update();
}
