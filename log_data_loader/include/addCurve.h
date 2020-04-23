#ifndef ADDCURVE_H
#define ADDCURVE_H

#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QString>
#include <QThread>
#include <QTextCodec>
#include "headerblock.h"
#include "toolinfoblock.h"
#include "formsblock.h"
#include "datablock.h"
#include "unknownblock.h"
#include "curve.h"
#include "aboard.h"



class AddCurve : public  ALoaderLogData{


public:
    AddCurve();
    ~AddCurve();
    void addItemInTrack(ATrack *track);
    void addTrackInCurve(ABoard *board);
    void addCurveInBlock(QList<IBlock*> *m_block);
};

#endif // ADDCURVE_H
