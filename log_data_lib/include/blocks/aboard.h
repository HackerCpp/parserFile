#ifndef ABOARD_H
#define ABOARD_H

#include "iboard.h"
#include <QList>



class ABoard : public IBoard{
    QString m_name;
    QList<ATrack*>*m_tracks;

public:
    ABoard();
    virtual ~ABoard()override;

    virtual void setName(QString name)override;
    virtual void setTrack(ATrack *track)override;

    virtual QString name()override{return m_name;}

};

#endif // ABOARD_H
