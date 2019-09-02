#include "inc/fileCreation/csv.h"
#include "QFileDialog"
#include "QTextDocumentWriter"
#include "QTextEdit"

CSV::CSV(QList<QString> header,QList<QList<QString>> data){

}

CSV::CSV(QList<PacketModulesData38k> *modulesData38k,ushort type){
    QString fileString;
    if(type == GKT)
        fileString = "temperature_internal,locator_amp16,locator_amp_interval_max,locator_amp_interval_min,gk_time,gk_impulses,gk_uhv,hygrometer,power_supply,emds_supply,temperature_external,\
        sti_1,sti_2,p_corr,p_bw,acceleration_x,acceleration_y,acceleration_z,locator_amp24,resistance,sti_pwm,pressure,temperature,gk_dac \n";
    else if(type == SHM)
        fileString = "";
    else if(type == AG)
        fileString = "periph_status,work_mode,temperature_internal,discharge_voltage \n";
    else if(type == MP)
        fileString ="periph_status, angle,rate,temperature_internal \n";
    else if(type == AMDS)
        fileString = "";
    else if(type == GKTSHM)
        fileString ="";
    else if(type == P04)
        fileString ="rate,temperature_internal \n";
    else if(type == P02)
        fileString ="rate, diameter,temperature_internal \n";
    else if(type == GVK)
        fileString ="temperature_internal,locator_amp16,locator_amp_interval_max,locator_amp_interval_min, \
        gk_time,gk_impulses,gk_uhv,power_supply,temperature_external,temperature_external2,temperature_external3, \
        p_corr,p_bw,acceleration_x,acceleration_y,acceleration_z,locator_amp24,temperature_external4,gk_dac \n";
    else if(type == NNKt)
        fileString ="periph_status,count_time,near_count,far_count,gk_uhv,gk_dac,temperature_internal, \
        comp_edac1_value,comp_edac2_value \n";
    else if(type == GGP)
        fileString ="periph_status,count_time,count,gk_uhv,gk_dac,temperature_internal,comp_edac_value \n";
    foreach(PacketModulesData38k data,*modulesData38k){
        if(data.dataStruct->type == type){
            if(type == GKT){
                DataGKT * dataGKT = reinterpret_cast<DataGKT*>(data.dataStruct);
                fileString += QString::number(dataGKT->temperature_internal)+","+QString::number(dataGKT->locator_amp16)+","+
                        QString::number(dataGKT->locator_amp_interval_max)+","+QString::number(dataGKT->locator_amp_interval_min)+","+
                        QString::number(dataGKT->gk_time)+","+QString::number(dataGKT->gk_impulses)+","+
                        QString::number(dataGKT->gk_uhv)+","+QString::number(dataGKT->hygrometer)+","+
                        QString::number(dataGKT->power_supply)+","+QString::number(dataGKT->emds_supply)+","+
                        QString::number(dataGKT->temperature_external)+","+QString::number(dataGKT->sti_1)+","+
                        QString::number(dataGKT->sti_2)+","+QString::number(dataGKT->p_corr)+","+
                        QString::number(dataGKT->p_bw)+","+QString::number(dataGKT->acceleration_x)+","+
                        QString::number(dataGKT->acceleration_y)+","+QString::number(dataGKT->acceleration_z)+","+
                        QString::number(dataGKT->locator_amp24)+","+QString::number(dataGKT->resistance)+","+
                        QString::number(dataGKT->sti_pwm)+","+QString::number(dataGKT->pressure)+","+
                        QString::number(dataGKT->temperature)+","+QString::number(dataGKT->gk_dac) + "\n";
            }
            else if(type == SHM){
                DataSHM0 * dataSHM0 = reinterpret_cast<DataSHM0*>(data.dataStruct);
                if(dataSHM0->Wave_1int){
                    foreach(int data,dataSHM0->Wave_1int)
                        fileString+= QString::number(data) + ",";
                    fileString += "\n";
                }
                else if(dataSHM0->Wave_1float){
                    foreach(float data,dataSHM0->Wave_1float)
                        fileString+= QString::number(data) + ",";
                    fileString += "\n";
                }
            }
            else if(type == 100){
                DataSHM1 * dataSHM1 = reinterpret_cast<DataSHM1*>(data.dataStruct);
                if(dataSHM1->Wave_1int){
                    foreach(int data,dataSHM1->Wave_1int)
                        fileString+= QString::number(data) + ",";
                    fileString += "\n";
                }
                else if(dataSHM1->Wave_1float){
                    foreach(float data,dataSHM1->Wave_1float)
                        fileString+= QString::number(data) + ",";
                    fileString += "\n";
                }
            }
            else if(type == AG){
                DataAG * dataAG = reinterpret_cast<DataAG*>(data.dataStruct);
                fileString += QString::number(dataAG->periph_status) + "," + QString::number(dataAG->work_mode) + "," + QString::number(dataAG->temperature_internal) +
                "," + QString::number(dataAG->discharge_voltage) + "\n";
            }
            else if(type == MP){
                DataP * dataP = reinterpret_cast<DataP*>(data.dataStruct);
                fileString += QString::number(dataP->periph_status) + "," + QString::number(dataP->angle) + "," + QString::number(dataP->rate) +
                "," + QString::number(dataP->temperature_internal) + "\n";
            }
            else if(type == P04){
                DataP04 * dataP04 = reinterpret_cast<DataP04*>(data.dataStruct);
                fileString += QString::number(dataP04->rate) + ","  + QString::number(dataP04->temperature_internal) + "\n";
            }
            else if(type == P02){
                DataP02 * dataP02 = reinterpret_cast<DataP02*>(data.dataStruct);
                fileString += QString::number(dataP02->rate) + ","  + QString::number(dataP02->diameter) + ","  + QString::number(dataP02->temperature_internal) + "\n";
            }
            else if(type == GVK){
                DataGVK * dataGVK = reinterpret_cast<DataGVK*>(data.dataStruct);
                fileString += QString::number(dataGVK->temperature_internal)+","+QString::number(dataGVK->locator_amp16)+","+
                QString::number(dataGVK->locator_amp_interval_max)+","+QString::number(dataGVK->locator_amp_interval_min)+","+
                QString::number(dataGVK->gk_time)+","+QString::number(dataGVK->gk_impulses)+","+
                QString::number(dataGVK->gk_uhv)+","+QString::number(dataGVK->power_supply)+","+
                QString::number(dataGVK->temperature_external)+","+QString::number(dataGVK->temperature_external2)+","+
                QString::number(dataGVK->temperature_external3)+","+
                QString::number(dataGVK->p_corr)+","+QString::number(dataGVK->p_bw)+","+QString::number(dataGVK->acceleration_x)+","+
                QString::number(dataGVK->acceleration_y)+","+QString::number(dataGVK->acceleration_z)+","+QString::number(dataGVK->locator_amp24)+","+
                QString::number(dataGVK->temperature_external4)+","+QString::number(dataGVK->gk_dac) + "\n";
            }
            else if(type == NNKt){
                Data2NNKT * data2NNKT = reinterpret_cast<Data2NNKT*>(data.dataStruct);
                fileString += QString::number(data2NNKT->periph_status)+","+ QString::number(data2NNKT->count_time)+","+
                QString::number(data2NNKT->near_count)+","+ QString::number(data2NNKT->far_count)+","+ QString::number(data2NNKT->gk_uhv)+","+
                QString::number(data2NNKT->gk_dac)+","+ QString::number(data2NNKT->temperature_internal)+","+
                QString::number(data2NNKT->comp_edac1_value)+","+ QString::number(data2NNKT->comp_edac2_value) + "\n";
            }
            else if(type == GGP){
                DataGGP * dataGGP = reinterpret_cast<DataGGP*>(data.dataStruct);
                fileString += QString::number(dataGGP->periph_status)+","+QString::number(dataGGP->count_time)+","+
                QString::number(dataGGP->count)+","+QString::number(dataGGP->gk_uhv)+","+QString::number(dataGGP->gk_dac)+","+
                QString::number(dataGGP->temperature_internal)+","+QString::number(dataGGP->comp_edac_value)+ "\n";
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
    QString docPath = filePath + ".csv";
    writer.setFileName(docPath);
    bool ok = writer.write(ptxt->document());
    delete ptxt;
}
