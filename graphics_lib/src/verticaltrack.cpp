#include "verticaltrack.h"

VerticalTrack::VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves,BoardForTrack *board)
    : AGraphicTrack(track,curves,board)
{
    setZValue(0);
    m_curentWidth = m_track->Width();
    if(!track){
        qDebug() << "Передан нулевой указатель на трекИнфо, не получается создать трек.";
        return;
    }
    m_border = new RightBorder();
    qreal f_pixelPerMm = m_board->pixelPerMm();
    uint f_pictureHeight = m_board->pictureHeight();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * f_pixelPerMm - m_border->width();
    int f_pictureWidth = m_track->Width() * f_pixelPerMm  - m_border->width();
    m_curentPixmap = new QImage(f_pictureWidth,f_pictureHeight,QImage::Format_RGB444);
    m_doublePixMap = new QImage(f_pictureWidth,f_pictureHeight,QImage::Format_RGB444);
    m_boundingRect = QRectF(m_track->Begin() * f_pixelPerMm,f_topY,m_track->Width() * f_pixelPerMm,f_lengthY);
    QList <AItem*> *itemInfo = track->Items();
    int f_count = 0,y = 0;
    foreach(auto item,*itemInfo){
        QString name = item->name();
        ICurve *curve = curves->value(name);
        if(!curve){
            ++f_count;
            //qDebug() << "Curve null" << name;
        }
        else{
            ++y;
            m_items->push_back(ItimsCreater::createItem(item,curve,m_board,ItimsCreater::VERTICAL));
        }
    }
    if(f_count){
        qDebug() << "Кривые не все вставлены в трек, некоторые не найдены" << f_count << y;
    }
}

VerticalTrack::~VerticalTrack(){

}

void VerticalTrack::resize(){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    QGraphicsItem::prepareGeometryChange();
    m_boundingRect = QRectF(m_track->Begin() * f_pixelPerMm,f_topY,m_track->Width() * f_pixelPerMm,f_lengthY);
    update();
}

void VerticalTrack::init(){

}

void VerticalTrack::resizePictures(){
    if(m_doublePixMap){
        delete m_doublePixMap;
        m_doublePixMap = nullptr;
    }
    if(m_curentPixmap){
        delete m_curentPixmap;
        m_curentPixmap = nullptr;
    }
    if(!m_isOpen)
        return;
    qreal f_pixelPerMm = m_board->pixelPerMm();
    uint f_pictureHeight = m_board->pictureHeight();
    int f_pictureWidth = m_track->Width() * f_pixelPerMm  - m_border->width();
    m_curentPixmap = new QImage(f_pictureWidth,f_pictureHeight,QImage::Format_RGB444);
    m_doublePixMap = new QImage(f_pictureWidth,f_pictureHeight,QImage::Format_RGB444);
    redraw();
}

void VerticalTrack::drawGrid(qreal step_mm,QPainter *per,QPen pen){
    int f_width = m_doublePixMap->width();
    int f_height = m_doublePixMap->height();
    per->setPen(pen);
    for(qreal i = 0;i < f_width;i += step_mm){
        per->drawLine(QPointF(i,0),QPointF(i,f_height));
        if(m_needToRedraw)
            return;
    }
    for(qreal i = step_mm - fmod(m_visibilitySquare.y(),step_mm);i < f_height;i += step_mm){
        per->drawLine(QPointF(0,i),QPointF(f_width,i));
        if(m_needToRedraw)
            return;
    }
}


bool VerticalTrack::is_openCloseClick(QPointF point){
    QPointF   pointRightDown = QPointF(m_boundingRect.x() + m_boundingRect.width(),m_visibilitySquare.y() + m_border->width());
    QPointF   pointLeftUp = QPointF(pointRightDown.x() - m_border->width(),m_visibilitySquare.y());
    if(point.x() < pointRightDown.x() && point.x() > pointLeftUp.x() && point.y() < pointRightDown.y() && point.y() > pointLeftUp.y()){
        return true;
    }
    return false;
}

bool VerticalTrack::is_borderClick(QPointF point){
    setZValue(50);
    qreal f_pixelPerMm = m_board->pixelPerMm();

    int borderEnd = (m_track->Begin() + m_track->Width()) * f_pixelPerMm;
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
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();

    m_isOpen = !m_isOpen;
    QGraphicsItem::prepareGeometryChange();
    if(m_isOpen){
        m_track->setWidth(m_curentWidth);
    }
    else{
        m_curentWidth = m_track->Width();
        m_track->setWidth(m_border->width()/f_pixelPerMm);
    }
    m_boundingRect = QRectF(m_track->Begin() * f_pixelPerMm,f_topY,m_track->Width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * f_pixelPerMm - m_border->width();
    m_border->setopen(m_isOpen);
    resizePictures();
    update();

    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->Begin() + m_track->Width()) * f_pixelPerMm);
    else
        m_board->resize();
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
    qreal f_pixelPerMm = m_board->pixelPerMm();

    int newPosition = m_positionOfTheBorder - (m_prevPoint.x() - point.x());
    if(newPosition > m_track->Begin() * f_pixelPerMm){
        m_positionOfTheBorder = newPosition;
        update();
    }
}
void  VerticalTrack::curvesMoveHandler(QPointF point){

}
void  VerticalTrack::headerMoveHandler(QPointF point){

}

void  VerticalTrack::borderReleaseHandler(QPointF point){
    setZValue(0);
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    QGraphicsItem::prepareGeometryChange();
    m_track->setWidth(((m_positionOfTheBorder + m_border->width())/f_pixelPerMm) - m_track->Begin());
    m_border->click(false);
    m_boundingRect = QRectF(m_track->Begin() * f_pixelPerMm,f_topY,m_track->Width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * f_pixelPerMm - m_border->width();
    resizePictures();
    update();
    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->Begin() + m_track->Width()) * f_pixelPerMm);
    else
        m_board->resize();
}

void  VerticalTrack::curvesReleaseHandler(QPointF point){

}
void  VerticalTrack::headerReleaseHandler(QPointF point){

}

void VerticalTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    int LeftPos = m_track->Begin() * m_board->pixelPerMm();

    if(m_curentPixmap)
        painter->drawImage(QRect(LeftPos,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    if(m_border)
        painter->drawImage(QRect(m_positionOfTheBorder,m_visibilitySquare.y(),m_border->width(),m_border->height()),*m_border);
}

void VerticalTrack::toSetTheLocationOfTheImageAfterDrawing(){
    m_topPositionPicture =static_cast<int>(m_visibilitySquare.y() - m_board->offsetUp());
}

void VerticalTrack::run(){
    if(!m_doublePixMap)
        return;
    //QTime time = QTime::currentTime();
    QPainter painter(m_doublePixMap);
    //QPainter painterHeader(m_doubleHeader);
    //m_doubleHeader->fill(0);
    int f_height = m_doublePixMap->height();
    m_doublePixMap->fill(0xffffff);
    painter.setPen(QPen(QColor(0,0,0,200),1,Qt::DashLine));//Qt::DotLine  Qt::DashLine Qt::DashDotDotLine
    qreal f_pixelPerMm = m_board->pixelPerMm();
    if(m_track->IsGreed()){
        drawGrid(5 * f_pixelPerMm,&painter,QPen(QColor(0,0,0,200),0.5,Qt::DashLine));
        drawGrid(20 * f_pixelPerMm,&painter,QPen(QColor(0,0,0,200),1));
    }
    else{
        painter.drawLine(QPoint(0,0),QPoint(0,f_height));
    }
    int position = 0;
    foreach(auto item,*m_items){
        if(item){
            item->paint(&painter,&painter,m_visibilitySquare,position,&m_needToRedraw);
        }
        if(m_needToRedraw)
            return;
    }
    swapPixMap();
    //qDebug() << time.msecsTo( QTime::currentTime() );
}

void VerticalTrack::changeBegin(int newBegin){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();

    QGraphicsItem::prepareGeometryChange();
    m_track->setBegin(newBegin/f_pixelPerMm);
    m_boundingRect = QRectF(m_track->Begin() * f_pixelPerMm,f_topY,m_track->Width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->Begin() + m_track->Width()) * f_pixelPerMm - m_border->width();
    resizePictures();
    update();
    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->Begin() + m_track->Width()) * f_pixelPerMm);
    else
        m_board->resize();
}


