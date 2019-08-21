#include "inc/parsers/parserDataCm.h"
#include "string.h"


void ParserDataCm::findServiseFFFE(){
    bool ok;
    unsigned char array[255];
    for (auto pack = this->tlmDeviceData->begin();pack < tlmDeviceData->end();pack++){
        QString serv = pack->dataPacket.data.mid(0,60);
        QString data = pack->dataPacket.data.mid(60);
        QByteArray byteArray = QByteArray::fromHex(serv.toLocal8Bit());
        memset(array,0,255);
        memcpy(array,byteArray.toStdString().c_str() + 2,static_cast<size_t>(byteArray.size() - 2));

        PacketDeviceData packetDeviceData;
        packetDeviceData.serv.status =  cod.decode_rs_short(array)|(crc.crcFast(array+6,22)?0x80:0);
        serv = QByteArray::fromRawData(reinterpret_cast<const char *>(array),30).toHex();
        packetDeviceData.serv.length = (serv.mid(18,2) + serv.mid(16,2)).toUInt(&ok,16);
        packetDeviceData.serv.segmentNum = static_cast<unsigned char>(serv.mid(16,2).toUInt(&ok,16));
        packetDeviceData.serv.segmentCurr = static_cast<unsigned char>(serv.mid(18,2).toUInt(&ok,16));
        packetDeviceData.serv.counter = static_cast<unsigned char>(serv.mid(20,2).toUInt(&ok,16));
        packetDeviceData.serv.numModules = static_cast<unsigned char>(serv.mid(22,2).toUInt(&ok,16));
        packetDeviceData.serv.sysTime = (serv.mid(30,2) + serv.mid(28,2)+serv.mid(26,2) + serv.mid(24,2)).toUInt(&ok,16);
        packetDeviceData.serv.report = static_cast<unsigned char>(serv.mid(32,2).toUInt(&ok,16));
        packetDeviceData.serv.tlmSpeed = static_cast<unsigned char>(serv.mid(34,2).toUInt(&ok,16));
        packetDeviceData.serv.cmdCrc = static_cast<unsigned short>((serv.mid(38,2) + serv.mid(36,2)).toUInt(&ok,16));
        packetDeviceData.serv.reserved0 = static_cast<unsigned short>((serv.mid(42,2) + serv.mid(40,2)).toUInt(&ok,16));
        packetDeviceData.serv.nCmd = static_cast<unsigned char>(serv.mid(44,2).toUInt(&ok,16));
        packetDeviceData.serv.reply = static_cast<unsigned char>(serv.mid(46,2).toUInt(&ok,16));
        packetDeviceData.serv.rsDeepness = static_cast<unsigned char>(serv.mid(48,2).toUInt(&ok,16));
        packetDeviceData.serv.reserved1 = static_cast<unsigned char>(serv.mid(50,2).toUInt(&ok,16));
        packetDeviceData.serv.crc16 = static_cast<unsigned short>((serv.mid(54,2) + serv.mid(52,2)).toUInt(&ok,16));
        packetDeviceData.data.status = 0;
        QString bl255 = "";
        for(int position = 0; position < data.length();position+=510 ){
            bl255 = data.mid(position,510);
            byteArray = QByteArray::fromHex(bl255.toLocal8Bit());
            memset(array,0,255);
            memcpy(array,byteArray.toStdString().c_str(),byteArray.size());
            packetDeviceData.data.status = cod.decode_rs_nasa(array);
            packetDeviceData.data.data += bl255.mid(64);
        }
        this->deviceData->push_back(packetDeviceData);
    }
}


ParserDataCm::ParserDataCm(QList<BlockTlm> *tlmBlocks){
    this->tlmDeviceData = new QList<TlmPack>;
    this->deviceData = new QList<PacketDeviceData>;

    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPacket.dev_type == "ADSP" && pack->dataPacket.inf_type == "GETDATA")
                this->tlmDeviceData->push_back(*pack);

    findServiseFFFE();
}
