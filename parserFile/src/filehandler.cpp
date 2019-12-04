#include "inc/filehandler.h"
#include "inc/filereader.h"
#include "inc/parsers/parsergfm.h"
#include "inc/tabs/tab38k.h"
#include "inc/tabs/tabgfm.h"




FileHandler::FileHandler(QWidget *parent){
    qRegisterMetaType<PacketModulesData38k>("PacketModulesData38k");
}

QWidget *FileHandler::getWidget(QString path){
    FileReader *file = new FileReader(path);
    if(file->getType() == ".tlm"){
        Tab38k *tab = new Tab38k(nullptr);
        Parser38k *deviceData = new Parser38k(file);
        connect(deviceData, SIGNAL(getModData38k(PacketModulesData38k)), tab, SLOT(addModulesData(PacketModulesData38k)));
        connect(deviceData, SIGNAL(finished(void)), tab, SLOT(allUploaded(void)));
        deviceData->start();
        return tab;
    }
    else if(file->getType() == ".gfm"){
        TabGFM * tab = new TabGFM(path);
        return tab;
    }
    return nullptr;
}
