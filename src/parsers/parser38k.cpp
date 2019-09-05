#include "inc/parsers/parser38k.h"
#include <QTextCodec>
#include <QTime>

void paramFlashGKT(QString & data,QByteArray &ba){
    data += "<tr><td>ttotal_length </td><td> %1</td></tr>\
<tr><td>telemetry_speed </td><td> %2</td></tr>\
<tr><td>telemetry_resolution </td><td> %3</td></tr>\
<tr><td>resistance_divisor </td><td> %4</td></tr>\
<tr><td>resistance_phase_one </td><td> %5</td></tr>\
<tr><td>resistance_phase_two </td><td> %6</td></tr>\
<tr><td>gk_dac_set_value </td><td> %7</td></tr>\
<tr><td>gk_dac_min_value </td><td> %8</td></tr>\
<tr><td>gk_dac_max_value </td><td> %9</td></tr>\
<tr><td>hygro_hi_prescaler </td><td> %10</td></tr>\
<tr><td>hygro_hi_timeout </td><td> %11</td></tr>\
<tr><td>hygro_lo_pulses </td><td> %12</td></tr>\
<tr><td>sti_max_temperature </td><td> %13</td></tr>\
<tr><td>sti_min_temperature </td><td> %14</td></tr>\
<tr><td>emds_disabled </td><td> %15</td></tr>\
<tr><td>gk_noisemeter_mode </td><td> %16</td></tr>\
<tr><td>sti_start_duty_value </td><td> %17</td></tr>\
<tr><td>extern_adc_temperature_config </td><td> %18</td></tr>\
<tr><td>extern_adc_std_config </td><td> %19</td></tr>\
<tr><td>extern_adc_pcorr_config </td><td> %20</td></tr>\
<tr><td>extern_adc_pbw_config </td><td> %21</td></tr>\
<tr><td>extern_adc_locator_config </td><td> %22</td></tr>\
<tr><td>extern_adc_accel_config </td><td> %23</td></tr>\
<tr><td>extern_adc_resist_config </td><td> %24</td></tr>\
<tr><td>add_command_dump </td><td> %25</td></tr>\
<tr><td>temperature_volatile </td><td> %26</td></tr>\
<tr><td>temperature_volatile </td><td> %27</td></tr>\
<tr><td>gk_dac_temperature_volatile </td><td> %28</td></tr>\
<tr><td>gk_dac_temperature_maximum </td><td> %29</td></tr>\
<tr><td>temperature_addition </td><td> %30</td></tr>\
<tr><td>reserve </td><td> %31</td></tr>\
<tr><td>extern_adc_locator_offset </td><td> %32</td></tr>\
<tr><td>CRC16 </td><td> %33</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<uchar*>(ba.data()+2)).arg(*reinterpret_cast<uchar*>(ba.data()+3))
            .arg(*reinterpret_cast<ushort*>(ba.data()+4))
            .arg(*reinterpret_cast<ushort*>(ba.data()+6))
            .arg(*reinterpret_cast<ushort*>(ba.data()+8))
            .arg(*reinterpret_cast<ushort*>(ba.data()+10))
            .arg(*reinterpret_cast<ushort*>(ba.data()+12))
            .arg(*reinterpret_cast<ushort*>(ba.data()+14))
            .arg(*reinterpret_cast<ushort*>(ba.data()+16))
            .arg(*reinterpret_cast<ushort*>(ba.data()+18))
            .arg(*reinterpret_cast<ushort*>(ba.data()+20))
            .arg(*reinterpret_cast<uint*>(ba.data()+22))
            .arg(*reinterpret_cast<uint*>(ba.data()+26))
            .arg(*reinterpret_cast<uchar*>(ba.data()+30)).arg(*reinterpret_cast<uchar*>(ba.data()+31))
            .arg(*reinterpret_cast<ushort*>(ba.data()+32))
            .arg(*reinterpret_cast<ushort*>(ba.data()+34))
            .arg(*reinterpret_cast<ushort*>(ba.data()+36))
            .arg(*reinterpret_cast<ushort*>(ba.data()+38))
            .arg(*reinterpret_cast<ushort*>(ba.data()+40))
            .arg(*reinterpret_cast<ushort*>(ba.data()+42))
            .arg(*reinterpret_cast<ushort*>(ba.data()+44))
            .arg(*reinterpret_cast<ushort*>(ba.data()+46))
            .arg(*reinterpret_cast<uchar*>(ba.data()+48))
            .arg(*reinterpret_cast<float*>(ba.data()+49))
            .arg(*reinterpret_cast<float*>(ba.data()+53))
            .arg(*reinterpret_cast<ushort*>(ba.data()+57))
            .arg(*reinterpret_cast<ushort*>(ba.data()+59))
            .arg(*reinterpret_cast<ushort*>(ba.data()+61))
            .arg(*reinterpret_cast<uint*>(ba.data()+63))
            .arg(*reinterpret_cast<uint*>(ba.data()+67))
            .arg(*reinterpret_cast<uchar*>(ba.data()+71));
}

void paramFlashSHM(QString & data,QByteArray &ba){
    data += "<tr><td>total_length </td><td> %1</td></tr>\
<tr><td>sensors_number </td><td> %2</td></tr>\
<tr><td>channel_coefficients </td><td> %3</td></tr>\
<tr><td>head_to_sensor_length </td><td> %4</td></tr>\
<tr><td>startup_mode : %5</td></tr>\
<tr><td>hardware_swap_channels </td><td> %6</td></tr>\
<tr><td>hardware_invert_channels </td><td> %7</td></tr>\
<tr><td>acoustics_startup_channels </td><td> %8</td></tr>\
<tr><td>acoustics_startup_adc_time </td><td> %9</td></tr>\
<tr><td>acoustics_startup_period </td><td> %10</td></tr>\
<tr><td>acoustics_start_offset </td><td> %11</td></tr>\
<tr><td>acoustics_gain </td><td> %12</td></tr>\
<tr><td>acoustics_gain_off_words </td><td> %13</td></tr>\
<tr><td>acoustics_preconversion_pause </td><td> %14</td></tr>\
<tr><td>generator_wait_interval </td><td> %15</td></tr>\
<tr><td>noisemeter_startup_channels </td><td> %16</td></tr>\
<tr><td>noisemeter_startup_words </td><td> %17</td></tr>\
<tr><td>noisemeter_startup_freq </td><td> %18</td></tr>\
<tr><td>noisemeter_warm_cycles </td><td> %19</td></tr>\
<tr><td>noisemeter_window_fuction </td><td> %20</td></tr>\
<tr><td>noisemeter_smooth_number </td><td> %21</td></tr>\
<tr><td>noisemeter_gain </td><td> %22</td></tr>\
<tr><td>noisemeter_gain_off_words </td><td> %23</td></tr>\
<tr><td>noisemeter_preconversion_pause </td><td> %24</td></tr>\
<tr><td>part_max_size </td><td> %25</td></tr>\
<tr><td>movement_variance_limit </td><td> %26</td></tr>\
<tr><td>variance_settle_period </td><td> %27</td></tr>\
<tr><td>bus_survey </td><td> %28</td></tr>\
<tr><td>reserve </td><td> %29</td></tr>\
<tr><td>crc16 </td><td> %30</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<ushort*>(ba.data()+2))
            .arg(QString::number(*reinterpret_cast<float*>(ba.data()+4)) + " " +
                 QString::number(*reinterpret_cast<float*>(ba.data()+8)))
            .arg(QString::number(*reinterpret_cast<ushort*>(ba.data()+12)) + " " +
                 QString::number(*reinterpret_cast<ushort*>(ba.data()+14)))
            .arg(*reinterpret_cast<ushort*>(ba.data()+16))
            .arg(*reinterpret_cast<ushort*>(ba.data()+18))
            .arg(*reinterpret_cast<ushort*>(ba.data()+20))
            .arg(*reinterpret_cast<ushort*>(ba.data()+22))
            .arg(*reinterpret_cast<ushort*>(ba.data()+24))
            .arg(*reinterpret_cast<ushort*>(ba.data()+26))
            .arg(*reinterpret_cast<ushort*>(ba.data()+28))
            .arg(*reinterpret_cast<uchar*>(ba.data()+30))
            .arg(*reinterpret_cast<ushort*>(ba.data()+31))
            .arg(*reinterpret_cast<ushort*>(ba.data()+33))
            .arg(*reinterpret_cast<ushort*>(ba.data()+35))
            .arg(*reinterpret_cast<ushort*>(ba.data()+37))
            .arg(*reinterpret_cast<ushort*>(ba.data()+39))
            .arg(*reinterpret_cast<uint*>(ba.data()+41))
            .arg(*reinterpret_cast<ushort*>(ba.data()+45))
            .arg(*reinterpret_cast<ushort*>(ba.data()+47))
            .arg(QString::number(*reinterpret_cast<ushort*>(ba.data()+49)) + " " +
                 QString::number(*reinterpret_cast<ushort*>(ba.data()+51)))
            .arg(*reinterpret_cast<uchar*>(ba.data()+53))
            .arg(*reinterpret_cast<ushort*>(ba.data()+54))
            .arg(*reinterpret_cast<ushort*>(ba.data()+56))
            .arg(*reinterpret_cast<ushort*>(ba.data()+58))
            .arg(*reinterpret_cast<uint*>(ba.data()+60))
            .arg(*reinterpret_cast<ushort*>(ba.data()+64))
            .arg(*reinterpret_cast<ushort*>(ba.data()+66))
            .arg("reserve")
            .arg(*reinterpret_cast<ushort*>(ba.data()+76));
}

void paramFlashAG(QString & data,QByteArray &ba){
    data += "<tr><td>total_length </td><td> %1</td></tr>\
<tr><td>head_to_discharger_length </td><td> %2</td></tr>\
<tr><td>click_interval_low_freq </td><td> %3</td></tr>\
<tr><td>click_interval_hi_freq </td><td> %4</td></tr>\
<tr><td>click_channel </td><td> %5</td></tr>\
<tr><td>stop_pwm_interval </td><td> %6</td></tr>\
<tr><td>wait_interval </td><td> %7</td></tr>\
<tr><td>start_pwm_interval </td><td> %8</td></tr>\
<tr><td>reception_enable_interval </td><td> %9</td></tr>\
<tr><td>pwm_period </td><td> %10</td></tr>\
<tr><td>set_voltage </td><td> %11</td></tr>\
<tr><td>CRC16 </td><td> %12</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<ushort*>(ba.data()+2))
            .arg(*reinterpret_cast<ushort*>(ba.data()+4))
            .arg(*reinterpret_cast<ushort*>(ba.data()+6))
            .arg(*reinterpret_cast<uchar*>(ba.data()+8))
            .arg(*reinterpret_cast<ushort*>(ba.data()+9))
            .arg(*reinterpret_cast<ushort*>(ba.data()+11))
            .arg(*reinterpret_cast<ushort*>(ba.data()+13))
            .arg(*reinterpret_cast<ushort*>(ba.data()+15))
            .arg(*reinterpret_cast<ushort*>(ba.data()+17))
            .arg(*reinterpret_cast<ushort*>(ba.data()+19))
            .arg(*reinterpret_cast<ushort*>(ba.data()+21));
}
void paramFlashP(QString & data,QByteArray &ba){
    data += "<tr><td>total_length </td><td> %1</td></tr>\
             <tr><td>CRC16 </td><td> %2</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<ushort*>(ba.data()+2));
}
void paramFlashP0204(QString & data,QByteArray &ba){
    data += "<tr><td>total_length </td><td> %1</td></tr>\
<tr><td>channel_1_offset </td><td> %2</td></tr>\
<tr><td>channel_2_offset </td><td> %3</td></tr>\
<tr><td>invert_rate_signum </td><td> %4</td></tr>\
<tr><td>CRC16 </td><td> %5</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<ushort*>(ba.data()+2))
            .arg(*reinterpret_cast<ushort*>(ba.data()+4))
            .arg(*reinterpret_cast<uchar*>(ba.data()+6))
            .arg(*reinterpret_cast<ushort*>(ba.data()+7));
}
void paramFlashGVK(QString & data,QByteArray &ba){
    data += "<tr><td>total_length </td><td> %1</td></tr>\
<tr><td>telemetry_speed </td><td> %2</td></tr>\
<tr><td>telemetry_resolution </td><td> %3</td></tr>\
<tr><td>gk_dac_set_value </td><td> %4</td></tr>\
<tr><td>gk_dac_min_value : %5</td></tr>\
<tr><td>gk_dac_max_value </td><td> %6</td></tr>\
<tr><td>extern_adc_temperature_config </td><td> %7</td></tr>\
<tr><td>extern_adc_temperature_2_config </td><td> %8</td></tr>\
<tr><td>extern_adc_pcorr_config </td><td> %9</td></tr>\
<tr><td>extern_adc_pbw_config </td><td> %10</td></tr>\
<tr><td>extern_adc_locator_config </td><td> %11</td></tr>\
<tr><td>extern_adc_accel_config </td><td> %12</td></tr>\
<tr><td>extern_adc_temperature_4_config </td><td> %13</td></tr>\
<tr><td>reserve </td><td> %14</td></tr>\
<tr><td>temperature_volatile </td><td> %15</td></tr>\
<tr><td>temperature_maximum </td><td> %16</td></tr>\
<tr><td>gk_dac_temperature_volatile </td><td> %17</td></tr>\
<tr><td>gk_dac_temperature_maximum </td><td> %18</td></tr>\
<tr><td>reserve </td><td> %19</td></tr>\
<tr><td>reserve </td><td> %20</td></tr>\
<tr><td>extern_adc_locator_offset </td><td> %21</td></tr>\
<tr><td>crc16 </td><td> %22</td></tr>";
            data = data.arg(*reinterpret_cast<ushort*>(ba.data()))
            .arg(*reinterpret_cast<uchar*>(ba.data()+2)).arg(*reinterpret_cast<uchar*>(ba.data()+3))
            .arg(*reinterpret_cast<ushort*>(ba.data()+4))
            .arg(*reinterpret_cast<short*>(ba.data()+6))
            .arg(*reinterpret_cast<short*>(ba.data()+8))
            .arg(*reinterpret_cast<ushort*>(ba.data()+10))
            .arg(*reinterpret_cast<ushort*>(ba.data()+12))
            .arg(*reinterpret_cast<ushort*>(ba.data()+14))
            .arg(*reinterpret_cast<ushort*>(ba.data()+16))
            .arg(*reinterpret_cast<ushort*>(ba.data()+18))
            .arg(*reinterpret_cast<ushort*>(ba.data()+20))
            .arg(*reinterpret_cast<ushort*>(ba.data()+22))
            .arg(*reinterpret_cast<uchar*>(ba.data()+24))
            .arg(*reinterpret_cast<float*>(ba.data()+25))
            .arg(*reinterpret_cast<float*>(ba.data()+29))
            .arg(*reinterpret_cast<ushort*>(ba.data()+33))
            .arg(*reinterpret_cast<ushort*>(ba.data()+35))
            .arg(*reinterpret_cast<ushort*>(ba.data()+37))
            .arg(*reinterpret_cast<uint*>(ba.data()+39))
            .arg(*reinterpret_cast<uint*>(ba.data()+43))
            .arg(*reinterpret_cast<ushort*>(ba.data()+47));
}
void channelGKT(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGKT();
    DataGKT *dS = reinterpret_cast<DataGKT*>(moduleData->dataStruct);
    memcpy(&dS->temperature_internal,data.data(),20);
    dS->type = GKT;
    dS->temperature_external = *reinterpret_cast<uint*>(data.mid(20,3).data());
    dS->sti_1 = *reinterpret_cast<uint*>(data.mid(23,3).data());
    dS->sti_2 = *reinterpret_cast<uint*>(data.mid(26,3).data());
    dS->p_corr = *reinterpret_cast<uint*>(data.mid(29,3).data());
    dS->p_bw = *reinterpret_cast<uint*>(data.mid(32,3).data());
    dS->acceleration_x = *reinterpret_cast<uint*>(data.mid(35,3).data());
    dS->acceleration_y = *reinterpret_cast<uint*>(data.mid(38,3).data());
    dS->acceleration_z = *reinterpret_cast<uint*>(data.mid(41,3).data());
    dS->locator_amp24 = *reinterpret_cast<uint*>(data.mid(44,3).data());
    dS->resistance = *reinterpret_cast<uint*>(data.mid(47,3).data());
    memcpy(&dS->sti_pwm,data.data() + 50,12);
    /*moduleData->data = "<table border='1'><tr><td>temperature_internal </td><td> %1</td></tr>\
<tr><td>locator_amp </td><td> %2</td></tr>\
<tr><td>locator_amp_interval_max </td><td> %3</td></tr>\
<tr><td>locator_amp_interval_min </td><td> %4</td></tr>\
<tr><td>gk_time </td><td> %5</td></tr>\
<tr><td>gk_impulses </td><td> %6</td></tr>\
<tr><td>gk_uhv </td><td> %7</td></tr>\
<tr><td>hygrometer </td><td> %8</td></tr>\
<tr><td>power_supply </td><td> %9</td></tr>\
<tr><td>emds_supply </td><td> %10</td></tr>\
<tr><td>temperature_external </td><td> %11</td></tr>\
<tr><td>sti_1 </td><td> %12</td></tr>\
<tr><td>sti_2 </td><td> %13</td></tr>\
<tr><td>p_corr </td><td> %14</td></tr>\
<tr><td>p_bw </td><td> %15</td></tr>\
<tr><td>acceleration_x </td><td> %16</td></tr>\
<tr><td>acceleration_y </td><td> %17</td></tr>\
<tr><td>acceleration_z </td><td> %18</td></tr>\
<tr><td>locator_amp </td><td> %19</td></tr>\
<tr><td>resistance </td><td> %20</td></tr>\
<tr><td>sti_pwm </td><td> %21</td></tr>\
<tr><td>pressure </td><td> %22</td></tr>\
<tr><td>temperature </td><td> %23</td></tr>\
<tr><td>gk_dac </td><td> %24</td></tr></table>";
    moduleData->data = moduleData->data.arg(dS->temperature_internal)
            .arg(dS->locator_amp16).arg(dS->locator_amp_interval_max)
            .arg(dS->locator_amp_interval_min).arg(dS->gk_time)
            .arg(dS->gk_impulses).arg(dS->gk_uhv).arg(dS->hygrometer)
            .arg(dS->power_supply).arg(dS->emds_supply).arg(dS->temperature_external)
            .arg(dS->sti_1).arg(dS->sti_2).arg(dS->p_corr).arg(dS->p_bw).arg(dS->acceleration_x)
            .arg(dS->acceleration_y).arg(dS->acceleration_z).arg(dS->locator_amp24).arg(dS->resistance)
            .arg(dS->sti_pwm).arg(dS->pressure).arg(dS->temperature).arg(dS->gk_dac);*/
}

void Parser38kModules::channelSHM(PacketModulesData38k * moduleData){
    int size = moduleData->dataBytes.size();
    int position = 0;
    QByteArray *data = &moduleData->dataBytes;
    moduleData->dataStruct = new DataSHM1();
    DataSHM1 *dS = reinterpret_cast<DataSHM1*>(moduleData->dataStruct);
    dS->type = SHM;
    if(!moduleData->header.currentPartNo){
        QByteArray *data = &moduleData->dataBytes;
        moduleData->dataStruct = new DataSHM0();
        DataSHM0 *dS = reinterpret_cast<DataSHM0*>(moduleData->dataStruct);
        dS->type = SHM;
        memcpy(&dS->periph_status,data->data(),20);
        isWave = dS->work_mode&0x0001;
        wordPerChannel = dS->words_per_channel;
        /*moduleData->data = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>work_mode_MSB </td><td> %2</td></tr>\
<tr><td>work_mode_LSB </td><td> %3</td></tr>\
<tr><td>channels_map </td><td> %4</td></tr>\
<tr><td>words_per_channel </td><td> %5</td></tr>\
<tr><td>channel_frequency </td><td> %6</td></tr>\
<tr><td>pga_gain </td><td> %7</td></tr>\
<tr><td>temperature_internal </td><td> %8</td></tr>\
<tr><td>accel_z_mean </td><td> %9</td></tr>\
<tr><td>accel_z_variance </td><td> %10</td></tr>\
<tr><td>accel_z_flags </td><td> %11</td></tr>\
<tr><td>Data </td></tr></table>";
        currentChannel = 0;
        currentWordPerChannel = 0;
        moduleData->data = moduleData->data.arg(dS->periph_status)
                .arg(dS->work_mode&0x8000).arg(dS->work_mode&0x0001).arg(dS->channels_map).arg(dS->words_per_channel)
                .arg(dS->channel_frequency).arg(dS->pga_gain).arg(dS->temperature_internal)
                .arg(dS->accel_z_mean).arg(dS->accel_z_variance).arg(dS->accel_z_flags);*/
        position = 20;
    }
    moduleData->data += "<table border='1'><tr><td>";
    if(!isWave){
        dS->Wave_1int = nullptr;
        dS->Wave_1float = new QVector<float>();
        for(int i = position; i < size - 4;i+=4){
            if(!currentWordPerChannel){
                moduleData->data += "</td></tr><tr><td  align='center'>Channel " + QString::number(currentChannel++)+ "</td></tr>";
                currentWordPerChannel = wordPerChannel;
            }
            dS->Wave_1float->push_back(*reinterpret_cast<float*>(data->mid(i,4).data()));
            moduleData->data += QString::number(dS->Wave_1float->last()) + " ";
            currentWordPerChannel--;
        }
    }
    else{
        dS->Wave_1int = new QVector<short>();
        dS->Wave_1float = nullptr;
        for(int i = position; i < size - 2;i += 2){
            if(!currentWordPerChannel){
                //moduleData->data += "<tr><td align='center'>Channel " + QString::number(currentChannel++) + "</td></tr>";
                currentWordPerChannel = wordPerChannel;
            }
            dS->Wave_1int->push_back(*reinterpret_cast<short*>(data->data()+i));
            //moduleData->data += QString::number(dS->Wave_1int->last()) + "  ";
            currentWordPerChannel--;
        }
   }
   //moduleData->data += "</table>";
}

void channelAG(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataAG();
    DataAG *dS = reinterpret_cast<DataAG*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),8);
    dS->type = AG;
    /*moduleData->data = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>work_mode </td><td> %2</td></tr>\
<tr><td>temperature_internal </td><td> %3</td></tr>\
<tr><td>discharge_voltage </td><td> %4</td></tr></table>";
            moduleData->data = moduleData->data.arg(dS->periph_status)
            .arg(dS->work_mode)
            .arg(dS->temperature_internal)
            .arg(dS->discharge_voltage);*/
}
void channelP(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP();
    DataP *dS = reinterpret_cast<DataP*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),10);
    dS->type = MP;
    moduleData->data = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>angle </td><td> %2</td></tr>\
<tr><td>rate </td><td> %3</td></tr>\
<tr><td>temperature_internal </td><td> %4</td></tr></table>";
    moduleData->data = moduleData->data.arg(dS->periph_status).arg(dS->angle).arg(dS->rate).arg(dS->temperature_internal);

}

void channelP02(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP02();
    DataP02 *dS = reinterpret_cast<DataP02*>(moduleData->dataStruct);
    memcpy(&dS->rate,data.data(),8);
    dS->type = P02;
    /*moduleData->data = "<table border='1'><tr><td>rate </td><td> %1</td></tr>\
<tr><td>diameter </td><td> %2</td></tr>\
<tr><td>temperature_internal </td><td> %3</td></tr></table>";
            moduleData->data = moduleData->data.arg(dS->rate).arg(dS->diameter).arg(dS->temperature_internal);*/
}

void channelP04(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP04();
    DataP04 *dS = reinterpret_cast<DataP04*>(moduleData->dataStruct);
    memcpy(&dS->rate,data.data(),3);
    /*QString channel = "<table border='1'><tr><td>rate </td><td> %1</td></tr>\
<tr><td>temperature_internal </td><td> %2</td></tr></table>";
            channel = channel.arg(dS->rate)
            .arg(dS->temperature_internal);*/
}

void channel2NNKt(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new Data2NNKT();
    Data2NNKT *dS = reinterpret_cast<Data2NNKT*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),21);
    QString channel = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>count_time </td><td> %2</td></tr>\
<tr><td>near_count </td><td> %3</td></tr>\
<tr><td>far_count </td><td> %4</td></tr>\
<tr><td>gk_uhv </td><td> %5</td></tr>\
<tr><td>gk_dac </td><td> %6</td></tr>\
<tr><td>temperature_internal </td><td> %7</td></tr>\
<tr><td>comp_edac1_value </td><td> %8</td></tr>\
<tr><td>comp_edac2_value </td><td> %9</td></tr></table>";
    channel = channel.arg(dS->periph_status).arg(dS->count_time).arg(dS->near_count)
            .arg(dS->far_count).arg(dS->gk_uhv).arg(dS->gk_dac).arg(dS->temperature_internal)
            .arg(dS->comp_edac1_value).arg(dS->comp_edac2_value);
}
void channelGGP(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGGP();
    DataGGP *dS = reinterpret_cast<DataGGP*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),15);
    QString channel = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>count_time </td><td> %2</td></tr>\
<tr><td>count </td><td> %3</td></tr>\
<tr><td>gk_uhv </td><td> %4</td></tr>\
<tr><td>gk_dac </td><td> %5</td></tr>\
<tr><td>temperature_internal </td><td> %6</td></tr>\
<tr><td>comp_edac_value </td><td> %7</td></tr></table>";
            channel = channel.arg(dS->periph_status)
            .arg(dS->count_time)
            .arg(dS->count)
            .arg(dS->gk_uhv)
            .arg(dS->gk_dac)
            .arg(dS->temperature_internal)
            .arg(dS->comp_edac_value);
}
void channelGVK(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGVK();
    DataGVK *dS = reinterpret_cast<DataGVK*>(moduleData->dataStruct);
    memcpy(&dS->temperature_internal,data.data(),48);
    QString channel = "<table border='1'><tr><td>temperature_internal </td><td> %1</td></tr>\
<tr><td>locator_amp </td><td> %2</td></tr>\
<tr><td>locator_amp_interval_max </td><td> %3</td></tr>\
<tr><td>locator_amp_interval_min </td><td> %4</td></tr>\
<tr><td>gk_time </td><td> %5</td></tr>\
<tr><td>gk_impulses </td><td> %6</td></tr>\
<tr><td>gk_uhv </td><td> %7</td></tr>\
<tr><td>power_supply </td><td> %8</td></tr>\
<tr><td>temperature_external </td><td> %9</td></tr>\
<tr><td>temperature_external_2 </td><td> %10</td></tr>\
<tr><td>temperature_external_3 </td><td> %11</td></tr>\
<tr><td>p_corr </td><td> %12</td></tr>\
<tr><td>p_bw </td><td> %13</td></tr>\
<tr><td>acceleration_x </td><td> %14</td></tr>\
<tr><td>acceleration_y </td><td> %15</td></tr>\
<tr><td>acceleration_z </td><td> %16</td></tr>\
<tr><td>locator_amp </td><td> %17</td></tr>\
<tr><td>temperature_external_4 </td><td> %18</td></tr>\
<tr><td>gk_dac </td><td> %19</td></tr></table>";
    channel = channel.arg(dS->temperature_internal).arg(dS->locator_amp16)
            .arg(dS->locator_amp_interval_max).arg(dS->locator_amp_interval_min)
            .arg(dS->gk_time).arg(dS->gk_impulses).arg(dS->gk_uhv)
            .arg(dS->power_supply).arg(dS->temperature_external).arg(dS->temperature_external2)
            .arg(dS->temperature_external3).arg(dS->p_corr).arg(dS->p_bw)
            .arg(dS->acceleration_x).arg(dS->acceleration_y).arg(dS->acceleration_z)
            .arg(dS->locator_amp24).arg(dS->temperature_external4).arg(dS->gk_dac);
}
void Parser38kModules::moduleDataParsing(PacketModulesData38k * moduleData){
    moduleData->dataStruct = nullptr;
    QString * data = &moduleData->data;
    if(moduleData->header.data_state & 0x02){
        QString hardFlash = "<table border='1' >\
<tr><td colspan = '2' align='center'> HardFlash: </td></tr>\
<tr><td> total_length </td><td>  %1 </td></tr>\
<tr><td> device_type </td><td>  %2 </td></tr>\
<tr><td> device_number </td><td>  %3 </td></tr>\
<tr><td> production_day </td><td>  %4 </td></tr>\
<tr><td> production_month </td><td>  %5 </td></tr>\
<tr><td> production_year </td><td>  %6 </td></tr>\
<tr><td> device_name </td><td>  %7 </td></tr>\
<tr><td> device_code </td><td>  %8 </td></tr>\
<tr><td> device_decimal </td><td>  %9 </td></tr>\
<tr><td> flash_version </td><td>  %10 </td></tr>\
<tr><td> firmware_version </td><td>  %11 </td></tr>\
<tr><td> reserved </td><td>  %12 </td></tr>\
<tr><td> device_tag </td><td>  %13 </td></tr>\
<tr><td> device_length </td><td>  %14 </td></tr>\
<tr><td> device_tech_header_size </td><td>  %15 </td></tr>\
<tr><td> device_data_size </td><td>  %16 </td></tr>\
<tr><td> data_parts_max </td><td>  %17 </td></tr>";

        bool moduleAdded = false;
        ushort deviceType = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+2);
        ushort length = *reinterpret_cast<ushort*>(moduleData->dataBytes.data());
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
        hardFlash = hardFlash.arg(length).arg(deviceType)
        .arg(QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(4,12).data()))
        .arg(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+16)).arg(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+17))
        .arg(*reinterpret_cast<ushort*>(moduleData->dataBytes.data()+18))
        .arg(QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(20,16).data()))
        .arg(QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(36,6).data()))
        .arg(QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(42,6).data()))
        .arg(QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+48)) + "." + QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+49)))
        .arg(QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+50)) + "." + QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+51)))
        .arg("res")
        .arg(QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(56,20).data()))
        .arg(*reinterpret_cast<ushort*>(moduleData->dataBytes.data()+76))
        .arg(*reinterpret_cast<ushort*>(moduleData->dataBytes.data()+78))
        .arg(*reinterpret_cast<uint*>(moduleData->dataBytes.data()+80))
        .arg(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+84));
        int numberOfChannels = (length-86)/8;
        for(int i = 0; i <  numberOfChannels;i++){
            hardFlash += "<tr><td colspan = '2' align='center' > %1 </td></tr>\
<tr><td> channel_mnemonics </td><td>  %2 </td></tr>\
<tr><td> channel_write_point </td><td>  %3 </td></tr>\
<tr><td> channel_flags </td><td>  %4 </td></tr>";
            hardFlash = hardFlash.arg("\n\tchannel " + QString::number(i) + ":").arg(*reinterpret_cast<uint*>(moduleData->dataBytes.data()+85+(i*8)))
            .arg(*reinterpret_cast<ushort*>(moduleData->dataBytes.data()+89+(i*8)))
            .arg(*reinterpret_cast<ushort*>(moduleData->dataBytes.data()+91+(i*8)));
        }
        hardFlash+= "<tr><td>CRC16</td><td>" + moduleData->dataBytes.mid(85+(numberOfChannels*8),2).toHex() + "</td></tr>";
        length = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+87);
        QString paramFlash = "<tr><td colspan = '2' align='center'> ParamFlash: </td></tr>";
        QByteArray paramFlashArray = moduleData->dataBytes.mid(87 +(numberOfChannels * 8),length);

        if(deviceType == GKT)
           paramFlashGKT(paramFlash,paramFlashArray);
        else if(deviceType == SHM)
           paramFlashSHM(paramFlash,paramFlashArray);
        else if(deviceType == AG)
           paramFlashAG(paramFlash,paramFlashArray);
        else if(deviceType == MP)
           paramFlashP(paramFlash,paramFlashArray);
        else if(deviceType == P02 || deviceType == P04)
           paramFlashP0204(paramFlash,paramFlashArray);
        else if(deviceType == GVK)
           paramFlashGVK(paramFlash,paramFlashArray);

        QString calibFlash = "<tr><td colspan = '2' align='center'>CalibFlash:</td></tr>" + moduleData->dataBytes.mid(87 +(numberOfChannels * 8) + (length)).toHex();
        *data = hardFlash + paramFlash + calibFlash + "</table>";
    }
    else if(!(moduleData->header.data_state & 0x01) & !moduleData->dataBytes.isEmpty()){
        uint type = 124;
        if(listOfFoundModules->size() != 0)
            for(auto value = listOfFoundModules->begin();value < listOfFoundModules->end();value++)
                if(value->moduleAddress == moduleData->header.moduleAddress){
                    type = value->type;
                    break;
                }
        if(type == GKT)
           channelGKT(moduleData);
        else if(type == SHM)
           channelSHM(moduleData);
        else if(type == AG)
           channelAG(moduleData);
        else if(type == MP)
           channelP(moduleData);
        else if(type == P04)
           channelP04(moduleData);
        else if(type == P02)
           channelP02(moduleData);
        else if(type == GVK)
           channelGVK(moduleData);
        else if(type == NNKt)
           channel2NNKt(moduleData);
        else if(type == GGP)
           channelGGP(moduleData);
    }
}
Parser38kModules::Parser38kModules(QList<PacketModulesData38k> *modulesData){
    this->modulesData = modulesData;
    this->listOfFoundModules = new QList<NumberType>;
    enabled = true;
    connect(this, SIGNAL(finished(void)), this, SLOT(del()));
}
void Parser38kModules::run(){
    QTime time =  QTime::currentTime();
    for(auto value = modulesData->begin();value < modulesData->end(); value++)
        if(enabled)
            moduleDataParsing(&*value);
        else
           return;
    qDebug() <<   time.msecsTo(QTime::currentTime());
}
void Parser38kModules::stop(){
    enabled = false;
}
void Parser38kModules::del(){
    this->~Parser38kModules();
}
Parser38kModules::~Parser38kModules(){
    if(this->listOfFoundModules)
        delete this->listOfFoundModules;
    this->listOfFoundModules = nullptr;
}


void Parser38k::findModulesDataBytes(PacketDeviceData38k pack){
    QByteArray moduleDataByteArray;
    int position = 0;
        dataBytes += pack.data.dataByte.mid(0);
        int size = dataBytes.size();
        while(position < size){
            PacketModulesData38k moduleData;
            moduleData.header.moduleAddress = *reinterpret_cast<unsigned char*>(dataBytes.data()+position);
            moduleData.header.data_state = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+1);
            moduleData.header.totalSize = *reinterpret_cast<unsigned short*>((dataBytes.data()+position+2));
            if(moduleData.header.totalSize > size - position || moduleData.header.totalSize < 12)
                break;
            moduleDataByteArray = dataBytes.mid(position,moduleData.header.totalSize);
            moduleData.status =  crc.crcFast(reinterpret_cast<uchar*>(moduleDataByteArray.data()),moduleData.header.totalSize)?0x80:0;
            int posLastComSt = 0;
            if(moduleData.header.data_state & 0x80){
                moduleData.header.totalDataSize = moduleData.header.totalSize - 14;
                moduleData.header.totalParts = 1;
                moduleData.header.currentPartNo = 0;
                moduleData.dataBytes = moduleDataByteArray.mid(12,moduleData.header.totalSize - 14);
            }
            else{
                moduleData.header.totalDataSize = *reinterpret_cast<unsigned short*>((dataBytes.data()+position+4));
                moduleData.header.totalParts = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+6);
                moduleData.header.currentPartNo = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+7);
                posLastComSt = 4;
                moduleData.dataBytes = moduleDataByteArray.mid(16,moduleData.header.totalSize - 14);
            }
            int pos = position + posLastComSt + 4;
            moduleData.header.lastCommandState = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos);
            moduleData.header.commandCounter = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+1);
            moduleData.header.lastCommandCrc = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+2);
            moduleData.header.lastCommandCode = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+3);
            moduleData.header.requestTime = *reinterpret_cast<uint*>(dataBytes.data()+pos+4);

            //moduleDataParsing(&moduleData);
            moduleData.dataStruct = nullptr;
            emit  getModData38k(moduleData);
            position += moduleDataByteArray.size();
        }
        dataBytes = dataBytes.mid(position);
        position = 0;
        if(dataBytes.toHex() == "00")
            dataBytes.resize(0);
}
void Parser38k::findServiseFFFEBytes(TlmPack pack){
    unsigned char array[255];
        QByteArray data = pack.dataPacketBytes.data.mid(2);
        QByteArray bl255;
        QByteArray byteArray;
        PacketDeviceData38k packetDeviceData;
        packetDeviceData.data.status = 0;
        for(int position = 0; position < data.length();position+=255 ){
           // memset(array,0,255);
            bl255 = data.mid(position,255);
            //memcpy(array,bl255.data(),bl255.size());
            //int decod = cod.decode_rs_nasa(array);
            //this->numberOfChecks++;
            //this->numberOfError += decod?1:0;
            //packetDeviceData.data.status |= decod;
            packetDeviceData.data.dataByte += bl255.mid(33);
        }

        QByteArray serv = packetDeviceData.data.dataByte.mid(0,12);
        memset(array,0,255);
        memcpy(array,serv.data(),12);
        this->numberOfChecks++;
        int crcF = crc.crcFast(array,12);
        if(crcF)
            this->numberOfError++;
        if((packetDeviceData.data.status == 2 && crcF) || serv.size() == 0){
            return;
        }
        packetDeviceData.data.dataByte = packetDeviceData.data.dataByte.mid(12);
        packetDeviceData.serv.systemTime = *reinterpret_cast<uint*>(serv.data());
        packetDeviceData.serv.transmissionCounter = *reinterpret_cast<unsigned short*>(serv.data()+4);
        packetDeviceData.serv.totalModules = *reinterpret_cast<unsigned char*>(serv.data()+6);
        packetDeviceData.serv.speedTelemetry = (*reinterpret_cast<unsigned char*>(serv.data()+7) << 4) & 0x0f;
        packetDeviceData.serv.bitDepthTelemetry = *reinterpret_cast<unsigned char*>(serv.data()+7) >> 4;
        packetDeviceData.serv.commandCounter = *reinterpret_cast<unsigned char*>(serv.data()+8);
        packetDeviceData.serv.reserved = *reinterpret_cast<unsigned char*>(serv.data()+9);
        packetDeviceData.serv.crc16 = *reinterpret_cast<unsigned short*>(serv.data()+10);
        findModulesDataBytes(packetDeviceData);
}
Parser38k::Parser38k(FileReader *file){
    this->tlmDeviceData = new QList<TlmPack>;
    this->byteArrayData = file->getByteArray();
    delete file;
    file = nullptr;
    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}

void Parser38k::run(){
    numberOfChecks = 0;
    numberOfError = 0;
    QTime time = QTime::currentTime();
    ParserTLM *parserTlm = new ParserTLM(this->byteArrayData);
    QList<BlockTlm> *tlmBlocks = parserTlm->getBlocks();
    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPacketBytes.dev_type == "ADSP" && pack->dataPacketBytes.inf_type == "GETDATA"){
                findServiseFFFEBytes(*pack);
            }

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
    this->tlmDeviceData = nullptr;
    this->quit();
}
