#ifndef VERTICALTRACK_H
#define VERTICALTRACK_H
#include "agraphictrack.h"
#include "rightborder.h"

class VerticalTrack : public AGraphicTrack
{
    static int m_bottomY , m_topY;
    int m_curentWidth;
public:
    VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves);
    ~VerticalTrack()override;
private:
    void init();

    virtual bool is_openCloseClick(QPointF point) override;
    virtual bool is_borderClick(QPointF point)override;
    virtual bool is_CurvesClick(QPointF point)override;
    virtual bool is_headerClick(QPointF point)override;

    virtual void  openCloseClickHandler(QPointF point)override;
    virtual void  borderClickHandler(QPointF point)override;
    virtual void  curvesClickHandler(QPointF point)override;
    virtual void  headerClickHandler(QPointF point)override;

    virtual void  borderMoveHandler(QPointF point)override;
    virtual void  curvesMoveHandler(QPointF point)override;
    virtual void  headerMoveHandler(QPointF point)override;

    virtual void  borderReleaseHandler(QPointF point)override;
    virtual void  curvesReleaseHandler(QPointF point)override;
    virtual void  headerReleaseHandler(QPointF point)override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
public slots:
    virtual void changeBegin(int newBegin)override;


};

#endif // VERTICALTRACK_H
