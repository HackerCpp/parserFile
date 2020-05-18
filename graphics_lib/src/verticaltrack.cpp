#include "verticaltrack.h"
#include "acuItem.h"
#include "qgraphicsscene.h"
#include "settingsitem.h"
#include <QTabWidget>
#include "shortcut.h"
#include "SFML/Graphics.hpp"
#include "curveeditor.h"
#include <QApplication>
#include <QDrag>
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
using namespace sf;

VerticalTrack::VerticalTrack(ATrack *track,BoardForTrack *board)
    : AGraphicTrack(track,board)
{
    setZValue(0);
    m_curentWidth = m_track->width();
    if(!track){
        qDebug() << "Передан нулевой указатель на трекИнфо, не получается создать трек.";
        return;
    }
    m_selectingArea = nullptr;

    m_curvesMenu = new QMenu("&CurvesMenu");
    m_curvesMenu->addAction("&Curve settings",this, SLOT(openSettingsActiveItems()));
    m_curvesMenu->addAction("&Curve edit",this, SLOT(openEditorActiveItems()));
    m_curvesMenu->setMaximumSize(1000,1000);

    m_trackMenu = new QMenu("&TrackMenu");
    m_trackMenu->addAction("&Track settings",this, SLOT(openSettingsTrack()));
    m_trackMenu->addAction("&Insert a track on the right",this, SLOT(insertRightTrack()));
    m_trackMenu->addAction("&Insert a track on the left",this, SLOT(insertLeftTrack()));
    m_trackMenu->addAction("&Delete a track",this, SLOT(deleteTrack()));
    m_trackMenu->addAction("&Open curve browser",this, SLOT(openCurveBrowser()));
    m_border = new RightBorder();
    qreal f_pixelPerMm = m_board->pixelPerMm();
    uint f_pictureHeight = m_board->pictureHeight();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    m_positionOfTheBorder = (m_track->begin() + m_track->width()) * f_pixelPerMm - m_border->width();
    int f_pictureWidth = m_track->width() * f_pixelPerMm  - m_border->width();
    QImage::Format f_format = m_board->formatPicture();
    m_curentPixmap = new QImage(f_pictureWidth,f_pictureHeight,f_format);
    m_doublePixMap = new QImage(f_pictureWidth,f_pictureHeight,f_format);
    m_curentHeader = new QImage(f_pictureWidth,3000,QImage::Format_ARGB4444_Premultiplied);
    m_doubleHeader = new QImage(f_pictureWidth,3000,QImage::Format_ARGB4444_Premultiplied);
    m_infoPixMap = new QImage(f_pictureWidth,30,QImage::Format_ARGB4444_Premultiplied);
    m_nameTrack = new QImage(100,30,QImage::Format_ARGB32);
    m_nameTrack->fill(0x0);
    QPainter per(m_nameTrack);
    per.setPen(QPen(QColor(100,100,100,100)));

    per.setFont(QFont("Times", 14, QFont::Bold));
    per.drawText(QRect(0,0,m_nameTrack->width(),m_nameTrack->height()),Qt::AlignHCenter|Qt::AlignVCenter,m_track->name());

    m_boundingRect = QRectF(m_track->begin() * f_pixelPerMm,f_topY,m_track->width() * f_pixelPerMm,f_lengthY);
    updateItemsParam();
}

VerticalTrack::~VerticalTrack(){
    deleteAllPictures();
}

void VerticalTrack::resize(){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    QGraphicsItem::prepareGeometryChange();
    m_boundingRect = QRectF(m_track->begin() * f_pixelPerMm,f_topY,m_track->width() * f_pixelPerMm,f_lengthY);
    update();
}

void VerticalTrack::deleteAllPictures(){
    m_endRedraw = true;
    wait();
    if(m_curentPixmap){
        delete m_curentPixmap;
        m_curentPixmap = nullptr;
    }
    if(m_doublePixMap){
        delete m_doublePixMap;
        m_doublePixMap = nullptr;
    }
    if(m_curentHeader){
        delete m_curentHeader;
        m_curentHeader = nullptr;
    }
    if(m_doubleHeader){
        delete m_doubleHeader;
        m_doubleHeader = nullptr;
    }
}

void VerticalTrack::activate(bool activate){
    if(activate){
        resizePictures();
        redraw();
    }
    else{
        deleteAllPictures();
    }
}

void VerticalTrack::init(){

}

void VerticalTrack::resizePictures(){

    deleteAllPictures();

    if(!m_isOpen)
        return;
    qreal f_pixelPerMm = m_board->pixelPerMm();
    uint f_pictureHeight = m_board->pictureHeight();
    int f_pictureWidth = m_track->width() * f_pixelPerMm  - m_border->width();

    QImage *f_img = m_infoPixMap;
    m_infoPixMap = new QImage(f_pictureWidth,30,QImage::Format_ARGB4444_Premultiplied);
    m_infoPixMap->fill(0x0);
    QPainter painterCurent(m_infoPixMap);
    painterCurent.setFont(QFont("Times", 10, QFont::Bold));
    painterCurent.drawText(10,15,"download");
    if(f_img){
        delete f_img;
        f_img = nullptr;
    }
    QImage::Format f_format = m_board->formatPicture();
    m_curentPixmap = new QImage(f_pictureWidth,f_pictureHeight,f_format);
    m_curentPixmap->fill(0xffffffff);
    m_doublePixMap = new QImage(f_pictureWidth,f_pictureHeight,f_format);
    m_curentHeader = new QImage(f_pictureWidth,3000,QImage::Format_ARGB4444_Premultiplied);
    m_doubleHeader = new QImage(f_pictureWidth,3000,QImage::Format_ARGB4444_Premultiplied);
    updateItemsParam();
    redraw();
}

void VerticalTrack::drawGrid(qreal step_mm,QPainter *per,QPen pen){
    qreal f_width = m_doublePixMap->width();
    qreal f_height = m_doublePixMap->height();
    per->setPen(pen);
    for(qreal i = 0;i < f_width;i += step_mm){
        per->drawLine(QPointF(i,0),QPointF(i,f_height));
        if(m_endRedraw)
            return;
    }
    for(qreal i = step_mm - fmod(m_visibilitySquare.y(),step_mm);i < f_height;i += step_mm){
        per->drawLine(QPointF(0,i),QPointF(f_width,i));
        if(m_endRedraw)
            return;
    }
}

void VerticalTrack::setActiveSelectingArea(){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    uint f_pictureHeight = m_board->pictureHeight();
    int f_pictureWidth = m_track->width() * f_pixelPerMm  - m_border->width();
    QImage::Format f_format =  QImage::Format_Grayscale8;

    QImage f_image(f_pictureWidth,f_pictureHeight,f_format);
    QPainter painter(&f_image);
    int f_x = m_selectingArea->left()-(m_track->begin() * f_pixelPerMm);
    int f_y = m_selectingArea->top() - m_visibilitySquare.y() + m_board->offsetUp();
    int f_width = m_selectingArea->right() - m_selectingArea->left();
    int f_height = m_selectingArea->bottom() - m_selectingArea->top();
    QRectF area(f_x,f_y,f_width,f_height);
    bool isActive = false;
    m_сurrentСountOfActive = 0;
    foreach(auto item, *m_items){
        isActive = item->isLocatedInTheArea(area,m_visibilitySquare,&painter);
        item->setActive(isActive);
        m_сurrentСountOfActive += isActive ? 1 : 0;
    }
    redraw();
}

void VerticalTrack::startDrag(QPointF point){
    QMimeData *f_mimeData = nullptr;

    QPoint f_pointInHeaderPicture = QPoint(point.x() - (m_track->begin() * m_board->pixelPerMm()),point.y() - m_visibilitySquare.y() - m_board->positionHeader());
    QImage *f_image = new QImage(200,100,QImage::Format_ARGB32);
    bool flag = false;
    int position = 0;
    //QTextStream *f_stream = new QTextStream()
    foreach(auto grItem, *m_items){
        if(grItem->isClickHeaderArea(f_pointInHeaderPicture)){
            f_image->fill(0x0);
            grItem->drawHeader(new QPainter(f_image),position,&flag);
            f_mimeData = new QMimeData;
            f_mimeData->setText(QString::number(reinterpret_cast<long long>(grItem)));
            grItem->itemInfo()->setVisible(AItem::BOARD_GRAPH_VIEW,false);
            m_items->removeOne(grItem);
            break;
        }
    }
    if(f_mimeData){
            QDrag *f_drag = new QDrag(this);
            f_drag->setMimeData(f_mimeData);
            f_drag->setPixmap(QPixmap::fromImage(*f_image));


            f_drag->exec();
    }
    redraw();
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
    qreal f_pixelPerMm = m_board->pixelPerMm();

    int borderEnd = (m_track->begin() + m_track->width()) * f_pixelPerMm;
    int borderBegin = borderEnd - m_border->width();
    if(point.x() >= borderBegin && point.x() <= borderEnd){

        return true;
    }
    return false;
}

bool VerticalTrack::is_CurvesClick(QPointF point){
    Q_UNUSED(point)
    return true;
}

bool VerticalTrack::is_headerClick(QPointF point){
    int f_position = m_visibilitySquare.y() + m_board->positionHeader();
    if(point.y() > f_position && point.y() < (f_position + m_heightHeader)){
        return true;
    }
    return false;
}

void  VerticalTrack::openCloseClickHandler(QPointF point){
    Q_UNUSED(point)
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();

    m_isOpen = !m_isOpen;
    QGraphicsItem::prepareGeometryChange();
    if(m_isOpen){
        m_track->setWidth(m_curentWidth);
    }
    else{
        m_curentWidth = m_track->width();
        m_track->setWidth(m_border->width()/f_pixelPerMm);
    }
    m_boundingRect = QRectF(m_track->begin() * f_pixelPerMm,f_topY,m_track->width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->begin() + m_track->width()) * f_pixelPerMm - m_border->width();
    m_border->setopen(m_isOpen);
    resizePictures();
    update();

    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->begin() + m_track->width()) * f_pixelPerMm);
    else
        m_board->resize();
}

void  VerticalTrack::borderLeftClickHandler(QPointF point){
    Q_UNUSED(point)
    setZValue(50);
    m_border->click(true);
    m_boundingRect = m_visibilitySquare;
    update();
}

void  VerticalTrack::borderRightClickHandler(QPointF point){
    Q_UNUSED(point)

}

void  VerticalTrack::curvesLeftClickHandler(QPointF point){
    m_curvesMenu->hide();
    if(!m_selectingArea){
        m_selectingArea = new SelectingArea(QRectF(point.x(),point.y(),1,1));
        scene()->addItem(m_selectingArea);
    }
    m_selectingArea->setPosition(point);
    m_selectingArea->setWidth(1);
    m_selectingArea->setHeight(1);
    m_selectingArea->show();
}

void  VerticalTrack::curvesRightClickHandler(QPointF point){
    Q_UNUSED(point)

}

void  VerticalTrack::headerLeftClickHandler(QPointF point){
    Q_UNUSED(point)
    m_ptDragPos = point;
}

void  VerticalTrack::headerRightClickHandler(QPointF point){
    QPoint f_pointInHeaderPicture = QPoint(point.x() - (m_track->begin() * m_board->pixelPerMm()),point.y() - m_visibilitySquare.y() - m_board->positionHeader());
    bool isActive = false;
    m_сurrentСountOfActive = 0;
    foreach(auto grItem, *m_items){
        isActive = grItem->isClickHeaderArea(f_pointInHeaderPicture);
        grItem->setActive(isActive);
        m_сurrentСountOfActive += isActive;
    }
    redraw();
}

void  VerticalTrack::borderLeftMoveHandler(QPointF point){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int newPosition = m_positionOfTheBorder - (m_prevPoint.x() - point.x());
    if(newPosition > m_track->begin() * f_pixelPerMm){
        m_positionOfTheBorder = newPosition;
        update();
    }
}

void  VerticalTrack::borderRightMoveHandler(QPointF point){
    Q_UNUSED(point)
}

void  VerticalTrack::curvesLeftMoveHandler(QPointF point){
    int f_height =  m_selectingArea->height() - (m_prevPoint.y() - point.y());
    int f_width =  m_selectingArea->width() - (m_prevPoint.x() - point.x());
    if(m_selectingArea->boundingRect().x() + f_width < ((m_track->begin() + m_track->width()) * m_board->pixelPerMm()) - m_border->width()
       && m_selectingArea->boundingRect().x() + f_width > m_track->begin() * m_board->pixelPerMm()){
        m_selectingArea->setWidth(f_width);
    }
    m_selectingArea->setHeight(f_height);
    m_selectingArea->update();
    scene()->update();
}

void  VerticalTrack::curvesRightMoveHandler(QPointF point){
    Q_UNUSED(point)
}

void  VerticalTrack::headerLeftMoveHandler(QPointF point){
    int distance = abs(m_ptDragPos.x() - point.x());
    if(distance > 20 * m_board->pixelPerMm()){
        startDrag(point);
        m_isLeftHeaderClick = false;
        return;
    }
    int f_newPos = m_board->positionHeader() - (m_prevPoint.y() - point.y());
    if(f_newPos <  m_visibilitySquare.height() - 50 && (f_newPos + m_heightHeader) >  50)
        m_board->setPositionHeader(f_newPos);
    scene()->update();
}

void  VerticalTrack::borderLeftReleaseHandler(QPointF point){
    Q_UNUSED(point)
    setZValue(0);
    m_infoPixMap->fill(0x0);
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();
    QGraphicsItem::prepareGeometryChange();
    m_track->setWidth(((m_positionOfTheBorder + m_border->width())/f_pixelPerMm) - m_track->begin());
    m_border->click(false);
    m_boundingRect = QRectF(m_track->begin() * f_pixelPerMm,f_topY,m_track->width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->begin() + m_track->width()) * f_pixelPerMm - m_border->width();
    resizePictures();
    update();
    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->begin() + m_track->width()) * f_pixelPerMm);
    else
        m_board->resize();
}

void  VerticalTrack::borderRightReleaseHandler(QPointF point){
    Q_UNUSED(point)
}

void  VerticalTrack::curvesLeftReleaseHandler(QPointF point){
    Q_UNUSED(point)
    m_selectingArea->hide();
    scene()->update();
    setActiveSelectingArea();
    if(m_сurrentСountOfActive){
        m_curvesMenu->move(QCursor::pos());
        m_curvesMenu->show();
    }
}

void  VerticalTrack::curvesRightReleaseHandler(QPointF point){
    Q_UNUSED(point)
    m_trackMenu->move(QCursor::pos());
    m_trackMenu->show();
}

void  VerticalTrack::headerLeftReleaseHandler(QPointF point){
    Q_UNUSED(point)
}
void  VerticalTrack::headerRightReleaseHandler(QPointF point){
    Q_UNUSED(point)
    if(m_сurrentСountOfActive){
        m_curvesMenu->move(QCursor::pos());
        m_curvesMenu->show();
    }
}

void VerticalTrack::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
    //qDebug() << "drEnterEvent";
}

void VerticalTrack::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    //qDebug() << "drLeaveEvent" << m_track->name();
}

void VerticalTrack::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
   // qDebug() << "drMoveEvent";
}

void VerticalTrack::dropEvent(QGraphicsSceneDragDropEvent *event){
    bool ok = false;
     AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->text().toLongLong(&ok));
     if(f_item && ok){
        f_item->itemInfo()->setVisible(AItem::BOARD_GRAPH_VIEW,true);
        f_item->itemInfo()->setNumberOfTrack(m_track->number());
        f_item->updateParam(m_doublePixMap->width());
        addIteam(f_item);
     }
     redraw();
}

void VerticalTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    int LeftPos = m_track->begin() * m_board->pixelPerMm();
    int f_rightPos = (m_track->begin() + m_track->width()) * m_board->pixelPerMm();

    if(m_curentPixmap)
        painter->drawImage(QRect(LeftPos,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    if(m_curentHeader)
        painter->drawImage(QRect(LeftPos,m_visibilitySquare.y() + m_board->positionHeader(),m_curentHeader->width(),m_curentHeader->height()),*m_curentHeader);
    if(m_border)
        painter->drawImage(QRect(m_positionOfTheBorder,m_visibilitySquare.y(),m_border->width(),m_border->height()),*m_border);
    if(m_infoPixMap){
        painter->drawImage(QRect(LeftPos,m_visibilitySquare.y(),m_infoPixMap->width(),m_infoPixMap->height()),*m_infoPixMap);
    }
    if(m_nameTrack){
        painter->drawImage(QRect(f_rightPos - m_nameTrack->width() - m_border->width() - 5,m_visibilitySquare.y(),m_nameTrack->width(),m_nameTrack->height()),*m_nameTrack);
    }
}

void VerticalTrack::toSetTheLocationOfTheImageAfterDrawing(){
    m_topPositionPicture = static_cast<int>(m_visibilitySquare.y() - m_board->offsetUp());
}

void VerticalTrack::run(){
    if(!m_doublePixMap || !m_infoPixMap || !m_doubleHeader)
        return;
    if(m_visibilitySquare.x() > boundingRect().x() + boundingRect().width()
    || m_visibilitySquare.x() + m_visibilitySquare.width() < boundingRect().x()){
        return;
    }
    //QTime time = QTime::currentTime();
    QPainter painter(m_doublePixMap);
    QPainter painterCurent(m_infoPixMap);
    QPainter painterHeader(m_doubleHeader);
    painterCurent.setBrush(QBrush(Qt::white));
    painterCurent.setFont(QFont("Times", 10, QFont::Bold));
    painterCurent.drawText(10,15,"download");
    int f_height = m_doublePixMap->height();
    m_doublePixMap->fill(0xffffff);
    m_doubleHeader->fill(0x0);
    painter.setPen(QPen(QColor(0,0,0,200),1,Qt::DashLine));//Qt::DotLine  Qt::DashLine Qt::DashDotDotLine
    qreal f_pixelPerMm = m_board->pixelPerMm();
    if(m_track->isGreed()){
        drawGrid(5 * f_pixelPerMm,&painter,QPen(QColor(0,0,0,200),0.5,Qt::DashLine));
        drawGrid(20 * f_pixelPerMm,&painter,QPen(QColor(0,0,0,200),1));
    }
    else{
        painter.drawLine(QPoint(0,0),QPoint(0,f_height));
    }
    int f_position = 0;

    foreach(auto item,*m_items){
        if(item){
            item->paint(&painter,&painterHeader,m_visibilitySquare,f_position,&m_endRedraw);
        }
        if(m_endRedraw){
            m_infoPixMap->fill(0x0);
            return;
        }
    }
    m_infoPixMap->fill(0x0);
    m_heightHeader = f_position;

    swapPixMap();
    //qDebug() << time.msecsTo(QTime::currentTime());
}

void VerticalTrack::changeBegin(int newBegin){
    qreal f_pixelPerMm = m_board->pixelPerMm();
    int f_topY = m_board->top();
    uint f_lengthY = m_board->length();

    QGraphicsItem::prepareGeometryChange();
    m_track->setBegin(newBegin/f_pixelPerMm);
    m_boundingRect = QRectF(m_track->begin() * f_pixelPerMm,f_topY,m_track->width() * f_pixelPerMm,f_lengthY);
    m_positionOfTheBorder = (m_track->begin() + m_track->width()) * f_pixelPerMm - m_border->width();
    //resizePictures();
    update();
    const QMetaMethod valueChangedSignal = QMetaMethod::fromSignal(&AGraphicTrack::changedPositionBorder);
    if(isSignalConnected(valueChangedSignal))
        emit changedPositionBorder((m_track->begin() + m_track->width()) * f_pixelPerMm);
    else
        m_board->resize();
}

void VerticalTrack::applySettings(){
    updateItemsParam();
    redraw();
}

void VerticalTrack::openSettingsActiveItems(){
    SettingsItems *f_tabWidget = new SettingsItems();
    connect(f_tabWidget,&SettingsItems::changeSettings,this,&VerticalTrack::applySettings);
    int f_count = 0;
    foreach(auto item,*m_items){
        if(item->isActive()){
            f_tabWidget->addItem(item);
            f_count++;
        }
    }

}

void VerticalTrack::insertLeftTrack(){
    m_board->insertNewTrack(m_track->number(),InsertPossition::LEFT);
}

void VerticalTrack::insertRightTrack(){
    m_board->insertNewTrack(m_track->number(),InsertPossition::RIGHT);
}

void VerticalTrack::deleteTrack(){

}

void VerticalTrack::openSettingsTrack(){

}

void VerticalTrack::openCurveBrowser(){
    m_board->openCurveSettings();
}

void VerticalTrack::openEditorActiveItems(){
    foreach(auto item,*m_items){
        if(item->isActive()){
            CurveEditor *f_curveEditor  = new CurveEditor(item);
            connect(f_curveEditor,&CurveEditor::changeSettings,this,&VerticalTrack::applySettings);
            f_curveEditor->show();
        }
    }
}
