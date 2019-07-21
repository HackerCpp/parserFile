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
struct TlmPuck{          //**
    uchar state;
    ushort length;
    Pucket dataPucket;
};
struct BlockTlm{
    QString boom;
    QString name;
    QList<TlmPuck> tlmPuckList;
};



class ParserTLM{
    QString string;
    QList<BlockTlm> *tlmBlocks;
public:
    ParserTLM(QString hexTextTlmFile);
    QString getHexString();
    QList<BlockTlm> *getBlocks();
};

#endif // PARSERTLM_H
