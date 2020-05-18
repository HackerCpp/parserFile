#ifndef IBOARD_H
#define IBOARD_H

#include <QString>
#include "atrack.h"

class IBoard : public QObject{
    Q_OBJECT
public:
    IBoard(){}
    virtual ~IBoard(){}

    virtual void setName(QString name){}
    virtual void setTrack(ATrack *track){}
    virtual QList<ATrack*> *tracks(){return nullptr;}
    virtual QString name(){return QString();}
    virtual void setItem(QString name, AItem *item){}
    virtual QMap<QString,AItem*> *items(){return nullptr;}
};

#endif // IBOARD_H
