#ifndef PARSERTLM_H
#define PARSERTLM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"

struct Pucket{           //***
    uint	time;
    QString dev_type;
    QString	inf_type;
    QString data;
};
struct TlmPack{          //**
    uchar state;
    ushort length;
    Pucket dataPucket;
};
struct BlockTlm{
    QString boom;
    QString name;
    QList<TlmPack> TlmPackList;
};



class ParserTLM{
    QString devTypeArray[10] //!< Названия приборов откуда(куда) могут приходить данные
                    = {"UPS1","UPS2","UPS3","UPS4","CPU","PLOT","SU","MTK","Reserve","ADSP"};
    QString infTypeArray[14] = {"GETVERSION","GETBLOCKINF","ERROR","STARTMON","WRITEDATA","STARTPROG",
                            "WRITEPARAM","GETPARAM","CMD","GETDATA","WRITEBLOCKINF","CLEARSECTOR","GETCLEARSTATUS","UIPCOMMAND"};
    QList<BlockTlm> *tlmBlocks;

    void findPuckFFFE(QString TlmPackString,TlmPack *TlmPack);
    void findTlmPackFFFE(QString blockTlmString,BlockTlm* blockTlm);
public:
    ParserTLM(QString hexTextTlmFile);
    QList<BlockTlm> *getBlocks();
};

#endif // PARSERTLM_H
