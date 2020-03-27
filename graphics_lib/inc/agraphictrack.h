#ifndef AGRAPHICTRACK_H
#define AGRAPHICTRACK_H
#include <QThread>

#include "atrack.h"
#include <QDebug>
#include "agraphicitem.h"
#include "objectoftheboard.h"
#include "rightborder.h"


class AGraphicTrack :  public ObjectOfTheBoard
{
    Q_OBJECT
protected:
    QRectF m_boundingRect;
    Border *m_border;
    int m_positionOfTheBorder;
    QList<AGraphicItem> *m_items;
    static unsigned int pictureHeight,offsetUp;
    ATrack *m_track;
    QImage *m_curentPixmap,*m_doublePixMap;
    bool m_isBorderClick,m_isCurvesClick,m_isHeaderClick,m_isOpenCloseClick,m_isOpen;
    QPointF m_prevPoint;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override{}
    virtual void run()override{}
    virtual QRectF boundingRect()const override{return m_boundingRect;}
    virtual void swapPixMap(){}
    void redraw(){}
    void init();

    virtual bool is_openCloseClick(QPointF point){return false;}
    virtual bool is_borderClick(QPointF point){return false;}
    virtual bool is_CurvesClick(QPointF point){return false;}
    virtual bool is_headerClick(QPointF point){return false;}

    virtual void  openCloseClickHandler(QPointF point){}
    virtual void  borderClickHandler(QPointF point){}
    virtual void  curvesClickHandler(QPointF point){}
    virtual void  headerClickHandler(QPointF point){}

    virtual void  borderMoveHandler(QPointF point){}
    virtual void  curvesMoveHandler(QPointF point){}
    virtual void  headerMoveHandler(QPointF point){}

    virtual void  borderReleaseHandler(QPointF point){}
    virtual void  curvesReleaseHandler(QPointF point){}
    virtual void  headerReleaseHandler(QPointF point){}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;


public:
    AGraphicTrack();
    AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves);
    ~AGraphicTrack()override;
signals:
    virtual void changedPositionBorder(int position);
public slots:
    virtual void changeBegin(int newBegin){}

};

#endif // AGRAPHICTRACK_H
