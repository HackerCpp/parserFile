#ifndef PARSERDEVICEDATATLM_H
#define PARSERDEVICEDATATLM_H

#include "inc/parsers/parsertlm.h"
#include "inc/reedsolomoncoding.h"
#include "inc/crc16.h"
#include <QDebug>

struct ServiseCm{
    int status;
    uint length;
    uchar segmentNum;
    uchar segmentCurr;
    uchar counter;
    uchar numModules;
    uint sysTime;
    uchar report;
    uchar tlmSpeed;
    ushort cmdCrc;
    ushort reserved0;
    uchar nCmd;
    uchar reply;
    uchar rsDeepness;
    uchar reserved1;
    ushort crc16;
};
struct Data{
    int status;
    QString data;
};

struct PacketDeviceData{
    ServiseCm serv;
    Data data;
};


class ParserDataCm{
    Crc16 crc;
    ReedSolomonCoding cod;
    QList<TlmPack> *tlmDeviceData;
    QList<PacketDeviceData> *deviceData;
    void findServiseFFFE();
public:
    ParserDataCm(QList<BlockTlm> *tlmBlocks);
};

#endif // PARSERDEVICEDATATLM_H
