#include "inc/parsers/parser38k.h"

void Parser38k::findServiseFFFE(){
    bool ok;
    unsigned char array[255];
    for (auto pack = this->tlmDeviceData->begin();pack < tlmDeviceData->end();pack++){
        QString data = pack->dataPucket.data.mid(4);
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
            continue;

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

        this->deviceData->push_back(packetDeviceData);
    }
}


void Parser38k::findModulesData(){
    bool ok;
    QString data ="";
    QString moduleDataString;
    int position = 0;
    for (auto pack = this->deviceData->begin();pack < deviceData->end();pack++){
        data += pack->data.data.mid(0,pack->data.data.size());
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
            emit  getModData38k(moduleData);
            //this->modulesData->push_back(moduleData);
            position += moduleDataString.size();
        }
        data.remove(0,position);
        position = 0;
        if(data == "00")
            data ="";
    }
}

Parser38k::Parser38k(QList<BlockTlm> *tlmBlocks){
    this->tlmDeviceData = new QList<TlmPack>;
    this->deviceData = new QList<PacketDeviceData38k>;
    this->modulesData = new QList<PacketModulesData38k>;

    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPucket.dev_type == "ADSP" && pack->dataPucket.inf_type == "GETDATA")
                this->tlmDeviceData->push_back(*pack);
}
void Parser38k::run(){
    numberOfChecks = 0;
    numberOfError = 0;
    findServiseFFFE();
    //double sr = numberOfError/(numberOfChecks/100);
    //this->probabilityOfError = sr;
    //if(this->probabilityOfError > 20)
       // return;
    findModulesData();
}
Parser38k::~Parser38k(){
    delete this->tlmDeviceData;
    delete this->deviceData;
    delete this->modulesData;
}
