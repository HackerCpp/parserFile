#include "inc/parsers/parser38k.h"
#include <QTextCodec>

void paramFlashGKT(QString * data){
    bool ok;
    QString paramFlash = "\n\ttotal_length : %1\n\t\
telemetry_speed : %2\n\t\
telemetry_resolution : %3\n\t\
resistance_divisor : %4\n\t\
resistance_phase_one : %5\n\t\
resistance_phase_two : %6\n\t\
gk_dac_set_value : %7\n\t\
gk_dac_min_value : %8\n\t\
gk_dac_max_value : %9\n\t\
hygro_hi_prescaler : %10\n\t\
hygro_hi_timeout : %11\n\t\
hygro_lo_pulses : %12\n\t\
sti_max_temperature : %13\n\t\
sti_min_temperature : %14\n\t\
emds_disabled : %15\n\t\
gk_noisemeter_mode : %16\n\t\
sti_start_duty_value : %17\n\t\
extern_adc_temperature_config : %18\n\t\
extern_adc_std_config : %19\n\t\
extern_adc_pcorr_config : %20\n\t\
extern_adc_pbw_config : %21\n\t\
extern_adc_locator_config : %22\n\t\
extern_adc_accel_config : %23\n\t\
extern_adc_resist_config : %24\n\t\
add_command_dump : %25\n\t\
temperature_volatile : %26\n\t\
temperature_volatile : %27\n\t\
gk_dac_temperature_volatile : %28\n\t\
gk_dac_temperature_maximum : %29\n\t\
temperature_addition : %30\n\t\
reserve : %31\n\t\
extern_adc_locator_offset : %32\n\t\
CRC16 : %33\n\t";
            paramFlash = paramFlash.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg((*data).mid(4,2).toUInt(&ok,16)).arg((*data).mid(6,2).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16))
            .arg(((*data).mid(18,2) + (*data).mid(16,2)).toUInt(&ok,16))
            .arg(((*data).mid(22,2) + (*data).mid(20,2)).toUInt(&ok,16))
            .arg(((*data).mid(26,2) + (*data).mid(24,2)).toUInt(&ok,16))
            .arg(((*data).mid(30,2) + (*data).mid(28,2)).toUInt(&ok,16))
            .arg(((*data).mid(34,2) + (*data).mid(32,2)).toUInt(&ok,16))
            .arg(((*data).mid(38,2) + (*data).mid(36,2)).toUInt(&ok,16))
            .arg(((*data).mid(42,2) + (*data).mid(40,2)).toUInt(&ok,16))
            .arg(((*data).mid(50,2) + (*data).mid(48,2)+ (*data).mid(46,2)+ (*data).mid(44,2)).toUInt(&ok,16))
            .arg(((*data).mid(58,2) + (*data).mid(56,2)+ (*data).mid(54,2)+ (*data).mid(52,2)).toUInt(&ok,16))
            .arg((*data).mid(60,2).toUInt(&ok,16)).arg((*data).mid(62,2).toUInt(&ok,16))
            .arg(((*data).mid(66,2) + (*data).mid(64,2)).toUInt(&ok,16))
            .arg(((*data).mid(70,2) + (*data).mid(68,2)).toUInt(&ok,16))
            .arg(((*data).mid(74,2) + (*data).mid(72,2)).toUInt(&ok,16))
            .arg(((*data).mid(78,2) + (*data).mid(76,2)).toUInt(&ok,16))
            .arg(((*data).mid(82,2) + (*data).mid(80,2)).toUInt(&ok,16))
            .arg(((*data).mid(86,2) + (*data).mid(84,2)).toUInt(&ok,16))
            .arg(((*data).mid(90,2) + (*data).mid(88,2)).toUInt(&ok,16))
            .arg(((*data).mid(94,2) + (*data).mid(92,2)).toUInt(&ok,16))
            .arg((*data).mid(96,2).toUInt(&ok,16))
            .arg(((*data).mid(104,2) + (*data).mid(102,2)+ (*data).mid(100,2)+ (*data).mid(98,2)))
            .arg(((*data).mid(112,2) + (*data).mid(110,2)+ (*data).mid(108,2)+ (*data).mid(106,2)))
            .arg(((*data).mid(116,2) + (*data).mid(114,2)).toUInt(&ok,16))
            .arg(((*data).mid(120,2) + (*data).mid(118,2)).toUInt(&ok,16))
            .arg(((*data).mid(124,2) + (*data).mid(122,2)).toInt(&ok,16))
            .arg((*data).mid(126,8))
            .arg(((*data).mid(140,2) + (*data).mid(138,2)+ (*data).mid(136,2)+ (*data).mid(134,2)).toUInt(&ok,16))
            .arg((*data).mid(144,2) + (*data).mid(142,2));
    *data = paramFlash;
}

void paramFlashSHM(QString * data){
    bool ok;
    QString paramFlash = "\n\ttotal_length : %1\n\t\
sensors_number : %2\n\t\
channel_coefficients : %3\n\t\
head_to_sensor_length : %4\n\t\
startup_mode : %5\n\t\
hardware_swap_channels : %6\n\t\
hardware_invert_channels : %7\n\t\
acoustics_startup_channels : %8\n\t\
acoustics_startup_adc_time : %9\n\t\
acoustics_startup_period : %10\n\t\
acoustics_start_offset : %11\n\t\
acoustics_gain : %12\n\t\
acoustics_gain_off_words : %13\n\t\
acoustics_preconversion_pause : %14\n\t\
generator_wait_interval : %15\n\t\
noisemeter_startup_channels : %16\n\t\
noisemeter_startup_words : %17\n\t\
noisemeter_startup_freq : %18\n\t\
noisemeter_warm_cycles : %19\n\t\
noisemeter_window_fuction : %20\n\t\
noisemeter_smooth_number : %21\n\t\
noisemeter_gain : %22\n\t\
noisemeter_gain_off_words : %23\n\t\
noisemeter_preconversion_pause : %24\n\t\
part_max_size : %25\n\t\
movement_variance_limit : %26\n\t\
variance_settle_period : %27\n\t\
bus_survey : %28\n\t\
reserve : %29\n\t\
crc16 : %30\n\t";
            paramFlash = paramFlash.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)+ (*data).mid(10,2) + (*data).mid(8,2)) + " " +
                 ((*data).mid(22,2) + (*data).mid(20,2)+ (*data).mid(18,2) + (*data).mid(16,2)))
            .arg(QString::number(((*data).mid(26,2) + (*data).mid(24,2)).toUInt(&ok,16)) + " " +
                 QString::number(((*data).mid(30,2) + (*data).mid(28,2)).toUInt(&ok,16)))
            .arg(((*data).mid(34,2) + (*data).mid(32,2)).toUInt(&ok,16))
            .arg(((*data).mid(38,2) + (*data).mid(36,2)).toUInt(&ok,16))
            .arg(((*data).mid(42,2) + (*data).mid(40,2)).toUInt(&ok,16))
            .arg(((*data).mid(46,2) + (*data).mid(44,2)).toUInt(&ok,16))
            .arg(((*data).mid(50,2) + (*data).mid(48,2)).toUInt(&ok,16))
            .arg(((*data).mid(54,2) + (*data).mid(52,2)).toUInt(&ok,16))
            .arg(((*data).mid(58,2) + (*data).mid(56,2)).toUInt(&ok,16))
            .arg((*data).mid(60,2).toUInt(&ok,16))
            .arg(((*data).mid(64,2) + (*data).mid(62,2)).toUInt(&ok,16))
            .arg(((*data).mid(68,2) + (*data).mid(66,2)).toUInt(&ok,16))
            .arg(((*data).mid(72,2) + (*data).mid(70,2)).toUInt(&ok,16))
            .arg(((*data).mid(76,2) + (*data).mid(74,2)).toUInt(&ok,16))
            .arg(((*data).mid(80,2) + (*data).mid(78,2)).toUInt(&ok,16))
            .arg(((*data).mid(88,2) + (*data).mid(86,2)+ (*data).mid(84,2)+ (*data).mid(82,2)).toUInt(&ok,16))
            .arg(((*data).mid(92,2) + (*data).mid(90,2)).toUInt(&ok,16))
            .arg(((*data).mid(96,2) + (*data).mid(94,2)).toUInt(&ok,16))
            .arg(QString::number(((*data).mid(100,2) + (*data).mid(98,2)).toUInt(&ok,16)) + " " +
                 QString::number(((*data).mid(104,2) + (*data).mid(102,2)).toUInt(&ok,16)))
            .arg((*data).mid(106,2).toUInt(&ok,16))
            .arg(((*data).mid(110,2) + (*data).mid(108,2)).toUInt(&ok,16))
            .arg(((*data).mid(114,2) + (*data).mid(112,2)).toUInt(&ok,16))
            .arg(((*data).mid(118,2) + (*data).mid(116,2)).toUInt(&ok,16))
            .arg(((*data).mid(126,2) + (*data).mid(124,2)+ (*data).mid(122,2)+ (*data).mid(120,2)).toUInt(&ok,16))
            .arg(((*data).mid(130,2) + (*data).mid(128,2)).toUInt(&ok,16))
            .arg(((*data).mid(134,2) + (*data).mid(132,2)).toUInt(&ok,16))
            .arg((*data).mid(136,16))
            .arg((*data).mid(154,2) + (*data).mid(152,2));
    *data = paramFlash;
}

void paramFlashAG(QString * data){
    bool ok;
    QString paramFlash = "\n\ttotal_length : %1\n\t\
head_to_discharger_length : %2\n\t\
click_interval_low_freq : %3\n\t\
click_interval_hi_freq : %4\n\t\
click_channel : %5\n\t\
stop_pwm_interval : %6\n\t\
wait_interval : %7\n\t\
start_pwm_interval : %8\n\t\
reception_enable_interval : %9\n\t\
pwm_period : %10\n\t\
set_voltage : %11\n\t\
CRC16 : %12\n\t";
            paramFlash = paramFlash.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16))
            .arg((*data).mid(16,2).toUInt(&ok,16))
            .arg(((*data).mid(20,2) + (*data).mid(18,2)).toUInt(&ok,16))
            .arg(((*data).mid(24,2) + (*data).mid(22,2)).toUInt(&ok,16))
            .arg(((*data).mid(28,2) + (*data).mid(26,2)).toUInt(&ok,16))
            .arg(((*data).mid(32,2) + (*data).mid(30,2)).toUInt(&ok,16))
            .arg(((*data).mid(36,2) + (*data).mid(34,2)).toUInt(&ok,16))
            .arg(((*data).mid(40,2) + (*data).mid(38,2)).toUInt(&ok,16))
            .arg((*data).mid(44,2) + (*data).mid(42,2));
    *data = paramFlash;
}

void paramFlashP02(QString * data){
    bool ok;
    QString paramFlash = "\n\ttotal_length : %1\n\t\
channel_1_offset : %2\n\t\
channel_2_offset : %3\n\t\
invert_rate_signum : %4\n\t\
CRC16 : %5\n\t";
            paramFlash = paramFlash.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg((*data).mid(12,2).toUInt(&ok,16))
            .arg((*data).mid(16,2) + (*data).mid(14,2));
    *data = paramFlash;
}

void channelGKT(QString * data){
    bool ok;
    QString channel = "\n\ttemperature_internal : %1\n\t\
locator_amp : %2\n\t\
locator_amp_interval_max : %3\n\t\
locator_amp_interval_min : %4\n\t\
gk_time : %5\n\t\
gk_impulses : %6\n\t\
gk_uhv : %7\n\t\
hygrometer : %8\n\t\
power_supply : %9\n\t\
emds_supply : %10\n\t\
temperature_external : %11\n\t\
sti_1 : %12\n\t\
sti_2 : %13\n\t\
p_corr : %14\n\t\
p_bw : %15\n\t\
acceleration_x : %16\n\t\
acceleration_y : %17\n\t\
acceleration_z : %18\n\t\
locator_amp : %19\n\t\
resistance : %20\n\t\
sti_pwm : %21\n\t\
pressure : %22\n\t\
temperature : %23\n\t\
gk_dac : %24\n\t";
            channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16))
            .arg(((*data).mid(18,2) + (*data).mid(16,2)).toUInt(&ok,16))
            .arg(((*data).mid(22,2) + (*data).mid(20,2)).toUInt(&ok,16))
            .arg(((*data).mid(26,2) + (*data).mid(24,2)).toUInt(&ok,16))
            .arg(((*data).mid(30,2) + (*data).mid(28,2)).toUInt(&ok,16))
            .arg(((*data).mid(34,2) + (*data).mid(32,2)).toUInt(&ok,16))
            .arg(((*data).mid(38,2) + (*data).mid(36,2)).toUInt(&ok,16))
            .arg(((*data).mid(44,2) + (*data).mid(42,2)+ (*data).mid(40,2)).toUInt(&ok,16))
            .arg(((*data).mid(50,2) + (*data).mid(48,2)+ (*data).mid(46,2)).toUInt(&ok,16))
            .arg(((*data).mid(56,2) + (*data).mid(54,2)+ (*data).mid(52,2)).toUInt(&ok,16))
            .arg(((*data).mid(62,2) + (*data).mid(60,2)+ (*data).mid(58,2)).toUInt(&ok,16))
            .arg(((*data).mid(68,2) + (*data).mid(66,2)+ (*data).mid(64,2)).toUInt(&ok,16))
            .arg(((*data).mid(74,2) + (*data).mid(72,2)+ (*data).mid(70,2)).toUInt(&ok,16))
            .arg(((*data).mid(80,2) + (*data).mid(78,2)+ (*data).mid(76,2)).toUInt(&ok,16))
            .arg(((*data).mid(86,2) + (*data).mid(84,2)+ (*data).mid(82,2)).toUInt(&ok,16))
            .arg(((*data).mid(92,2) + (*data).mid(90,2)+ (*data).mid(88,2)).toUInt(&ok,16))
            .arg(((*data).mid(98,2) + (*data).mid(96,2)+ (*data).mid(94,2)).toUInt(&ok,16))
            .arg(((*data).mid(102,2) + (*data).mid(100,2)).toUInt(&ok,16))
            .arg(((*data).mid(110,2) + (*data).mid(108,2)+ (*data).mid(106,2)+ (*data).mid(104,2)).toUInt(&ok,16))
            .arg(((*data).mid(118,2) + (*data).mid(116,2)+ (*data).mid(114,2)+ (*data).mid(112,2)).toUInt(&ok,16))
            .arg(((*data).mid(122,2) + (*data).mid(120,2)).toUInt(&ok,16));
    *data = channel;
}

void channelSHM(QString * data,unsigned char currentPartNo){
    bool ok;
    int size = (data->size()/2);
    int pos = 0;
    static uint wordPerChannel;
    static uint currentWordPerChannel;
    static uint currentChannel;
    static uint isWave;
    QString channel;
    if(!currentPartNo){
        channel = "\n\tperiph_status : %1\n\t\
work_mode_MSB : %2\n\t\
work_mode_LSB : %3\n\t\
channels_map : %4\n\t\
words_per_channel : %5\n\t\
channel_frequency : %6\n\t\
pga_gain : %7\n\t\
temperature_internal : %8\n\t\
accel_z_mean : %9\n\t\
accel_z_variance : %10\n\t\
accel_z_flags : %11\n\t\
Data :\n\t";
        currentChannel = 0;
        currentWordPerChannel = 0;
        wordPerChannel = ((*data).mid(12,2) + (*data).mid(10,2)).toUInt(&ok,16);
        isWave = ("0"+(*data).mid(7,1)).toUInt(&ok,16);
        channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(("0"+(*data).mid(6,1)).toUInt(&ok,16)).arg(isWave)
            .arg(((*data).mid(8,2)).toUInt(&ok,16))
            .arg(wordPerChannel)
            .arg(((*data).mid(20,2) + (*data).mid(18,2)+ (*data).mid(16,2)+ (*data).mid(14,2)).toUInt(&ok,16))
            .arg((*data).mid(22,2).toUInt(&ok,16))
            .arg(((*data).mid(26,2) + (*data).mid(24,2)).toUInt(&ok,16))
            .arg(((*data).mid(30,2) + (*data).mid(28,2)).toUInt(&ok,16))
            .arg(((*data).mid(34,2) + (*data).mid(32,2)).toUInt(&ok,16))
            .arg(((*data).mid(38,2) + (*data).mid(36,2)).toUInt(&ok,16));
        size  = (data->size()/2)-20;
        pos = 42;
    }

    if(!isWave){
        for(int i = 0; i < size;i+=4){
            if(!currentWordPerChannel){
               channel += "\nChannel" + QString::number(currentChannel++) + "\n\n\t";
               currentWordPerChannel = wordPerChannel;
            }
            QByteArray string =  QByteArray::fromHex( ((*data).mid((i*2)+pos+6,2) + (*data).mid((i*2)+pos+4,2) + (*data).mid((i*2)+pos+2,2) + (*data).mid((i*2)+pos,2)).toLocal8Bit());
            channel += " \n\t" + QString::number(*reinterpret_cast<double*>( string.data() ));
            currentWordPerChannel--;
        }
    }
    else{
        for(int i = 0; i < size;i+=2){
            if(!currentWordPerChannel){
               channel += "\nChannel" + QString::number(currentChannel) + "\n\n\t";
               currentWordPerChannel = wordPerChannel;
            }
            channel += " \n\t" + QString::number(((*data).mid((i*2)+pos+6,2) + (*data).mid((i*2)+pos+4,2)).toUInt(&ok,16));
            currentWordPerChannel--;
        }
    }
    *data = channel;
}

void channelAG(QString * data){
    bool ok;
    QString channel = "\n\tperiph_status : %1\n\t\
work_mode : %2\n\t\
temperature_internal : %3\n\t\
discharge_voltage : %4\n\t";
            channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16));
    *data = channel;
}
void channelP(QString * data){
    bool ok;
    QString channel = "\n\tperiph_status : %1\n\t\
angle : %2\n\t\
rate : %3\n\t\
temperature_internal : %4\n\t";
            channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(QString::number(*reinterpret_cast<double*>( QByteArray::fromHex( ((*data).mid(14,2) + (*data).mid(12,2) + (*data).mid(10,2) + (*data).mid(8,2)).toLocal8Bit()).data() )))
            .arg(((*data).mid(18,2) + (*data).mid(16,2)).toUInt(&ok,16));
    *data = channel;
}

void channelP02(QString * data){
    bool ok;
    QString channel = "\n\trate : %1\n\t\
diameter : %2\n\t\
temperature_internal : %3\n\t";
            channel = channel.arg(QString::number(*reinterpret_cast<double*>( QByteArray::fromHex( ((*data).mid(6,2) + (*data).mid(4,2) + (*data).mid(2,2) + (*data).mid(0,2)).toLocal8Bit()).data() )))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16));
    *data = channel;
}

void channelP04(QString * data){
    bool ok;
    QString channel = "\n\trate : %1\n\t\
temperature_internal : %2\n\t";
            channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(4,2)).toUInt(&ok,16));
    *data = channel;
}
void channel2NNKt(QString * data){
    bool ok;
    QString channel = "\n\tperiph_status : %1\n\t\
count_time : %2\n\t\
near_count : %3\n\t\
far_count : %4\n\t\
gk_uhv : %5\n\t\
gk_dac : %6\n\t\
temperature_internal : %7\n\t\
comp_edac1_value : %8\n\t\
comp_edac2_value : %9\n\t";
            channel = channel.arg(((*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(4,2) + (*data).mid(2,2)).toUInt(&ok,16))
            .arg(((*data).mid(12,2) + (*data).mid(10,2)+ (*data).mid(8,2)+ (*data).mid(6,2)).toUInt(&ok,16))
            .arg(((*data).mid(20,2) + (*data).mid(18,2)+ (*data).mid(16,2)+ (*data).mid(14,2)).toUInt(&ok,16))
            .arg(((*data).mid(24,2) + (*data).mid(22,2)).toUInt(&ok,16))
            .arg(((*data).mid(28,2) + (*data).mid(26,2)).toUInt(&ok,16))
            .arg(((*data).mid(32,2) + (*data).mid(30,2)).toUInt(&ok,16))
            .arg(((*data).mid(36,2) + (*data).mid(34,2)).toUInt(&ok,16))
            .arg(((*data).mid(40,2) + (*data).mid(38,2)).toUInt(&ok,16));
    *data = channel;
}
void channelGGP(QString * data){
    bool ok;
    QString channel = "\n\tperiph_status : %1\n\t\
count_time : %2\n\t\
count : %3\n\t\
gk_uhv : %4\n\t\
gk_dac : %5\n\t\
temperature_internal : %6\n\t\
comp_edac_value : %7\n\t";
            channel = channel.arg(((*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(4,2) + (*data).mid(2,2)).toUInt(&ok,16))
            .arg(((*data).mid(12,2) + (*data).mid(10,2)+ (*data).mid(8,2)+ (*data).mid(6,2)).toUInt(&ok,16))
            .arg(((*data).mid(16,2) + (*data).mid(14,2)).toUInt(&ok,16))
            .arg(((*data).mid(20,2) + (*data).mid(18,2)).toUInt(&ok,16))
            .arg(((*data).mid(24,2) + (*data).mid(22,2)).toUInt(&ok,16))
            .arg(((*data).mid(28,2) + (*data).mid(26,2)).toUInt(&ok,16));
    *data = channel;
}
void channelGVK(QString * data){
    bool ok;
    QString channel = "\n\ttemperature_internal : %1\n\t\
locator_amp : %2\n\t\
locator_amp_interval_max : %3\n\t\
locator_amp_interval_min : %4\n\t\
gk_time : %5\n\t\
gk_impulses : %6\n\t\
gk_uhv : %7\n\t\
power_supply : %8\n\t\
temperature_external : %9\n\t\
temperature_external_2 : %10\n\t\
temperature_external_3 : %11\n\t\
p_corr : %12\n\t\
p_bw : %13\n\t\
acceleration_x : %14\n\t\
acceleration_y : %15\n\t\
acceleration_z : %16\n\t\
locator_amp : %17\n\t\
temperature_external_4 : %18\n\t\
gk_dac : %19\n\t";
            channel = channel.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16))
            .arg(((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16))
            .arg(((*data).mid(10,2) + (*data).mid(8,2)).toUInt(&ok,16))
            .arg(((*data).mid(14,2) + (*data).mid(12,2)).toUInt(&ok,16))
            .arg(((*data).mid(18,2) + (*data).mid(16,2)).toUInt(&ok,16))
            .arg(((*data).mid(22,2) + (*data).mid(20,2)).toUInt(&ok,16))
            .arg(((*data).mid(26,2) + (*data).mid(24,2)).toUInt(&ok,16))
            .arg(((*data).mid(30,2) + (*data).mid(28,2)).toUInt(&ok,16))
            .arg(((*data).mid(36,2) + (*data).mid(34,2)+ (*data).mid(32,2)).toUInt(&ok,16))
            .arg(((*data).mid(42,2) + (*data).mid(40,2)+ (*data).mid(38,2)).toUInt(&ok,16))
            .arg(((*data).mid(48,2) + (*data).mid(46,2)+ (*data).mid(44,2)).toUInt(&ok,16))
            .arg(((*data).mid(54,2) + (*data).mid(52,2)+ (*data).mid(50,2)).toUInt(&ok,16))
            .arg(((*data).mid(60,2) + (*data).mid(58,2)+ (*data).mid(56,2)).toUInt(&ok,16))
            .arg(((*data).mid(66,2) + (*data).mid(64,2)+ (*data).mid(62,2)).toUInt(&ok,16))
            .arg(((*data).mid(72,2) + (*data).mid(70,2)+ (*data).mid(68,2)).toUInt(&ok,16))
            .arg(((*data).mid(78,2) + (*data).mid(76,2)+ (*data).mid(74,2)).toUInt(&ok,16))
            .arg(((*data).mid(84,2) + (*data).mid(82,2)+ (*data).mid(80,2)).toUInt(&ok,16))
            .arg(((*data).mid(90,2) + (*data).mid(88,2)+ (*data).mid(86,2)).toUInt(&ok,16))
            .arg(((*data).mid(94,2) + (*data).mid(92,2)).toUInt(&ok,16));
    *data = channel;
}
void Parser38kModules::moduleDataParsing(PacketModulesData38k * moduleData){
    bool ok;
    QString * data = &moduleData->data;
    if(moduleData->header.data_state & 0x02){
        QString hardFlash = "HardFlash:\n\t\
total_length : %1\n\t\
device_type : %2\n\t\
device_number : %3\n\t\
production_day : %4\n\t\
production_month : %5\n\t\
production_year : %6\n\t\
device_name : %7\n\t\
device_code : %8\n\t\
device_decimal : %9\n\t\
flash_version : %10\n\t\
firmware_version : %11\n\t\
reserved : %12\n\t\
device_tag : %13\n\t\
device_length : %14\n\t\
device_tech_header_size : %15\n\t\
device_data_size : %16\n\t\
data_parts_max : %17";

        bool moduleAdded = false;
        uint deviceType = ((*data).mid(6,2) + (*data).mid(4,2)).toUInt(&ok,16);
        if(listOfFoundModules->size() != 0)
            for(auto value = listOfFoundModules->begin();value < listOfFoundModules->end();value++)
                if(value->moduleAddress == moduleData->header.moduleAddress){
                    moduleAdded = true;
                    break;
                }
        if(!moduleAdded){
            NumberType module = {moduleData->header.moduleAddress,deviceType};
            listOfFoundModules->push_back(module);
        }
        hardFlash = hardFlash.arg(((*data).mid(2,2) + (*data).mid(0,2)).toUInt(&ok,16)).arg(deviceType)
        .arg(((*data).mid(30,2) + (*data).mid(28,2)+ (*data).mid(26,2)+ (*data).mid(24,2)+
        (*data).mid(22,2) + (*data).mid(20,2)+ (*data).mid(18,2)+ (*data).mid(16,2)+
        (*data).mid(14,2) + (*data).mid(12,2)+ (*data).mid(10,2)+ (*data).mid(8,2)))
        .arg((*data).mid(32,2).toUInt(&ok,16)).arg((*data).mid(34,2).toUInt(&ok,16))
        .arg(((*data).mid(38,2) + (*data).mid(36,2)).toUInt(&ok,16))
        .arg(QTextCodec::codecForMib(106)->toUnicode(QByteArray::fromHex(((*data).mid(40,32)).toLocal8Bit())))
        .arg(((*data).mid(82,2) + (*data).mid(80,2)+ (*data).mid(78,2)+ (*data).mid(76,2)+
              (*data).mid(74,2) + (*data).mid(72,2)))
        .arg(((*data).mid(94,2) + (*data).mid(92,2)+ (*data).mid(90,2)+ (*data).mid(88,2)+
              (*data).mid(86,2) + (*data).mid(84,2)))
        .arg((*data).mid(96,4).toUInt(&ok,16))
        .arg((*data).mid(100,4).toUInt(&ok,16))
        .arg((*data).mid(104,8).toUInt(&ok,16))
        .arg(QTextCodec::codecForMib(106)->toUnicode(QByteArray::fromHex(((*data).mid(112,40)).toLocal8Bit())))
        .arg(((*data).mid(154,2) + (*data).mid(152,2)).toUInt(&ok,16))
        .arg(((*data).mid(158,2) + (*data).mid(156,2)).toUInt(&ok,16))
        .arg(((*data).mid(166,2) + (*data).mid(164,2) + (*data).mid(162,2) + (*data).mid(160,2)).toUInt(&ok,16))
        .arg(((*data).mid(168,2)).toUInt(&ok,16));
        int length = ((*data).mid(2,2) + (*data).mid(0,2)).toInt(&ok,16);
        int numberOfChannels = (length-86)/8;
        for(int i = 0; i <  numberOfChannels;i++){
            hardFlash+= "\n\tchannel " + QString::number(i) + ":";
            hardFlash+="\n\tchannel_mnemonics : " + (*data).mid((i*16)+176,2) + (*data).mid((i*16)+174,2)+ (*data).mid((i*16)+172,2)+ (*data).mid((i*16)+170,2);
            hardFlash+="\n\tchannel_write_point : " + QString::number(((*data).mid((i*16)+180,2) + (*data).mid((i*16)+178,2)).toUInt(&ok,16));
            hardFlash+="\n\tchannel_flags : " + (*data).mid((i*16)+184,2) + (*data).mid((i*16)+182,2);
        }
        hardFlash+= "\n\tCRC16 : " + (*data).mid(172 +(numberOfChannels * 16) ,2) + (*data).mid(170 +(numberOfChannels * 16),2);
        length = ((*data).mid(176 +(numberOfChannels * 16) ,2) + (*data).mid(174 +(numberOfChannels * 16),2)).toInt(&ok,16);
        QString paramFlash = "\nParamFlash:";
        QString paramFlashString = (*data).mid(174 +(numberOfChannels * 16),length*2);
        if(deviceType == 0)
           paramFlashGKT(&paramFlashString);
        else if(deviceType == 1)
           paramFlashSHM(&paramFlashString);
        else if(deviceType == 2)
           paramFlashAG(&paramFlashString);
        else if(deviceType == 7)
           paramFlashP02(&paramFlashString);
        paramFlash += paramFlashString;
        QString calibFlash = "\nCalibFlash:\n\t" + (*data).mid(178 +(numberOfChannels * 16) + (length-2)*2);
        *data = hardFlash + paramFlash + calibFlash;
    }
    else if(!(moduleData->header.data_state & 0x01)){
        uint type = 124;
        if(listOfFoundModules->size() != 0)
            for(auto value = listOfFoundModules->begin();value < listOfFoundModules->end();value++)
                if(value->moduleAddress == moduleData->header.moduleAddress){
                    type = value->type;
                    break;
                }
        if(type == 0)
           channelGKT(data);
        else if(type == 1)
           channelSHM(data,moduleData->header.currentPartNo);
        else if(type == 2)
           channelAG(data);
        else if(type == 7)
           channelP02(data);
    }
}
Parser38kModules::Parser38kModules(QList<PacketModulesData38k> *modulesData){
    this->modulesData = modulesData;
    this->listOfFoundModules = new QList<NumberType>;
}
void Parser38kModules::run(){
    //int quantity = 0;
    //QThread::sleep(20);
    //while(modulesData->size() == 0){};
    for(auto value = modulesData->begin();value < modulesData->end(); value++){
        moduleDataParsing(&*value);
        //quantity++;
        //while(quantity == modulesData->size()){}
    }
}

Parser38kModules::~Parser38kModules(){

}



void Parser38k::findServiseFFFE(TlmPack pack){
    bool ok;
    unsigned char array[255];
        QString data = pack.dataPucket.data.mid(4);
        QByteArray byteArray = QByteArray::fromHex(data.toLocal8Bit());
        QString bl255 = "";
        PacketDeviceData38k packetDeviceData;
        packetDeviceData.data.status = 0;
        for(int position = 0; position < data.length()-2;position+=510 ){
            bl255 = data.mid(position,510);
            byteArray = QByteArray::fromHex(bl255.toLocal8Bit());
            memset(array,0,255);
            memcpy(array,byteArray.toStdString().c_str(),byteArray.size());
            int decod = cod.decode_rs_nasa(array);
            this->numberOfChecks++;
            this->numberOfError += decod?1:0;
            packetDeviceData.data.status |= decod;
            packetDeviceData.data.data += bl255.mid(66);
        }
        QString serv = packetDeviceData.data.data.mid(0,24);
        byteArray = QByteArray::fromHex(serv.toLocal8Bit());
        memset(array,0,255);
        memcpy(array,byteArray.toStdString().c_str(),byteArray.size());
        this->numberOfChecks++;
        int crcF = crc.crcFast(array,12);
        if(crcF)
            this->numberOfError++;
        if((packetDeviceData.data.status == 2 && crcF) || serv.size() == 0)
            return;

        packetDeviceData.data.data = packetDeviceData.data.data.mid(24);
        data = QByteArray::fromRawData(reinterpret_cast<const char *>(array),30).toHex();
        packetDeviceData.serv.systemTime = (serv.mid(6,2) + serv.mid(4,2)+serv.mid(2,2) + serv.mid(0,2)).toUInt(&ok,16);
        packetDeviceData.serv.transmissionCounter = static_cast<unsigned short>((serv.mid(10,2) + serv.mid(8,2)).toUInt(&ok,16));
        packetDeviceData.serv.totalModules = static_cast<unsigned char>(serv.mid(12,2).toUInt(&ok,16));
        packetDeviceData.serv.speedTelemetry = static_cast<unsigned char>(("0"+serv.mid(14,1)).toUInt(&ok,16));
        packetDeviceData.serv.bitDepthTelemetry = static_cast<unsigned char>(("0"+serv.mid(15,1)).toUInt(&ok,16));
        packetDeviceData.serv.commandCounter = static_cast<unsigned char>(serv.mid(16,2).toUInt(&ok,16));
        packetDeviceData.serv.reserved = static_cast<unsigned char>(serv.mid(18,2).toUInt(&ok,16));
        packetDeviceData.serv.crc16 = static_cast<unsigned short>((data.mid(22,2) + data.mid(20,2)).toUInt(&ok,16));
        findModulesData(packetDeviceData);
}

void Parser38k::findModulesData(PacketDeviceData38k pack){
    static bool ok;
    static QString data ="";
    QString moduleDataString;
    int position = 0;
        data += pack.data.data.mid(0,pack.data.data.size());
        int size = data.size();
        while(position < size){
            PacketModulesData38k moduleData;
            moduleData.header.moduleAddress = static_cast<unsigned char>(data.mid(position,2).toUInt(&ok,16));
            moduleData.header.data_state = static_cast<unsigned char>(data.mid(position + 2,2).toUInt(&ok,16));
            moduleData.header.totalSize = static_cast<unsigned short>((data.mid(position + 6,2) + data.mid(position +4,2)).toUInt(&ok,16));
            if(moduleData.header.totalSize * 2 > size - position || moduleData.header.totalSize < 12)
                break;
            moduleDataString = data.mid(position,moduleData.header.totalSize*2);
            unsigned char array[moduleData.header.totalSize];
            memset(array,0,moduleData.header.totalSize);
            QByteArray byteArray = QByteArray::fromHex(moduleDataString.toLocal8Bit());
            memcpy(array,byteArray.toStdString().c_str(),moduleData.header.totalSize);
            moduleData.status =  crc.crcFast(array,moduleData.header.totalSize)?0x80:0;
            int posLastComSt = 0;
            if(moduleData.header.data_state & 0x80){
                moduleData.header.totalDataSize = moduleData.header.totalSize - 14;
                moduleData.header.totalParts = 1;
                moduleData.header.currentPartNo = 0;
            }
            else{
                moduleData.header.totalDataSize = static_cast<unsigned short>((data.mid(position + 10,2) + data.mid(position +8,2)).toUInt(&ok,16));
                moduleData.header.totalParts = static_cast<unsigned char>(data.mid(position + 12,2).toUInt(&ok,16));
                moduleData.header.currentPartNo = static_cast<unsigned char>(data.mid(position + 14,2).toUInt(&ok,16));
                posLastComSt = 8;
            }
            int pos = position + posLastComSt;
            moduleData.header.lastCommandState = static_cast<unsigned char>(data.mid(pos + 8,2).toUInt(&ok,16));
            moduleData.header.commandCounter = static_cast<unsigned char>(data.mid(pos + 10,2).toUInt(&ok,16));
            moduleData.header.lastCommandCrc = static_cast<unsigned char>(data.mid(pos + 12,2).toUInt(&ok,16));
            moduleData.header.lastCommandCode = static_cast<unsigned char>(data.mid(pos + 14,2).toUInt(&ok,16));
            moduleData.header.requestTime = (data.mid(pos +22,2) + data.mid(pos +20,2)+data.mid(pos +18,2) + data.mid(pos +16,2)).toUInt(&ok,16);
            moduleData.data = moduleDataString.mid(24,moduleData.header.totalSize*2 - 28);
            //moduleDataParsing(&moduleData);
            emit  getModData38k(moduleData);
            position += moduleDataString.size();
        }
        data.remove(0,position);
        position = 0;
        if(data == "00")
            data ="";
}

Parser38k::Parser38k(FileReader *file){
    this->tlmDeviceData = new QList<TlmPack>;
    this->listOfFoundModules = new QList<NumberType>;
    this->hexString = file->getHexString();
    delete file;
    file = nullptr;
    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}

void Parser38k::run(){
    numberOfChecks = 0;
    numberOfError = 0;
    ParserTLM *parserTlm = new ParserTLM(this->hexString);
    QList<BlockTlm> *tlmBlocks = parserTlm->getBlocks();
    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPucket.dev_type == "ADSP" && pack->dataPucket.inf_type == "GETDATA")
                findServiseFFFE(*pack);
    delete parserTlm;
    parserTlm = nullptr;
    double sr;
    if(numberOfError != 0 & numberOfChecks != 0)
         sr = numberOfError/(numberOfChecks/100);
    else
        sr = 100;

    this->probabilityOfError = sr;
}

void Parser38k::destroy(){
   this->~Parser38k();
}

Parser38k::~Parser38k(){
    delete this->tlmDeviceData;
    this->quit();
}
