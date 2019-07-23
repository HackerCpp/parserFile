#ifndef PARSERTLM_H
#define PARSERTLM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"

struct Pucket{           //***
    uint	time;
    char    dev_type;
    uchar	inf_type;
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
    QList<BlockTlm> *tlmBlocks;

    void findPuckFFFE(QString TlmPackString,TlmPack *TlmPack);
    void findTlmPackFFFE(QString blockTlmString,BlockTlm* blockTlm);
public:
    ParserTLM(QString hexTextTlmFile);
    QList<BlockTlm> *getBlocks();
};

#endif // PARSERTLM_H
