#ifndef ITIMSCREATER_H
#define ITIMSCREATER_H
#include "agraphicitem.h"

class ItimsCreater{

public:
    enum OrientationItem{VERTICAL,HORIZONTAL};

    ItimsCreater(){}
    ~ItimsCreater(){}

    static AGraphicItem *createItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board,OrientationItem orientation);
};

#endif // ITIMSCREATER_H
