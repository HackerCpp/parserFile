#include "agraphictrack.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QEvent>
#include "ldlabel.h"
#include "labelitem.h"


void AGraphicTrack::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    if(m_endRedraw){
        ptr = nullptr;
        return;
    }
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;
    ptr = m_curentHeader;
    m_curentHeader = m_doubleHeader;
    m_doubleHeader = ptr;
    ptr = nullptr;
    toSetTheLocationOfTheImageAfterDrawing();
}

void AGraphicTrack::init(){
    m_mode = NORMAL_MODE;//NORMAL_MODE;
    setFlags(ItemClipsToShape | ItemClipsChildrenToShape |ItemIgnoresTransformations);
    m_items = new QList<AGraphicItem*>;
    m_visibilitySquare.setRect(0,0,2000,2000);
    m_border = nullptr;
    m_isLeftBorderClick = m_isRightBorderClick = m_isLeftCurvesClick
    =  m_isRightCurvesClick = m_isLeftHeaderClick = m_isOpenCloseClick
    = m_isRightHeaderClick = m_isRightClick = m_isLeftClick = false;
    m_isLinePress = m_isClickAddLabel = false;
    m_isOpen = true;
    m_positionOfTheBorder = 0;
    m_boundingRect = QRectF(0,0,2000,2000);
    setAcceptDrops(true);
    connect(&m_timerLeftClick,&QTimer::timeout,this,&AGraphicTrack::timerLeftClick);
}

AGraphicTrack::AGraphicTrack(ATrack *track,BoardForTrack *board)
    : m_board(board), m_track(track){
    init();
}

AGraphicTrack::~AGraphicTrack(){
    if(m_items){
        m_items->clear();
        delete m_items;m_items = nullptr;
    }
    if(m_infoPixMap){delete m_infoPixMap;m_infoPixMap = nullptr;}
    if(m_curentHeader){delete m_curentHeader;m_curentHeader = nullptr;}
    if(m_doubleHeader){delete m_doubleHeader;m_doubleHeader = nullptr;}
    if(m_nameTrack){delete m_nameTrack;m_nameTrack = nullptr;}
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

void AGraphicTrack::deleteLabelItem(LDLabelItem * labelitem){
    m_board->deleteLabelItem(labelitem);
}

void AGraphicTrack::updateItemsParam(){
                                      //Дополнительная проверка для рисования на диск
    if(!m_items || !m_doublePixMap || m_doublePixMap->width() < 20)
        return;
    if(m_doublePixMap->isNull())
        return;
    foreach(auto grItem,*m_items){
        grItem->updateParam(m_doublePixMap->width());
    }
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
    qreal f_maximum = -999999999999999999.0;
    foreach(auto value,*m_items){
        f_maximum = f_maximum > value->bottomValue() ? f_maximum : value->bottomValue();
    }
    return f_maximum;
}


void AGraphicTrack::mousePressEvent(QGraphicsSceneMouseEvent *event){
    switch (m_mode) {
        case NORMAL_MODE:
            mousePressEventNormalMode(event);
            break;
        case CURVE_SHIFT_MODE:
            mousePressEventCurveShiftMode(event);
            break;
        case DRAW_LABEL_MODE:
            mousePressEventDrawLabelMode(event);
            break;

    }
}

void AGraphicTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    switch (m_mode) {
        case NORMAL_MODE:
            mouseMoveEventNormalMode(event);
            break;
        case CURVE_SHIFT_MODE:
            mouseMoveEventCurveShiftMode(event);
            break;
        case DRAW_LABEL_MODE:
            mouseMoveEventDrawLabelMode(event);
            break;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void AGraphicTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    switch (m_mode) {
        case NORMAL_MODE:
            mouseReleaseEventNormalMode(event);
            break;
        case CURVE_SHIFT_MODE:
            mouseReleaseEventCurveShiftMode(event);
            break;
        case DRAW_LABEL_MODE:
            mouseReleaseEventDrawLabelMode(event);
            break;
    }
}

void AGraphicTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    switch (m_mode) {
        case NORMAL_MODE:
            mouseDoubleClickEventNormalMode(event);
            break;
        case CURVE_SHIFT_MODE:
            mouseDoubleClickEventCurveShiftMode(event);
            break;
        case DRAW_LABEL_MODE:
            break;
    }
}

void AGraphicTrack::mousePressEventNormalMode(QGraphicsSceneMouseEvent *event){
    m_prevPoint = event->scenePos();
    if(is_openCloseClick(m_prevPoint)){
        openCloseClickHandler(m_prevPoint);
        m_isOpenCloseClick = true;
        return;
    }
    if(m_isOpen){
        if(event->button() == Qt::RightButton){
            if(is_borderClick(m_prevPoint)){
                borderRightClickHandler(m_prevPoint);
                m_isRightBorderClick = true;
            }
            else if(is_headerClick(m_prevPoint)){
                headerRightClickHandler(m_prevPoint);
                m_isRightHeaderClick = true;
            }
            else if(is_CurvesClick(m_prevPoint)){
                curvesRightClickHandler(m_prevPoint);
                m_isRightCurvesClick = true;
            }
            else{
                clickRightHandler(event->pos());
                m_isRightClick = true;
            }
        }
        else if(event->button() == Qt::LeftButton){
            if(is_borderClick(m_prevPoint)){
                borderLeftClickHandler(m_prevPoint);

                m_isLeftBorderClick = true;
            }
            else if(is_headerClick(m_prevPoint)){
                headerLeftClickHandler(m_prevPoint);
                m_isLeftHeaderClick = true;
            }
            else{
                m_posLeftClick = event->pos();
                m_timerLeftClick.start(200);
                //clickLeftHandler(event->pos());
            }
        }
    }
}

void AGraphicTrack::mouseMoveEventNormalMode(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isRightClick){
       moveRightHandler(f_curentPoint);
    }
    else if(m_isLeftClick){
        moveLeftHandler(f_curentPoint);
    }
    else if(m_isLeftBorderClick){
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

void AGraphicTrack::mouseReleaseEventNormalMode(QGraphicsSceneMouseEvent *event){
    m_timerLeftClick.stop();
    QPointF f_curentPoint = event->scenePos();
    if(m_isRightClick){
        releaseRightHandler(f_curentPoint);
        m_isRightClick = false;
    }
    else if(m_isLeftClick){
        releaseLeftHandler(f_curentPoint);
        m_isLeftClick = false;
    }
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
    else if(m_isRightHeaderClick){
        m_isRightHeaderClick = false;
        headerRightReleaseHandler(f_curentPoint);
    }
    else if(m_isRightCurvesClick){
        m_isRightCurvesClick = false;
        curvesRightReleaseHandler(f_curentPoint);
    }
    else if(m_isLeftCurvesClick){
        m_isLeftCurvesClick = false;
        curvesLeftReleaseHandler(f_curentPoint);
    }
}

void AGraphicTrack::mouseDoubleClickEventNormalMode(QGraphicsSceneMouseEvent *event){
    m_timerLeftClick.stop();
    m_prevPoint = event->scenePos();
    if(m_isOpen){
        if(event->button() == Qt::LeftButton){
            if(is_CurvesClick(m_prevPoint)){
                curvesLeftClickHandler(m_prevPoint);
                m_isLeftCurvesClick = true;
            }
        }
        else if(event->button() == Qt::RightButton){

        }
    }
}

void AGraphicTrack::mousePressEventCurveShiftMode(QGraphicsSceneMouseEvent *event){
    m_prevPoint = event->scenePos();
    if(m_isOpen){
        if(event->button() == Qt::RightButton){
            setLineCurveShift(m_prevPoint);
        }
        else if(event->button() == Qt::LeftButton){
            if(is_lineCurveShift(m_prevPoint)){
                m_isLinePress = true;
                lineCurveShiftPresHandler(m_prevPoint);
            }

        }
    }
}

void AGraphicTrack::mouseMoveEventCurveShiftMode(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isLinePress){
        lineCurveShiftMoveHandler(f_curentPoint);
    }


    m_prevPoint = f_curentPoint;
}

void AGraphicTrack::mouseReleaseEventCurveShiftMode(QGraphicsSceneMouseEvent *event){
    QPointF f_curentPoint = event->scenePos();
    if(m_isLinePress){
        m_isLinePress = false;
        lineCurveShiftReleaseHandler(f_curentPoint);
    }
}

void AGraphicTrack::mouseDoubleClickEventCurveShiftMode(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
}

void AGraphicTrack::timerLeftClick(){
    m_timerLeftClick.stop();
    clickLeftHandler(m_posLeftClick);
    m_isLeftClick = true;
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


//Draw label mode
void AGraphicTrack::mousePressEventDrawLabelMode(QGraphicsSceneMouseEvent *event){
    qreal f_deptOrTime = (event->pos().y() / m_board->scale());
    int f_xIndent = (event->pos().x() - this->boundingRect().x()) / m_board->pixelPerMm();
    LDLabel *m_ldLabel = new LDLabel(f_deptOrTime,m_board->isDrawTime(),m_track->number(),m_board->name()," ",f_xIndent);
    m_ldLabel->setSize(QSizeF(0.1,0.1));
    m_lastLabelItem = m_board->addLabel(m_ldLabel);
    m_lastLabelItem->addParentTrack(this);
    m_prevLabelPoint = event->scenePos();
    m_isClickAddLabel = true;

}

void AGraphicTrack::mouseMoveEventDrawLabelMode(QGraphicsSceneMouseEvent *event){
    if(m_isClickAddLabel){

        QPointF f_delta = m_prevLabelPoint - event->scenePos();
        m_lastLabelItem->setSize(QSizeF(m_lastLabelItem->size().width() - (f_delta.x() / m_board->pixelPerMm()),
                                        m_lastLabelItem->size().height() + (f_delta.y() / m_board->pixelPerMm())
                                        )
                                 );
        m_prevLabelPoint = event->scenePos();
        sceneUpdate();
    }

}

void AGraphicTrack::mouseReleaseEventDrawLabelMode(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    m_isClickAddLabel = false;
}
