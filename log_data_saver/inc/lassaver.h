#ifndef LASSAVER_H
#define LASSAVER_H
#include "asaverlogdata.h"

class LASSaver : public ASaverLogData
{
public:
    LASSaver();
    ~LASSaver()override;

    bool save()override;
    bool isReady()override;
};

#endif // LASSAVER_H
