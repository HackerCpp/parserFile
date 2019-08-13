#include "inc/filehandler.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include "inc/parsers/parserDataCm.h"
#include "inc/parsers/parser38k.h"
#include "inc/tabs/tab38k.h"
#include <QSplitter>




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
    return nullptr;
}
