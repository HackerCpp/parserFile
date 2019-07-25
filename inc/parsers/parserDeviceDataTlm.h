#ifndef PARSERDEVICEDATATLM_H
#define PARSERDEVICEDATATLM_H

#include "inc/parsers/parsertlm.h"
#include "inc/reedsolomoncoding.h"
#include <QDebug>

struct Servise{

};

struct PacketDeviceData{
    QString serv;
    QString data;
};


class ParserDeviceDataTlm{
    ReedSolomonCoding cod;
    QList<TlmPack> *tlmDeviceData;

public:
    ParserDeviceDataTlm(QList<BlockTlm> *tlmBlocks);
};

#endif // PARSERDEVICEDATATLM_H
