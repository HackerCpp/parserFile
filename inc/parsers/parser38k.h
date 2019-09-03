#ifndef PARSER38K_H
#define PARSER38K_H
#include "inc/parsers/parsertlm.h"
#include "inc/reedsolomoncoding.h"
#include "inc/crc16.h"
#include <QDebug>
#include <QThread>
#include "inc/filereader.h"


enum {GKT,SHM,AG,MP,AMDS,GKTSHM,P04,P02,GVK,NNKt,GGP};
#pragma pack(push,1)
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
struct ModuleData{
    ushort type;
};
struct DataGKT : public ModuleData{
    ushort temperature_internal;
    short locator_amp16;
    short locator_amp_interval_max;
    short locator_amp_interval_min;
    ushort gk_time;
    ushort gk_impulses;
    ushort gk_uhv;
    ushort hygrometer;
    ushort power_supply;
    ushort emds_supply;
    uint temperature_external;
    uint sti_1;
    uint sti_2;
    uint p_corr;
    uint p_bw;
    uint acceleration_x;
    uint acceleration_y;
    uint acceleration_z;
    uint locator_amp24;
    uint resistance;
    ushort sti_pwm;
    uint pressure;
    uint temperature;
    ushort gk_dac;
};
struct DataSHM0 : public ModuleData{
    ushort periph_status;
    ushort work_mode;
    uchar channels_map;
    ushort words_per_channel;
    uint channel_frequency;
    uchar pga_gain;
    ushort temperature_internal;
    ushort accel_z_mean;
    ushort accel_z_variance;
    ushort accel_z_flags;
    QVector<ushort> * Wave_1int;
    QVector<float> * Wave_1float;
};
struct DataSHM1 : public ModuleData{
    QVector<ushort> * Wave_1int;
    QVector<float> * Wave_1float;
};
struct DataAG : public ModuleData{
    ushort periph_status;
    ushort work_mode;
    ushort temperature_internal;
    ushort discharge_voltage;
};
struct DataP : public ModuleData{
    ushort periph_status;
    ushort angle;
    float rate;
    ushort temperature_internal;
};
struct DataP02 : public ModuleData{
    float rate;
    ushort diameter;
    ushort temperature_internal;
};
struct DataP04 : public ModuleData{
    ushort rate;
    uchar temperature_internal;
};
struct Data2NNKT : public ModuleData{
    uchar periph_status;
    ushort count_time;
    uint near_count;
    uint far_count;
    ushort gk_uhv;
    ushort gk_dac;
    ushort temperature_internal;
    ushort comp_edac1_value;
    ushort comp_edac2_value;
};
struct DataGGP : public ModuleData{
    uchar periph_status;
    ushort count_time;
    uint count;
    ushort gk_uhv;
    ushort gk_dac;
    ushort temperature_internal;
    ushort comp_edac_value;
};
struct DataGVK : public ModuleData{
    ushort temperature_internal;
    short locator_amp16;
    short locator_amp_interval_max;
    short locator_amp_interval_min;
    ushort gk_time;
    ushort gk_impulses;
    ushort gk_uhv;
    ushort power_supply;
    uint temperature_external;
    uint temperature_external2;
    uint temperature_external3;
    uint p_corr;
    uint p_bw;
    uint acceleration_x;
    uint acceleration_y;
    uint acceleration_z;
    uint locator_amp24;
    uint temperature_external4;
    ushort gk_dac;
};
struct DataGKTVirtual : public ModuleData{
    ushort work_mode;
    float lf_rms;
    float mf_rms;
    float hf_rms;
    ushort channelWords;
    uint channel_frequency;
    ushort * wave;
};
struct PacketModulesData38k{
    int status;
    HeaderModules38k header;
    QByteArray dataBytes;
    QString data;
    ModuleData *dataStruct;
};
struct NumberType{
    unsigned char moduleAddress;
    uint type;
};
#pragma pack(pop)
class Parser38kModules : public QThread{
    Q_OBJECT

    QList<NumberType> *listOfFoundModules;
    QList<PacketModulesData38k> *modulesData;
    uint wordPerChannel;
    uint currentWordPerChannel;
    uint currentChannel;
    uint isWave;
    bool enabled;

    void channelSHM(PacketModulesData38k * moduleData);
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
