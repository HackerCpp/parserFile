#include "agraphictrack.h"
#include <QGraphicsSceneMouseEvent>

unsigned int AGraphicTrack::pictureHeight = 6000;
unsigned int AGraphicTrack::offsetUp = 1000;

void AGraphicTrack::init(){
     m_items = new QList<AGraphicItem>;
     m_visibilitySquare.setRect(0,0,2000,2000);
     m_border = nullptr;
     m_isBorderClick = m_isCurvesClick = m_isHeaderClick = m_isOpenCloseClick = false;
     m_isOpen = true;
     m_positionOfTheBorder = 0;
     m_boundingRect = QRectF(0,0,2000,2000);
}

AGraphicTrack::AGraphicTrack(){
    init();
}

AGraphicTrack::AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves)
    : m_track(track){
    init();
}

AGraphicTrack::~AGraphicTrack(){

}

void AGraphicTrack::mousePressEvent(QGraphicsSceneMouseEvent *event){
    m_prevPoint = event->scenePos();
    if(is_openCloseClick(m_prevPoint)){
        openCloseClickHandler(m_prevPoint);
        m_isOpenCloseClick = true;
    }
    else if(is_borderClick(m_prevPoint)){
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
        borderReleaseHandler(f_curentPoint);
    }
    else if(m_isHeaderClick){
        headerReleaseHandler(f_curentPoint);
    }
    else if(m_isCurvesClick){
        curvesReleaseHandler(f_curentPoint);
    }
    m_isBorderClick = m_isCurvesClick = m_isHeaderClick = m_isOpenCloseClick = false;
}

