#ifndef PARSER38K_H
#define PARSER38K_H
#include "inc/parsers/parsertlm.h"
#include "inc/reedsolomoncoding.h"
#include "inc/crc16.h"
#include <QDebug>
#include <QThread>
#include "inc/filereader.h"

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
    QByteArray dataByte;
};

struct PacketDeviceData38k{
    Servise38k serv;
    Data38k data;
};
Q_DECLARE_METATYPE(PacketDeviceData38k);

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
    QByteArray dataBytes;
    QString data;
};
struct NumberType{
    unsigned char moduleAddress;
    uint type;
};
class Parser38kModules : public QThread{
    Q_OBJECT

    QList<NumberType> *listOfFoundModules;
    QList<PacketModulesData38k> *modulesData;
    uint wordPerChannel;
    uint currentWordPerChannel;
    uint currentChannel;
    uint isWave;
    bool enabled;

    void channelSHM(QString * data,unsigned char currentPartNo);
    void moduleDataParsing(PacketModulesData38k * moduleData);
public:
    Parser38kModules(QList<PacketModulesData38k> *modulesData);
    void run();

    ~Parser38kModules();
public slots:
    void stop();
    void del();

};
class Parser38k : public QThread{
    Q_OBJECT

    unsigned int numberOfChecks;
    unsigned int numberOfError;
    unsigned int probabilityOfError;
    Crc16 crc;
    ReedSolomonCoding cod;
    QByteArray byteArrayData;
    QList<TlmPack> *tlmDeviceData;
    QByteArray dataBytes;

    void findServiseFFFEBytes(TlmPack pack);
    void findModulesDataBytes(PacketDeviceData38k pack);
public:
    Parser38k(FileReader *file);
    void run();
    unsigned int getProbabilityOfError(){return probabilityOfError;}
    ~Parser38k();
public slots:
    void destroy();
signals:
    void getModData38k(PacketModulesData38k);

};

#endif // PARSER38K_H
