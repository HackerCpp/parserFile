#include "inc/fileCreation/csv.h"
#include "QFileDialog"
#include "QTextDocumentWriter"
#include "QTextEdit"

CSV::CSV(QList<QString> header,QList<QList<QString>> data){

}

CSV::CSV(QList<PacketModulesData38k> *modulesData38k,ushort type,QString separator){
    QString fileString = "time"+separator;
    if(type == GKT)
        fileString += "temperature_internal,locator_amp16,locator_amp_interval_max,locator_amp_interval_min,gk_time,gk_impulses,gk_uhv,hygrometer,power_supply,emds_supply,temperature_external,\
        sti_1,sti_2,p_corr,p_bw,acceleration_x,acceleration_y,acceleration_z,locator_amp24,resistance,sti_pwm,pressure,temperature,gk_dac \n";
    else if(type == SHM)
        fileString += "";
    else if(type == AG)
        fileString += "periph_status,work_mode,temperature_internal,discharge_voltage \n";
    else if(type == MP)
        fileString +="periph_status, angle,rate,temperature_internal \n";
    else if(type == AMDS)
        fileString += "";
    else if(type == GKTSHM)
        fileString +="";
    else if(type == P04)
        fileString +="rate,temperature_internal \n";
    else if(type == P02)
        fileString +="rate, diameter,temperature_internal \n";
    else if(type == GVK)
        fileString +="temperature_internal,locator_amp16,locator_amp_interval_max,locator_amp_interval_min, \
        gk_time,gk_impulses,gk_uhv,power_supply,temperature_external,temperature_external2,temperature_external3, \
        p_corr,p_bw,acceleration_x,acceleration_y,acceleration_z,locator_amp24,temperature_external4,gk_dac \n";
    else if(type == NNKt)
        fileString +="periph_status,count_time,near_count,far_count,gk_uhv,gk_dac,temperature_internal, \
        comp_edac1_value,comp_edac2_value \n";
    else if(type == GGP)
        fileString +="periph_status,count_time,count,gk_uhv,gk_dac,temperature_internal,comp_edac_value \n";
    fileString.replace(",",separator);
    foreach(PacketModulesData38k data,*modulesData38k){
        if(!data.dataStruct)
            continue;
        if(data.dataStruct->type == type){
            if(type == GKT){
                DataGKT * dataGKT = reinterpret_cast<DataGKT*>(data.dataStruct);
                fileString += QString::number(dataGKT->temperature_internal)+separator+QString::number(dataGKT->locator_amp16)+separator+
                        QString::number(dataGKT->locator_amp_interval_max)+separator+QString::number(dataGKT->locator_amp_interval_min)+separator+
                        QString::number(dataGKT->gk_time)+separator+QString::number(dataGKT->gk_impulses)+separator+
                        QString::number(dataGKT->gk_uhv)+separator+QString::number(dataGKT->hygrometer)+separator+
                        QString::number(dataGKT->power_supply)+separator+QString::number(dataGKT->emds_supply)+separator+
                        QString::number(dataGKT->temperature_external)+separator+QString::number(dataGKT->sti_1)+separator+
                        QString::number(dataGKT->sti_2)+separator+QString::number(dataGKT->p_corr)+separator+
                        QString::number(dataGKT->p_bw)+separator+QString::number(dataGKT->acceleration_x)+separator+
                        QString::number(dataGKT->acceleration_y)+separator+QString::number(dataGKT->acceleration_z)+separator+
                        QString::number(dataGKT->locator_amp24)+separator+QString::number(dataGKT->resistance)+separator+
                        QString::number(dataGKT->sti_pwm)+separator+QString::number(dataGKT->pressure)+separator+
                        QString::number(dataGKT->temperature)+separator+QString::number(dataGKT->gk_dac) + "\n";
            }
            else if(type == SHM){
                DataSHM1 * dataSHM1 = reinterpret_cast<DataSHM1*>(data.dataStruct);
                if(dataSHM1->Wave_1int){
                    foreach(int data,*dataSHM1->Wave_1int)
                        fileString+= QString::number(data) + separator;
                    fileString += "\n";
                }
                else if(dataSHM1->Wave_1float){
                    foreach(float data,*dataSHM1->Wave_1float)
                        fileString+= QString::number(data) + separator;
                    fileString += "\n";
                }
            }
            else if(type == AG){
                DataAG * dataAG = reinterpret_cast<DataAG*>(data.dataStruct);
                fileString += QString::number(dataAG->periph_status) + separator + QString::number(dataAG->work_mode) + separator + QString::number(dataAG->temperature_internal) +
                separator + QString::number(dataAG->discharge_voltage) + "\n";
            }
            else if(type == MP){
                DataP * dataP = reinterpret_cast<DataP*>(data.dataStruct);
                fileString += QString::number(dataP->periph_status) + separator + QString::number(dataP->angle) + separator + QString::number(dataP->rate) +
                separator + QString::number(dataP->temperature_internal) + "\n";
            }
            else if(type == P04){
                DataP04 * dataP04 = reinterpret_cast<DataP04*>(data.dataStruct);
                fileString += QString::number(dataP04->rate) + separator  + QString::number(dataP04->temperature_internal) + "\n";
            }
            else if(type == P02){
                DataP02 * dataP02 = reinterpret_cast<DataP02*>(data.dataStruct);
                fileString += QString::number(dataP02->rate) + separator  + QString::number(dataP02->diameter) + separator  + QString::number(dataP02->temperature_internal) + "\n";
            }
            else if(type == GVK){
                DataGVK * dataGVK = reinterpret_cast<DataGVK*>(data.dataStruct);
                fileString += QString::number(dataGVK->temperature_internal)+separator+QString::number(dataGVK->locator_amp16)+separator+
                QString::number(dataGVK->locator_amp_interval_max)+separator+QString::number(dataGVK->locator_amp_interval_min)+separator+
                QString::number(dataGVK->gk_time)+separator+QString::number(dataGVK->gk_impulses)+separator+
                QString::number(dataGVK->gk_uhv)+separator+QString::number(dataGVK->power_supply)+separator+
                QString::number(dataGVK->temperature_external)+separator+QString::number(dataGVK->temperature_external2)+separator+
                QString::number(dataGVK->temperature_external3)+separator+
                QString::number(dataGVK->p_corr)+separator+QString::number(dataGVK->p_bw)+separator+QString::number(dataGVK->acceleration_x)+separator+
                QString::number(dataGVK->acceleration_y)+separator+QString::number(dataGVK->acceleration_z)+separator+QString::number(dataGVK->locator_amp24)+separator+
                QString::number(dataGVK->temperature_external4)+separator+QString::number(dataGVK->gk_dac) + "\n";
            }
            else if(type == NNKt){
                Data2NNKT * data2NNKT = reinterpret_cast<Data2NNKT*>(data.dataStruct);
                fileString += QString::number(data2NNKT->periph_status)+separator+ QString::number(data2NNKT->count_time)+separator+
                QString::number(data2NNKT->near_count)+separator+ QString::number(data2NNKT->far_count)+separator+ QString::number(data2NNKT->gk_uhv)+separator+
                QString::number(data2NNKT->gk_dac)+separator+ QString::number(data2NNKT->temperature_internal)+separator+
                QString::number(data2NNKT->comp_edac1_value)+separator+ QString::number(data2NNKT->comp_edac2_value) + "\n";
            }
            else if(type == GGP){
                DataGGP * dataGGP = reinterpret_cast<DataGGP*>(data.dataStruct);
                fileString += QString::number(dataGGP->periph_status)+separator+QString::number(dataGGP->count_time)+separator+
                QString::number(dataGGP->count)+separator+QString::number(dataGGP->gk_uhv)+separator+QString::number(dataGGP->gk_dac)+separator+
                QString::number(dataGGP->temperature_internal)+separator+QString::number(dataGGP->comp_edac_value)+ "\n";
            }
        }
    }
    QFileDialog fileDialog;
    QTextEdit * ptxt = new QTextEdit();
    ptxt->setFontPointSize(6);
    ptxt->setFontFamily("Courier New");
    ptxt->setText(fileString);
    QString filePath = fileDialog.getSaveFileName(nullptr, "Save File","C:/","*.csv");
    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    QString docPath = filePath;
    writer.setFileName(docPath);
    bool ok = writer.write(ptxt->document());
    delete ptxt;
}
