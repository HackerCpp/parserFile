#include "verticaltrack.h"

int VerticalTrack::m_bottomY = 2000;
int VerticalTrack::m_topY = -10;

VerticalTrack::VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves)
    : AGraphicTrack(track,curves)
{
    m_curentWidth = m_track->Width();
    if(!track){
        qDebug() << "Передан нулевой указатель на трекИнфо, не получается создать трек.";
        return;
    }
    m_border = new RightBorder();
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * m_pixelPerMm - m_border->width();
    int f_pictureWidth = m_track->Width() * m_pixelPerMm  - m_border->width();
    m_curentPixmap = new QImage(f_pictureWidth,pictureHeight,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(f_pictureWidth,pictureHeight,QImage::Format_ARGB32);
    m_boundingRect = QRectF(m_track->Begin() * m_pixelPerMm,m_topY,m_track->Width() * m_pixelPerMm,m_bottomY - m_topY);
    /*QList <AItem*> itemInfo = track->Items();
    //m_items->push_back(AGraphicItem::createItem(itemInfo.last(),curves->take(itemInfo.last().name())));*/
}

VerticalTrack::~VerticalTrack(){

}

void VerticalTrack::init(){

}

bool VerticalTrack::is_openCloseClick(QPointF point){
    QPointF   pointRightDown = QPointF(m_boundingRect.x() + m_boundingRect.width(),m_visibilitySquare.y() + m_border->width());
    QPointF   pointLeftUp = QPointF(pointRightDown.x() - m_border->width(),m_visibilitySquare.y());
    if(point.x() < pointRightDown.x() && point.x() > pointLeftUp.x() && point.y() < pointRightDown.y() && point.y() > pointLeftUp.y()){
        qDebug() << "Click";
        return true;
    }
    return false;
}

bool VerticalTrack::is_borderClick(QPointF point){
    int borderEnd = (m_track->Begin() + m_track->Width()) * m_pixelPerMm;
    int borderBegin = borderEnd - m_border->width();
    if(point.x() >= borderBegin && point.x() <= borderEnd)
        return true;
    return false;
}
bool VerticalTrack::is_CurvesClick(QPointF point){
    return false;
}
bool VerticalTrack::is_headerClick(QPointF point){
    return false;
}

void  VerticalTrack::openCloseClickHandler(QPointF point){
    m_isOpen = !m_isOpen;
    QGraphicsItem::prepareGeometryChange();
    if(m_isOpen){
        m_track->setWidth(m_curentWidth);
    }
    else{
        m_curentWidth = m_track->Width();
        m_track->setWidth(m_border->width()/m_pixelPerMm);
    }
    m_boundingRect = QRectF(m_track->Begin() * m_pixelPerMm,m_topY,m_track->Width() * m_pixelPerMm,m_bottomY - m_topY);
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * m_pixelPerMm - m_border->width();
    emit changedPositionBorder((m_track->Begin() + m_track->Width()) * m_pixelPerMm);
    m_border->setopen(m_isOpen);
    update();
}

void  VerticalTrack::borderClickHandler(QPointF point){
    m_border->click(true);
    m_boundingRect = m_visibilitySquare;
    update();
}
void  VerticalTrack::curvesClickHandler(QPointF point){

}
void  VerticalTrack::headerClickHandler(QPointF point){

}

void  VerticalTrack::borderMoveHandler(QPointF point){
    int newPosition = m_positionOfTheBorder - (m_prevPoint.x() - point.x());
    if(newPosition > m_track->Begin() * m_pixelPerMm){
        m_positionOfTheBorder = newPosition;
        update();
    }
}
void  VerticalTrack::curvesMoveHandler(QPointF point){

}
void  VerticalTrack::headerMoveHandler(QPointF point){

}

void  VerticalTrack::borderReleaseHandler(QPointF point){
    QGraphicsItem::prepareGeometryChange();
    m_track->setWidth(((m_positionOfTheBorder + m_border->width())/m_pixelPerMm) - m_track->Begin());
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * m_pixelPerMm - m_border->width();
    m_border->click(false);
    m_boundingRect = QRectF(m_track->Begin() * m_pixelPerMm,m_topY,m_track->Width() * m_pixelPerMm,m_bottomY - m_topY);
    emit changedPositionBorder((m_track->Begin() + m_track->Width()) * m_pixelPerMm);
    update();
}

void  VerticalTrack::curvesReleaseHandler(QPointF point){

}
void  VerticalTrack::headerReleaseHandler(QPointF point){

}

void VerticalTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_border)
        painter->drawImage(QRect(m_positionOfTheBorder,m_visibilitySquare.y(),m_border->width(),m_border->height()),*m_border);
     else
        qDebug() << "border для трека не создан, не может быть нарисован";
    if(m_curentPixmap)
        painter->drawImage(QRect(0,m_visibilitySquare.y() - offsetUp,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    else
        qDebug() << "track не может быть нарисован не создана картинка";
    //painter->setBrush(QBrush(QColor(255,230,230,230)));
    //painter->drawRect(QRect(m_track->Begin() * m_pixelPerMm - m_border->width(),m_visibilitySquare.y(),m_border->width(),m_border->height()));
}


void VerticalTrack::changeBegin(int newBegin){
    QGraphicsItem::prepareGeometryChange();
    m_track->setBegin(newBegin/m_pixelPerMm);
    if(m_isOpen){
        m_boundingRect = QRectF(m_track->Begin() * m_pixelPerMm,m_topY,m_track->Width() * m_pixelPerMm,m_bottomY - m_topY);
        m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * m_pixelPerMm - m_border->width();
        emit changedPositionBorder((m_track->Begin() + m_track->Width()) * m_pixelPerMm);
    }
    else{
        m_boundingRect = QRectF(m_track->Begin() * m_pixelPerMm,m_topY,m_border->width(),m_bottomY - m_topY);
        m_positionOfTheBorder = m_track->Begin() * m_pixelPerMm;
        emit changedPositionBorder((m_track->Begin() * m_pixelPerMm) + m_border->width());
    }
}


