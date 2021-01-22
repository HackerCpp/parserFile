#ifndef AGRAPHICTRACK_H
#define AGRAPHICTRACK_H
#include <QThread>

#include "atrack.h"
#include <QDebug>
#include "objectoftheboard.h"
#include "rightborder.h"
#include "boardfortrack.h"
#include "itimscreater.h"
#include <QTabWidget>
#include <QDragEnterEvent>

enum TrackMode{NORMAL_MODE,DRAW_LABEL_MODE,CURVE_SHIFT_MODE};

class AGraphicTrack :  public ObjectOfTheBoard
{
    Q_OBJECT
protected:
    QPointF m_posLeftClick;
    QTimer m_timerLeftClick;
    QImage *m_infoPixMap,*m_curentHeader,*m_doubleHeader,*m_nameTrack;
    BoardForTrack *m_board;

    QWidget m_parent;

    QRectF m_boundingRect;
    int m_heightHeader;
    Border *m_border;
    int m_positionOfTheBorder;

    QList<AGraphicItem*> *m_items;
    ATrack *m_track;

    //Normal mode
    bool m_isRightClick,m_isLeftClick,m_isLeftBorderClick, m_isRightBorderClick,
    m_isLeftCurvesClick, m_isRightCurvesClick, m_isLeftHeaderClick,
    m_isRightHeaderClick, m_isOpenCloseClick, m_isOpen,
    m_isClickAddLabel;
    QPointF m_prevLabelPoint;
    LDLabelItem *m_lastLabelItem;

    //Curve shift mode
    bool m_isLinePress;

    QPointF m_prevPoint;
    TrackMode m_mode;
public:
    AGraphicTrack(ATrack *track,BoardForTrack *board);
    virtual ~AGraphicTrack()override;

    virtual void resize()override{}
    virtual void resizePictures()override{}

    qreal topValue();
    qreal bottomValue();


    virtual void activate(bool activate){Q_UNUSED(activate)}
    ATrack *trackInfo(){return m_track;}
    void addIteam(AGraphicItem* item);
    void clearItems();
    virtual void updateItemsParam();
    void changeMode(TrackMode mode){m_mode = mode;}


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override{Q_UNUSED(painter)}
    virtual void run()override{}
    virtual QRectF boundingRect()const override{return m_boundingRect;}
    virtual void swapPixMap()override;
    void deleteLabelItem(LDLabelItem * labelitem);

    void init();
    //Normal mode
    virtual bool is_openCloseClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_borderClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_CurvesClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_headerClick(QPointF point){Q_UNUSED(point)return false;}

    virtual void  clickRightHandler(QPointF point){Q_UNUSED(point)}
    virtual void  clickLeftHandler(QPointF point){Q_UNUSED(point)}
    virtual void  openCloseClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightClickHandler(QPointF point){Q_UNUSED(point)}

    virtual void  moveRightHandler(QPointF point){Q_UNUSED(point)}
    virtual void  moveLeftHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightMoveHandler(QPointF point){Q_UNUSED(point)}

    virtual void  releaseRightHandler(QPointF point){Q_UNUSED(point)}
    virtual void  releaseLeftHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightReleaseHandler(QPointF point){Q_UNUSED(point)}

    //Curve shift mode
    virtual void setLineCurveShift(QPointF point){Q_UNUSED(point)}
    virtual bool is_lineCurveShift(QPointF point){Q_UNUSED(point) return false;}
    virtual void lineCurveShiftPresHandler(QPointF point){Q_UNUSED(point)}
    virtual void lineCurveShiftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void lineCurveShiftReleaseHandler(QPointF point){Q_UNUSED(point)}

    void mousePressEventCurveShiftMode(QGraphicsSceneMouseEvent *event);
    void mouseMoveEventCurveShiftMode(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventCurveShiftMode(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEventCurveShiftMode(QGraphicsSceneMouseEvent *event);

    //Draw label mode
    void mousePressEventDrawLabelMode(QGraphicsSceneMouseEvent *event);
    void mouseMoveEventDrawLabelMode(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventDrawLabelMode(QGraphicsSceneMouseEvent *event);


    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;

    void mousePressEventNormalMode(QGraphicsSceneMouseEvent *event);
    void mouseMoveEventNormalMode(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventNormalMode(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEventNormalMode(QGraphicsSceneMouseEvent *event);




    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
signals:
    void changedPositionBorder(int position);
public slots:
    virtual void changeBegin(int newBegin){Q_UNUSED(newBegin)}
    void sceneUpdate()override;
    void timerLeftClick();

};

#endif // AGRAPHICTRACK_H
