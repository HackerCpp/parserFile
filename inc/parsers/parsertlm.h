#ifndef PARSERTLM_H
#define PARSERTLM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"
struct BlockTlm;
struct Pucket{           //***
    uint	time;
    char    dev_type;
    uchar	inf_type;
    QString data;
};
struct TlmPuck{          //**
    BlockTlm *parent;
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

    void findPuckFFFE(QString tlmPuckString,TlmPuck *tlmPuck);
    void findTlmPuckFFFE(QString blockTlmString,BlockTlm* blockTlm);
public:
    ParserTLM(QString hexTextTlmFile);
    QString getHexString();
    QList<BlockTlm> *getBlocks();
};

#endif // PARSERTLM_H
