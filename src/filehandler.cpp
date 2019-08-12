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
        ParserTLM *parserTlm = new ParserTLM(file->getHexString());
        delete file;
        file = nullptr;
        Parser38k *deviceData = new Parser38k(parserTlm->getBlocks());
        connect(deviceData, SIGNAL(getModData38k(PacketModulesData38k)), tab, SLOT(addModulesData(PacketModulesData38k)));
        deviceData->start();
        //if(deviceData->getProbabilityOfError() > 20){
         //   return nullptr;
        //}
        delete parserTlm;
        parserTlm = nullptr;
        return tab;
    }
}
