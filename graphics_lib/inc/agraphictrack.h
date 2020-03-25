#ifndef AGRAPHICTRACK_H
#define AGRAPHICTRACK_H
#include <QThread>
#include <QGraphicsItem>
#include "atrack.h"
#include <QDebug>
#include "agraphicitem.h"


class AGraphicTrack : public QThread, public QGraphicsItem
{
     Q_OBJECT
protected:
    QList<AGraphicItem> *m_items;
    unsigned int pictureHeight,offsetUp;

    ATrack *m_track;
    QRectF *m_visibilitySquare;
    QImage *m_curentPixmap,*m_doublePixMap;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override{}
    virtual QRectF boundingRect()const override{}
    virtual void run()override{}
    virtual void swapPixMap(){}
    void redraw(){}
    void init();

public:
    AGraphicTrack();
    AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves);
    ~AGraphicTrack()override;
};

#endif // AGRAPHICTRACK_H
