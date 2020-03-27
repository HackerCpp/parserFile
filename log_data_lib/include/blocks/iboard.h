#ifndef IBOARD_H
#define IBOARD_H

#include <QString>
#include "atrack.h"

class IBoard{
public:
    IBoard(){}
    virtual ~IBoard(){}

    virtual void setName(QString name){}
    virtual void setTrack(ATrack *track){}
    virtual QList<ATrack*> *tracks(){return nullptr;}
    virtual QString name(){return QString();}
};

#endif // IBOARD_H
