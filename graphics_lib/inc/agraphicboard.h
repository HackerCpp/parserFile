#ifndef AGRAPHICBOARD_H
#define AGRAPHICBOARD_H
#include <QGraphicsView>
#include "agraphictrack.h"



class AGraphicBoard : public QGraphicsView
{
    Q_OBJECT

public:
    AGraphicBoard();
    ~AGraphicBoard(){}

    virtual void newTrack();
    bool addCurve(ICurve *curve,int indexTab);
};

#endif // AGRAPHICBOARD_H
