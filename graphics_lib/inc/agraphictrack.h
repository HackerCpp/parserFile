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



class AGraphicTrack :  public ObjectOfTheBoard
{
    Q_OBJECT

public:
    AGraphicTrack(ATrack *track,BoardForTrack *board);
    ~AGraphicTrack()override;

    virtual void resize()override{}
    virtual void resizePictures()override{}

    qreal topValue();
    qreal bottomValue();
    virtual void activate(bool activate){Q_UNUSED(activate)}
    ATrack *trackInfo(){return m_track;}
    void addIteam(AGraphicItem* item);
    void clearItems();
    virtual void updateItemsParam();
protected:
    QImage *m_infoPixMap,*m_curentHeader,*m_doubleHeader,*m_nameTrack;
    BoardForTrack *m_board;

    QRectF m_boundingRect;
    int m_heightHeader;
    Border *m_border;
    int m_positionOfTheBorder;

    QList<AGraphicItem*> *m_items;
    ATrack *m_track;

    bool m_isLeftBorderClick, m_isRightBorderClick,
    m_isLeftCurvesClick, m_isRightCurvesClick, m_isLeftHeaderClick,
    m_isRightHeaderClick, m_isOpenCloseClick, m_isOpen;
    QPointF m_prevPoint;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override{Q_UNUSED(painter)}
    virtual void run()override{}
    virtual QRectF boundingRect()const override{return m_boundingRect;}
    virtual void swapPixMap()override;


    //virtual void toSetTheLocationOfTheImageAfterDrawing()override{}

    void init();

    virtual bool is_openCloseClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_borderClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_CurvesClick(QPointF point){Q_UNUSED(point)return false;}
    virtual bool is_headerClick(QPointF point){Q_UNUSED(point)return false;}

    virtual void  openCloseClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftClickHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightClickHandler(QPointF point){Q_UNUSED(point)}


    virtual void  borderLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftMoveHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightMoveHandler(QPointF point){Q_UNUSED(point)}

    virtual void  borderLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  borderRightReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  curvesRightReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerLeftReleaseHandler(QPointF point){Q_UNUSED(point)}
    virtual void  headerRightReleaseHandler(QPointF point){Q_UNUSED(point)}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;


    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event)override{Q_UNUSED(event)}
signals:
    void changedPositionBorder(int position);
public slots:
    virtual void changeBegin(int newBegin){Q_UNUSED(newBegin)}
    void sceneUpdate();

};

#endif // AGRAPHICTRACK_H
