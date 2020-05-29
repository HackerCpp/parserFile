#ifndef ABOARD_H
#define ABOARD_H

#include "iboard.h"
#include <QList>



class ABoard : public IBoard{
    QString m_name;
    QList<ATrack*> *m_tracks;
    QMap<QString,AItem*> *m_items;

public:
    ABoard();
    ABoard(const ABoard &object);
    virtual ~ABoard()override;

    virtual void setName(QString name)override;
    virtual void setTrack(ATrack *track)override;
    virtual void setItem(QString name, AItem *item)override;
    virtual QString name()override;
    virtual QList<ATrack*> *tracks()override;
    virtual QMap<QString,AItem*> *items()override;


};

#endif // ABOARD_H
