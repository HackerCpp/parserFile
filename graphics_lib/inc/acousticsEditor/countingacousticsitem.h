#ifndef COUNTINGACOUSTICSITEM_H
#define COUNTINGACOUSTICSITEM_H
#include "objectoftheboard.h"
#include "datacountingacoustics.h"

class CountingAcousticsItem : public ObjectOfTheBoard
{
    DataCountingAcoustics *m_dataAcoustics;
public:
    CountingAcousticsItem(DataCountingAcoustics *dataAcoustics,int width);
    ~CountingAcousticsItem()override{}


    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual QRectF boundingRect()const override;
    void changeVisibilityZone(QRectF visibilityZone);
    void changeSize(int width);
    void toSetTheLocationOfTheImageAfterDrawing()override;
    void run()override;
};

#endif // COUNTINGACOUSTICSITEM_H
