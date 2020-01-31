#ifndef GROUP_H
#define GROUP_H

#include "curvebaseitem.h"
#include "basegroup.h"
#include "headeritem.h"
#include <QMutex>


class Group : public BaseGroup{
    bool m_del;
    int k = 0;
    QMutex	m_mutex;
    int m_topPositionPicture;
    TabGroupSettings* m_settings;
    QImage *m_curentHeader,*m_doubleHeader;
    QVector<CurveBaseItem*> * m_curves;
    HeaderItem *m_headerItem;
    int m_sizeVisibleItem;
    int *m_headerTopOffset;
    QPointF m_prevPoint;
    bool m_isMoveHeader;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void run()override;
    virtual void swapPixMap()override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
public:
    void addCurve(CurveBaseItem *curve);
    Group(int leftX,int rightX,int *headerTopOffset);

public slots:
    void updateP(QPointF leftUp,QPointF rightDown,bool forceARedraw)override;
    void resize(int position);
};

#endif // GROUP_H
