#ifndef HEADERITEM_H
#define HEADERITEM_H
#include "objectoftheboard.h"
#include "agraphicitem.h"
#include "atrack.h"

class HeaderItem : public ObjectOfTheBoard
{
    QList<AGraphicItem*> *m_items;
    ATrack *m_track;
public:
    HeaderItem(ATrack *track);
    ~HeaderItem(){}

    void addIteam(AGraphicItem* item);
    ATrack *trackInfo(){return m_track;}

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual void toSetTheLocationOfTheImageAfterDrawing()override;
    virtual void run() override;
    void  swapImageHeader();
};

#endif // HEADERITEM_H
