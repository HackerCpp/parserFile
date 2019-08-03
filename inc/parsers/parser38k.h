#ifndef PARSER38K_H
#define PARSER38K_H
#include "inc/parsers/parsertlm.h"
#include "inc/reedsolomoncoding.h"
#include "inc/crc16.h"
#include <QDebug>

struct Servise38k{
    unsigned int systemTime;
    unsigned short transmissionCounter;
    unsigned char totalModules;
    unsigned char speedTelemetry;
    unsigned char bitDepthTelemetry;
    unsigned char commandCounter;
    unsigned char reserved;
    ushort crc16;
};


struct Data38k{
    int status;
    QString data;
};

struct PacketDeviceData38k{
    Servise38k serv;
    Data38k data;
};

struct HeaderModules38k{
   unsigned char moduleAddress;
   unsigned char data_state;
   unsigned short totalSize;
   unsigned short totalDataSize;
   unsigned char totalParts;
   unsigned char currentPartNo;
   unsigned char lastCommandState;
   unsigned char commandCounter;
   unsigned char lastCommandCrc;
   unsigned char lastCommandCode;
   unsigned int requestTime;
};
struct PacketModulesData38k{
    int status;
    HeaderModules38k header;
    QString data;
};

class Parser38k{
    unsigned int numberOfChecks;
    unsigned int numberOfError;
    unsigned int probabilityOfError;
    Crc16 crc;
    ReedSolomonCoding cod;
    QList<TlmPack> *tlmDeviceData;
    QList<PacketDeviceData38k> *deviceData;
    QList<PacketModulesData38k> *modulesData;

    void findServiseFFFE();
    void findModulesData();
public:
    Parser38k(QList<BlockTlm> *tlmBlocks);
    QList<PacketModulesData38k> *getModulesData(){return modulesData;}
    unsigned int getProbabilityOfError(){return probabilityOfError;}
    ~Parser38k();
};

#endif // PARSER38K_H
