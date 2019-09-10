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
struct ChannelInformation{
    QString channel_mnemonics;
    short channel_write_point;
    ushort channel_flags;
};
struct ModuleData{
    ushort type;
};
struct HardFlash{
   ushort total_length;
   ushort device_tipe;
   QString device_number;
   uchar production_day;
   uchar production_month;
   ushort production_year;
   QString device_name;
   QString device_code;
   QString device_decimal;
   QString flash_version;
   QString firmware_version;
   uint reserved;
   QString device_tag;
   ushort device_length;
   ushort device_tech_header_size;
   uint device_data_size;
   uchar data_parts_max;
   QList<ChannelInformation> channel;
   ushort crc16;
};
struct  ParamFlash{
    ushort total_length;
};
struct ParamFlashGKT : public ParamFlash{  
    uchar telemetry_speed;
    uchar telemetry_resolution;
    ushort resistance_divisor;
    ushort resistance_phase_one;
    ushort resistance_phase_two;
    ushort gk_dac_set_value;
    short gk_dac_min_value;
    short gk_dac_max_value;
    ushort hygro_hi_prescaler;
    ushort hygro_hi_timeout;
    ushort hygro_lo_pulses;
    uint sti_max_temperature;
    uint sti_min_temperature;
    uchar emds_disable;
    uchar gk_noisemeter_mode;
    ushort sti_start_duty_value;
    ushort extern_adc_temperature_config;
    ushort extern_adc_std_config;
    ushort extern_adc_pcorr_config;
    ushort extern_adc_pbw_config;
    ushort extern_adc_locator_config;
    ushort extern_adc_accel_config;
    ushort extern_adc_resist_config;
    uchar add_command_dump;
    float temperature_volatile;
    float temperature_maximum;
    ushort gk_dac_temperature_volatile;
    ushort gk_dac_temperature_maximum;
    short temperature_addition;
    int reserve;
    uint extern_adc_locator_offset;
    ushort crc16;
};
struct ParamFlashSHM : public ParamFlash{
    ushort sensor_number;
    float channel_coefficients[2];
    ushort head_to_sensor_length[2];
    ushort startup_mode;
    ushort hardware_swap_channels;
    ushort hardware_invert_channels;
    ushort acoustics_startup_channels;
    ushort acoustics_startup_adc_time;
    ushort acoustics_startup_period;
    ushort acoustics_start_offset;
    uchar acoustics_gain;
    ushort acoustics_gain_off_words;
    ushort acoustics_preconversion_pause;
    ushort generator_wait_interval;
    ushort noisemetr_startup_channels;
    ushort noisemetr_startup_words;
    uint noisemeter_startup_freq;
    ushort noisemeter_warm_cycles;
    ushort noisemeter_window_function;
    ushort noisemeter_smooth_number[2];
    uchar noisemeter_gain;
    ushort noisemeter_gain_off_words;
    ushort noisemeter_preconversion_pause;
    ushort part_max_size;
    uint movement_variance_limit;
    ushort variance_settle_period;
    ushort bus_survey;
    uchar reserve[8];
    ushort crc16;
};
struct ParamFlashAG : public ParamFlash{
    ushort head_to_discharger_length;
    ushort click_interval_low_freq;
    ushort click_interval_hi_freq;
    uchar click_channel;
    ushort stop_pwm_interval;
    ushort wait_interval;
    ushort start_pwm_interval;
    ushort reception_enable_interval;
    ushort pwm_period;
    ushort set_voltage;
    ushort crc16;
};
struct ParamFlashP : public ParamFlash{
   ushort crc16;
};
struct  ParamFlashP02P04 : public ParamFlash{
    ushort channel_1_offset;
    ushort channel_2_offset;
    bool invert_rate_signum;
    ushort crc16;
};
struct ParamFlashGVK : public ParamFlash{
    uchar telemetry_speed;
    uchar telemetry_resolution;
    ushort gk_dac_set_value;
    short gk_dac_min_value;
    short gk_dac_max_value;
    ushort extern_adc_temperature_config;
    ushort extern_adc_temperature_2_config;
    ushort extern_adc_pcorr_config;
    ushort extern_adc_pbw_config;
    ushort extern_adc_locator_config;
    ushort extern_adc_accel_config;
    ushort extern_adc_temperature_4_config;
    uchar reserve;
    float temperature_volatile;
    float temperature_maximum;
    ushort reserve2;
    int reserve3;
    uint extern_adc_locator_offset;
    ushort crc16;

};
struct ParamFlashNNKt : public ParamFlash{
  ushort near_counter_threshold;
  ushort far_counter_threshold;
  uchar swap_shannels;
  short dac_set_value;
  short dac_min_value;
  short dac_max_value;
  float temperature_volatile;
  float temperature_maximum;
  ushort dac_temperature_volatile;
  ushort dac_temperature_maximum;
  short temperature_addition;
  uchar reserve[8];
  ushort crc16;
};
struct ParamFlashGGP : public ParamFlash{
    short counter_threshold;
    uchar swap_channels;
    short dac_set_value;
    short dac_min_value;
    short dac_max_value;
    float temperature_volatile;
    float temperature_maximum;
    ushort dac_temperature_volatile;
    ushort dac_temperature_maximum;
    short temperature_addition;
    uchar reserve[8];
    ushort crc16;
};
struct Flash : public ModuleData{
    HardFlash hardFlash;
    ParamFlash *paramFlash;
    QByteArray calibFlash;
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
struct DataSHM1 : public ModuleData{
    QVector<short> * Wave_1int;
    QVector<float> * Wave_1float;
};
struct DataSHM0 : public DataSHM1{
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
    uint temperature_external : 24;
    uint temperature_external2 : 24;
    uint temperature_external3 : 24;
    uint p_corr : 24;
    uint p_bw : 24;
    uint acceleration_x : 24;
    uint acceleration_y : 24;
    uint acceleration_z : 24;
    uint locator_amp24 : 24;
    uint temperature_external4 : 24;
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
