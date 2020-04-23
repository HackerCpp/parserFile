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



class AGraphicTrack :  public ObjectOfTheBoard
{
    Q_OBJECT

public:
    AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves,BoardForTrack *board);
    ~AGraphicTrack()override;

    virtual void resize()override{}
    virtual void resizePictures(){}

    qreal topValue();
    qreal bottomValue();
    virtual void activate(bool activate){}
    ATrack *trackInfo(){return m_track;}
protected:
    QImage *m_infoPixMap,*m_curentHeader,*m_doubleHeader;
    BoardForTrack *m_board;
    int m_topPositionPicture;
    QRectF m_boundingRect;
    int m_heightHeader;
    Border *m_border;
    int m_positionOfTheBorder;

    QList<AGraphicItem*> *m_items;
    ATrack *m_track;

    bool m_isLeftBorderClick,m_isRightBorderClick,
    m_isLeftCurvesClick,m_isRightCurvesClick,m_isLeftHeaderClick,
    m_isOpenCloseClick,m_isOpen;
    QPointF m_prevPoint;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override{}
    virtual void run()override{}
    virtual QRectF boundingRect()const override{return m_boundingRect;}
    virtual void swapPixMap();

    virtual void toSetTheLocationOfTheImageAfterDrawing(){}

    void init();

    virtual bool is_openCloseClick(QPointF point){return false;}
    virtual bool is_borderClick(QPointF point){return false;}
    virtual bool is_CurvesClick(QPointF point){return false;}
    virtual bool is_headerClick(QPointF point){return false;}

    virtual void  openCloseClickHandler(QPointF point){}
    virtual void  borderRightClickHandler(QPointF point){}
    virtual void  borderLeftClickHandler(QPointF point){}
    virtual void  curvesLeftClickHandler(QPointF point){}
    virtual void  curvesRightClickHandler(QPointF point){}
    virtual void  headerLeftClickHandler(QPointF point){}

    virtual void  borderLeftMoveHandler(QPointF point){}
    virtual void  borderRightMoveHandler(QPointF point){}
    virtual void  curvesLeftMoveHandler(QPointF point){}
    virtual void  curvesRightMoveHandler(QPointF point){}
    virtual void  headerLeftMoveHandler(QPointF point){}

    virtual void  borderLeftReleaseHandler(QPointF point){}
    virtual void  borderRightReleaseHandler(QPointF point){}
    virtual void  curvesLeftReleaseHandler(QPointF point){}
    virtual void  curvesRightReleaseHandler(QPointF point){}
    virtual void  headerLeftReleaseHandler(QPointF point){}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;



signals:
    virtual void changedPositionBorder(int position);
public slots:
    virtual void changeBegin(int newBegin){}
    void sceneUpdate();

};

#endif // AGRAPHICTRACK_H
