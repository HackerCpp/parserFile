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

            packetDeviceData.data.status |= cod.decode_rs_nasa(array);
            packetDeviceData.data.data += bl255.mid(66);
            //qDebug()<< bl255.mid(64,2);
        }
        //qDebug() << endl;

        QString serv = packetDeviceData.data.data.mid(0,24);
        byteArray = QByteArray::fromHex(serv.toLocal8Bit());
        memset(array,0,255);
        memcpy(array,byteArray.toStdString().c_str(),byteArray.size());
        //qDebug()<<crc.crcFast(array,12);
        if((packetDeviceData.data.status == 2 && crc.crcFast(array,12)) || serv.size() == 0)
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
        //qDebug() << packetDeviceData.serv.totalModules;

        this->deviceData->push_back(packetDeviceData);
    }
}


void Parser38k::findModulesData(){
    bool ok;
    QString data ="";
    QString moduleDataString;
    int position = 0;
    for (auto pack = this->deviceData->begin();pack < deviceData->end();pack++){
        data += pack->data.data.mid(0,pack->data.data.size() - 4);
        int size = data.size();
        while(true){
            PacketModulesData38k moduleData;
            moduleData.header.moduleAddress = static_cast<unsigned char>(data.mid(0,2).toUInt(&ok,16));
            moduleData.header.data_state = static_cast<unsigned char>(data.mid(2,2).toUInt(&ok,16));
            moduleData.header.totalSize = static_cast<unsigned short>((data.mid(6,2) + data.mid(4,2)).toUInt(&ok,16));
            if(moduleData.header.totalSize > size - position)
                break;
            moduleDataString = data.mid(position,moduleData.header.totalSize*2);
            position += moduleData.header.totalSize*2;
            qDebug()<< moduleData.header.moduleAddress<<"  "<<moduleData.header.data_state<<"  "<<moduleData.header.totalSize;
            if(moduleData.header.data_state & 0x80){
                moduleData.header.totalDataSize = 0;
                moduleData.header.totalParts = 1;
                moduleData.header.currentPartNo = 0;
            }
        }

        data.remove(0,position);
        position = 0;
        qDebug()<<endl<<data<<endl;
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
    findServiseFFFE();
    findModulesData();

}
