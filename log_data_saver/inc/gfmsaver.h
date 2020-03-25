#ifndef GFMSAVER_H
#define GFMSAVER_H

#include "LogDataSaver_global.h"
#include <QThread>
#include "asaverlogdata.h"

class SAVER_EXPORT GFMSaver: public ASaverLogData , QThread{
public:
    GFMSaver();
    ~GFMSaver()override;

    bool save()override;
    bool isReady()override;

    bool setBlocks(QList<IBlock*> *blocks)override;
};

#endif // GFMSAVER_H
