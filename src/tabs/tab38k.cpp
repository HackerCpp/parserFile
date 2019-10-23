#include "inc/tabs/tab38k.h"
#include <QPropertyAnimation>

QString paramFlashGKT(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashGKT *pF = reinterpret_cast<ParamFlashGKT*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashGKT.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    file.close();
    str = str.arg(pF->total_length).arg(pF->telemetry_speed).arg(pF->telemetry_resolution).arg(pF->resistance_divisor).arg(pF->resistance_phase_one).arg(pF->resistance_phase_two)
            .arg(pF->gk_dac_set_value).arg(pF->gk_dac_min_value).arg(pF->gk_dac_max_value).arg(pF->hygro_hi_prescaler).arg(pF->hygro_hi_timeout).arg(pF->hygro_lo_pulses)
            .arg(pF->sti_max_temperature).arg(pF->sti_min_temperature).arg(pF->emds_disable).arg(pF->gk_noisemeter_mode).arg(pF->sti_start_duty_value).arg(pF->extern_adc_temperature_config).arg(pF->extern_adc_std_config)
            .arg(pF->extern_adc_pcorr_config).arg(pF->extern_adc_pbw_config).arg(pF->extern_adc_locator_config).arg(pF->extern_adc_accel_config).arg(pF->extern_adc_resist_config).arg(pF->add_command_dump)
            .arg(pF->temperature_volatile).arg(pF->temperature_maximum).arg(pF->gk_dac_temperature_volatile).arg(pF->gk_dac_temperature_maximum).arg(pF->temperature_addition).arg(pF->reserve)
            .arg(pF->extern_adc_locator_offset).arg(pF->crc16);
    return str;
}

QString paramFlashSHM(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashSHM *pF = reinterpret_cast<ParamFlashSHM*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashSHM.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());
    file.close();
    QString coeff = QString::number(pF->channel_coefficients[0]) + "; " + QString::number(pF->channel_coefficients[1]);
    QString sensorLenght = QString::number(pF->head_to_sensor_length[0]) + "; " + QString::number(pF->head_to_sensor_length[1]);
    QString smuth = QString::number(pF->noisemeter_smooth_number[0]) + "; " + QString::number(pF->noisemeter_smooth_number[1]);
    str = str.arg(pF->total_length).arg(pF->sensor_number).arg(coeff).arg(sensorLenght).arg(pF->startup_mode).arg(pF->hardware_swap_channels).arg(pF->hardware_invert_channels).arg(pF->acoustics_startup_channels)
            .arg(pF->acoustics_startup_adc_time).arg(pF->acoustics_startup_period).arg(pF->acoustics_start_offset).arg(pF->acoustics_gain).arg(pF->acoustics_gain_off_words).arg(pF->acoustics_preconversion_pause).arg(pF->generator_wait_interval).arg(pF->noisemetr_startup_channels)
            .arg(pF->noisemetr_startup_words).arg(pF->noisemeter_startup_freq).arg(pF->noisemeter_warm_cycles).arg(pF->noisemeter_window_function).arg(smuth).arg(pF->noisemeter_gain).arg(pF->noisemeter_gain_off_words).arg(pF->noisemeter_preconversion_pause)
            .arg(pF->part_max_size).arg(pF->movement_variance_limit).arg(pF->variance_settle_period).arg(pF->bus_survey).arg(0).arg(pF->crc16);
    return str;
}

QString paramFlashAG(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashAG *pF = reinterpret_cast<ParamFlashAG*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashAG.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(pF->total_length).arg(pF->head_to_discharger_length).arg(pF->click_interval_low_freq).arg(pF->click_interval_hi_freq).arg(pF->click_channel).arg(pF->stop_pwm_interval)
            .arg(pF->wait_interval).arg(pF->start_pwm_interval).arg(pF->reception_enable_interval).arg(pF->pwm_period).arg(pF->set_voltage).arg(pF->crc16);
    return str;
}
QString paramFlashP(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashP *pF = reinterpret_cast<ParamFlashP*>(dS->paramFlash);
    QString str = "<tr><td colspan = '2' align='center'> ParamFlash: </td></tr>\
<tr><td>total_length </td><td> %1</td></tr>\
<tr><td>CRC16 </td><td> %2</td></tr>";
    str = str.arg(pF->total_length).arg(pF->crc16);
    return str;
}
QString paramFlashP0204(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashP02P04 *pF = reinterpret_cast<ParamFlashP02P04*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashP02P04.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(pF->total_length).arg(pF->channel_1_offset).arg(pF->channel_2_offset).arg(pF->invert_rate_signum).arg(pF->crc16);
    return str;
}
QString paramFlashGVK(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashGVK *pF = reinterpret_cast<ParamFlashGVK*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashGVK.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(pF->total_length).arg(pF->telemetry_speed).arg(pF->telemetry_resolution).arg(pF->gk_dac_set_value).arg(pF->gk_dac_min_value).arg(pF->gk_dac_max_value).arg(pF->extern_adc_temperature_config)
            .arg(pF->extern_adc_temperature_2_config).arg(pF->extern_adc_pcorr_config).arg(pF->extern_adc_pbw_config).arg(pF->extern_adc_locator_config).arg(pF->extern_adc_accel_config)
            .arg(pF->extern_adc_temperature_4_config).arg(pF->reserve).arg(pF->temperature_volatile).arg(pF->temperature_maximum).arg(pF->reserve2).arg(pF->reserve3).arg(pF->extern_adc_locator_offset).arg(pF->crc16);
    return str;
}
QString paramFlashNNKt(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashNNKt *pF = reinterpret_cast<ParamFlashNNKt*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashNNKt.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(pF->total_length).arg(pF->near_counter_threshold).arg(pF->far_counter_threshold).arg(pF->swap_shannels).arg(pF->dac_set_value).arg(pF->dac_min_value).arg(pF->dac_max_value).arg(pF->temperature_volatile)
            .arg(pF->temperature_maximum).arg(pF->dac_temperature_volatile).arg(pF->dac_temperature_maximum).arg(pF->temperature_addition).arg(0).arg(pF->crc16);
    return str;
}
QString paramFlashGGP(const PacketModulesData38k & moduleData){
    Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
    ParamFlashGGP *pF = reinterpret_cast<ParamFlashGGP*>(dS->paramFlash);
    QFile file("template\\38k\\paramFlashGGP.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(pF->total_length).arg(pF->counter_threshold).arg(pF->swap_channels).arg(pF->dac_set_value).arg(pF->dac_min_value).arg(pF->dac_max_value)
            .arg(pF->temperature_volatile).arg(pF->temperature_maximum).arg(pF->dac_temperature_volatile).arg(pF->dac_temperature_maximum).arg(pF->temperature_addition).arg(0).arg(pF->crc16);
    return str;
}

QString channelGKT(const PacketModulesData38k & moduleData){
    DataGKT *dS = reinterpret_cast<DataGKT*>(moduleData.dataStruct);
    QFile file("template\\38k\\channelGKT.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(dS->temperature_internal).arg(dS->locator_amp16).arg(dS->locator_amp_interval_max).arg(dS->locator_amp_interval_min).arg(dS->gk_time)
            .arg(dS->gk_impulses).arg(dS->gk_uhv).arg(dS->hygrometer).arg(dS->power_supply).arg(dS->emds_supply).arg(dS->temperature_external).arg(dS->sti_1).arg(dS->sti_2).arg(dS->p_corr).arg(dS->p_bw).arg(dS->acceleration_x)
            .arg(dS->acceleration_y).arg(dS->acceleration_z).arg(dS->locator_amp24).arg(dS->resistance).arg(dS->sti_pwm).arg(dS->pressure).arg(dS->temperature).arg(dS->gk_dac);
    return str;
}

QString channelSHM(const PacketModulesData38k & moduleData){
    int isWave;
    QString str;
    DataSHM1 *dS = reinterpret_cast<DataSHM1*>(moduleData.dataStruct);
    if(!moduleData.header.currentPartNo){
        DataSHM0 *dS = reinterpret_cast<DataSHM0*>(moduleData.dataStruct);
        isWave = dS->work_mode&0x0001;
        str = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
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
        str = str.arg(dS->periph_status)
                .arg(dS->work_mode&0x8000).arg(dS->work_mode&0x0001).arg(dS->channels_map).arg(dS->words_per_channel)
                .arg(dS->channel_frequency).arg(dS->pga_gain).arg(dS->temperature_internal)
                .arg(dS->accel_z_mean).arg(dS->accel_z_variance).arg(dS->accel_z_flags);
        str += "<table border='1'><tr><td>";
        if(dS->Wave_1float){
            foreach(float value,*dS->Wave_1float){
                str += QString::number(value) + " ";
            }
        }
        else if(dS->Wave_1int){
            foreach(float value,*dS->Wave_1int){
                str += QString::number(value) + " ";
            }
       }
    }
    else{
        str += "<table border='1'><tr><td>";
        if(dS->Wave_1float){
            foreach(float value,*dS->Wave_1float){
                str += QString::number(value) + " ";
            }
        }
        else if(dS->Wave_1int){
            foreach(float value,*dS->Wave_1int){
                str += QString::number(value) + " ";
            }
        }
    }
    str+="</table>";
    return str;
}

QString channelAG(const PacketModulesData38k & moduleData){
    DataAG *dS = reinterpret_cast<DataAG*>(moduleData.dataStruct);
    QString str = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>work_mode </td><td> %2</td></tr>\
<tr><td>temperature_internal </td><td> %3</td></tr>\
<tr><td>discharge_voltage </td><td> %4</td></tr></table>";
            str = str.arg(dS->periph_status)
            .arg(dS->work_mode)
            .arg(dS->temperature_internal)
            .arg(dS->discharge_voltage);
    return str;
}
QString channelP(const PacketModulesData38k & moduleData){
    DataP *dS = reinterpret_cast<DataP*>(moduleData.dataStruct);
    QString str = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>angle </td><td> %2</td></tr>\
<tr><td>rate </td><td> %3</td></tr>\
<tr><td>temperature_internal </td><td> %4</td></tr></table>";
    str = str.arg(dS->periph_status).arg(dS->angle).arg(dS->rate).arg(dS->temperature_internal);
    return str;
}

QString channelP02(const PacketModulesData38k & moduleData){
   DataP02 *dS = reinterpret_cast<DataP02*>(moduleData.dataStruct);
   QString str = "<table border='1'><tr><td>rate </td><td> %1</td></tr>\
<tr><td>diameter </td><td> %2</td></tr>\
<tr><td>temperature_internal </td><td> %3</td></tr></table>";
            str = str.arg(dS->rate).arg(dS->diameter).arg(dS->temperature_internal);
   return str;
}

QString channelP04(const PacketModulesData38k & moduleData){
    DataP04 *dS = reinterpret_cast<DataP04*>(moduleData.dataStruct);
    QString str= "<table border='1'><tr><td>rate </td><td> %1</td></tr>\
<tr><td>temperature_internal </td><td> %2</td></tr></table>";
            str = str.arg(dS->rate)
            .arg(dS->temperature_internal);
    return str;
}

QString channel2NNKt(const PacketModulesData38k & moduleData){
    Data2NNKT *dS = reinterpret_cast<Data2NNKT*>(moduleData.dataStruct);
    QString str = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>count_time </td><td> %2</td></tr>\
<tr><td>near_count </td><td> %3</td></tr>\
<tr><td>far_count </td><td> %4</td></tr>\
<tr><td>gk_uhv </td><td> %5</td></tr>\
<tr><td>gk_dac </td><td> %6</td></tr>\
<tr><td>temperature_internal </td><td> %7</td></tr>\
<tr><td>comp_edac1_value </td><td> %8</td></tr>\
<tr><td>comp_edac2_value </td><td> %9</td></tr></table>";
    str = str.arg(dS->periph_status).arg(dS->count_time).arg(dS->near_count)
            .arg(dS->far_count).arg(dS->gk_uhv).arg(dS->gk_dac).arg(dS->temperature_internal)
            .arg(dS->comp_edac1_value).arg(dS->comp_edac2_value);
    return str;
}
QString channelGGP(const PacketModulesData38k & moduleData){
    DataGGP *dS = reinterpret_cast<DataGGP*>(moduleData.dataStruct);
    QString str = "<table border='1'><tr><td>periph_status </td><td> %1</td></tr>\
<tr><td>count_time </td><td> %2</td></tr>\
<tr><td>count </td><td> %3</td></tr>\
<tr><td>gk_uhv </td><td> %4</td></tr>\
<tr><td>gk_dac </td><td> %5</td></tr>\
<tr><td>temperature_internal </td><td> %6</td></tr>\
<tr><td>comp_edac_value </td><td> %7</td></tr></table>";
            str = str.arg(dS->periph_status)
            .arg(dS->count_time)
            .arg(dS->count)
            .arg(dS->gk_uhv)
            .arg(dS->gk_dac)
            .arg(dS->temperature_internal)
            .arg(dS->comp_edac_value);
    return str;
}
QString channelGVK(const PacketModulesData38k & moduleData){
    DataGVK *dS = reinterpret_cast<DataGVK*>(moduleData.dataStruct);
    QFile file("template\\38k\\channelGVK.html");
    file.open(QFile::ReadOnly);
    QString str = QLatin1String(file.readAll());file.close();
    str = str.arg(dS->temperature_internal).arg(dS->locator_amp16)
            .arg(dS->locator_amp_interval_max).arg(dS->locator_amp_interval_min)
            .arg(dS->gk_time).arg(dS->gk_impulses).arg(dS->gk_uhv)
            .arg(dS->power_supply).arg(dS->temperature_external).arg(dS->temperature_external2)
            .arg(dS->temperature_external3).arg(dS->p_corr).arg(dS->p_bw)
            .arg(dS->acceleration_x).arg(dS->acceleration_y).arg(dS->acceleration_z)
            .arg(dS->locator_amp24).arg(dS->temperature_external4).arg(dS->gk_dac);
    return str;
}

QString dataString(const PacketModulesData38k &moduleData){
    if(!moduleData.dataStruct)
        return "...";
    int type = moduleData.dataStruct->type;
    if(moduleData.header.data_state & 0x02){
        Flash *dS = reinterpret_cast<Flash*>(moduleData.dataStruct);
        QFile file("template\\38k\\hardFlash.html");
        file.open(QFile::ReadOnly);
        QString str = QLatin1String(file.readAll());file.close();
        str = str.arg(dS->hardFlash.total_length).arg(dS->hardFlash.device_tipe).arg(dS->hardFlash.device_number)
                .arg(dS->hardFlash.production_day).arg(dS->hardFlash.production_month).arg(dS->hardFlash.production_year)
                .arg(dS->hardFlash.device_name).arg(dS->hardFlash.device_code).arg(dS->hardFlash.device_decimal)
                .arg(dS->hardFlash.flash_version).arg(dS->hardFlash.firmware_version).arg(dS->hardFlash.reserved)
                .arg(dS->hardFlash.device_tag).arg(dS->hardFlash.device_length).arg(dS->hardFlash.device_tech_header_size)
                .arg(dS->hardFlash.device_data_size).arg(dS->hardFlash.data_parts_max);
     foreach(ChannelInformation value,dS->hardFlash.channel){
                str += "<tr><td colspan = '2' align='center' > Channel </td></tr><tr><td> channel_mnemonics </td><td>  %1 </td></tr>\
<tr><td> channel_write_point </td><td>  %2 </td></tr><tr><td> channel_flags </td><td>  %3 </td></tr>";
                str = str.arg(value.channel_mnemonics).arg(value.channel_write_point).arg(value.channel_flags);
     }
        if(type == GKT)
            str += paramFlashGKT(moduleData);
        else if(type == SHM)
            str += paramFlashSHM(moduleData);
        else if(type == AG)
            str += paramFlashAG(moduleData);
        else if(type == MP)
            str += paramFlashP(moduleData);
        else if(type == P04 | type == P02)
            str += paramFlashP0204(moduleData);
        else if(type == GVK)
            str += paramFlashGVK(moduleData);
        else if(type == NNKt)
            str += paramFlashNNKt(moduleData);
        else if(type == GGP)
            str += paramFlashGGP(moduleData);
        return str += "<tr><td colspan = '2' align='center'> CalibFlash: </td></tr><tr><td colspan = '2'>" + dS->calibFlash.toHex() + "</td></tr>";
    }
    else{
        if(type == GKT)
            return channelGKT(moduleData);
        else if(type == SHM)
            return channelSHM(moduleData);
        else if(type == AG)
            return channelAG(moduleData);
        else if(type == MP)
            return channelP(moduleData);
        else if(type == P04)
            return channelP04(moduleData);
        else if(type == P02)
            return channelP02(moduleData);
        else if(type == GVK)
            return channelGVK(moduleData);
        else if(type == NNKt)
            return channel2NNKt(moduleData);
        else if(type == GGP)
            return channelGGP(moduleData);
    }
    return "...";
}

Tab38k::Tab38k(QList<PacketModulesData38k> *modulesData,QWidget *parent) : AbstractTab(parent){
    this->model = new Model38k(modulesData);
    this->prModel = new QSortFilterProxyModel();
    table = new QTableView();
    textEdit = new QTextEdit();
    horBoxLayout = new QHBoxLayout();
    this->tableAndFilterLayout = new QVBoxLayout();
    textEdit->setFont(QFont("arial",16));
    table->setModel(model);
    sp = new QSplitter(Qt::Horizontal);
    tableAndFilterWidget = new QWidget();
    filter = new QWidget();
    filtration = new QLabel("Filter:");
    column = new QLabel("column:");
    filterLineEdit = new QLineEdit();
    filterColumnSB = new QSpinBox();
    sortingLabel = new QLabel("sorting:");
    sortingCheckBox = new QCheckBox();
    filterColumnSB->setMaximum(11);
    filterColumnSB->setMinimum(-1);
    filterLayout = new QHBoxLayout();
    filterLayout->addWidget(filtration);
    filterLayout->addWidget(filterLineEdit);
    filterLayout->addWidget(column);
    filterLayout->addWidget(filterColumnSB);
    filterLayout->addWidget(sortingLabel);
    filterLayout->addWidget(sortingCheckBox);
    filter->setLayout(filterLayout);
    tableAndFilterWidget->setLayout(tableAndFilterLayout);
    this->tableAndFilterLayout->addWidget(filter);
    this->tableAndFilterLayout->addWidget(table);
    sp->addWidget(tableAndFilterWidget);
    sp->addWidget(textEdit);
    horBoxLayout->addWidget(sp);
    this->setLayout(horBoxLayout);
    QObject::connect(this->table, SIGNAL(activated(QModelIndex const&)),this, SLOT(showText(QModelIndex const&)));
    QObject::connect(this->filterLineEdit, SIGNAL(returnPressed()),this, SLOT(setFilter()));
    QObject::connect(this->sortingCheckBox, SIGNAL(stateChanged(int)),this, SLOT(setSorting(int)));
    this->table->hideColumn(11);
}
void Tab38k::saveCSV(){
    this->model->saveFile();
}


void Tab38k::showText(QModelIndex const& index){
    int row =this->table->model()->headerData(index.row(),Qt::Vertical).toInt();
    this->textEdit->setText(dataString(this->model->getData()->at(row)));
}

void Tab38k::setFilter(){
    delete prModel;
    prModel = new QSortFilterProxyModel();
    int column = this->filterColumnSB->text().toInt();
    prModel->setFilterKeyColumn(column);
    QString filter = this->filterLineEdit->text();
    prModel->setFilterRegExp(QRegExp(filter,Qt::CaseInsensitive));
    prModel->setSourceModel(model);
    this->table->setModel(prModel);
}
void Tab38k::setSorting(int value){
       table->setSortingEnabled(value);
       if(!value)
           prModel->sort(-1);
}
void Tab38k::addModulesData(PacketModulesData38k pack){
    this->model->setData(pack);
}
void Tab38k::allUploaded(){
    model->startParsingMdules();
}
Tab38k::~Tab38k(){
    delete table;
    table = nullptr;
    delete model;
    model = nullptr;
    delete prModel;
    prModel = nullptr;
    delete table;
    delete textEdit;
    delete horBoxLayout;
    delete filtration;
    delete column;
    delete filterLineEdit;
    delete filterColumnSB;
    delete sortingLabel;
    delete sortingCheckBox;
    delete filter;
    delete tableAndFilterWidget;
    delete sp;
}
