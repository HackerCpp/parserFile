#include "inc/parsers/parserDeviceDataTlm.h"

void ParserDeviceDataTlm::findServiseFFFE(){
    bool ok;
    unsigned char* array = new unsigned char[255];
    for (auto pack = this->tlmDeviceData->begin();pack < tlmDeviceData->end();pack++){
        QString serv = pack->dataPucket.data.mid(0,60);
        QString data = pack->dataPucket.data.mid(60);
        QByteArray byteArray = QByteArray::fromHex(serv.toLocal8Bit());
        for(int i = 0; i < 255;i++){
            if(i+2 >= byteArray.length())
                array[i] = 0;
            else
                array[i] = static_cast<unsigned char>(byteArray.data()[i+2]);
        }
        PacketDeviceData packetDeviceData;
        unsigned short c = crc.crcFast(array+6,22);
        packetDeviceData.serv.status =  cod.decode_rs_short(array)|c?0x80:0;
        serv = byteArray.toHex();
        packetDeviceData.serv.length = (serv.mid(18,2) + serv.mid(16,2)).toUInt(&ok,16);
        packetDeviceData.serv.segmentNum = static_cast<unsigned char>(serv.mid(20,2).toUInt(&ok,16));
        packetDeviceData.serv.segmentCurr = static_cast<unsigned char>(serv.mid(22,2).toUInt(&ok,16));
        packetDeviceData.serv.counter = static_cast<unsigned char>(serv.mid(24,2).toUInt(&ok,16));
        packetDeviceData.serv.numModules = static_cast<unsigned char>(serv.mid(26,2).toUInt(&ok,16));
        packetDeviceData.serv.sysTime = (serv.mid(34,2) + serv.mid(32,2)+serv.mid(30,2) + serv.mid(28,2)).toUInt(&ok,16);
        packetDeviceData.serv.report = static_cast<unsigned char>(serv.mid(36,2).toUInt(&ok,16));
        packetDeviceData.serv.tlmSpeed = static_cast<unsigned char>(serv.mid(38,2).toUInt(&ok,16));
        packetDeviceData.serv.cmdCrc = static_cast<unsigned short>((serv.mid(42,2) + serv.mid(40,2)).toUInt(&ok,16));
        packetDeviceData.serv.reserved0 = static_cast<unsigned short>((serv.mid(46,2) + serv.mid(44,2)).toUInt(&ok,16));
        packetDeviceData.serv.nCmd = static_cast<unsigned char>(serv.mid(48,2).toUInt(&ok,16));
        packetDeviceData.serv.reply = static_cast<unsigned char>(serv.mid(50,2).toUInt(&ok,16));
        packetDeviceData.serv.rsDeepness = static_cast<unsigned char>(serv.mid(52,2).toUInt(&ok,16));
        packetDeviceData.serv.reserved1 = static_cast<unsigned char>(serv.mid(54,2).toUInt(&ok,16));
        packetDeviceData.serv.crc16 = static_cast<unsigned short>((serv.mid(58,2) + serv.mid(56,2)).toUInt(&ok,16));
        qDebug()<< packetDeviceData.serv.length <<" "<<
                 packetDeviceData.serv.segmentNum <<" "<<
                 packetDeviceData.serv.segmentCurr <<" "<<
                 packetDeviceData.serv.counter <<" "<<
                 packetDeviceData.serv.numModules <<" "<<
                 packetDeviceData.serv.sysTime <<" "<<
                 packetDeviceData.serv.report <<" "<<
                 packetDeviceData.serv.tlmSpeed <<" "<<
                 packetDeviceData.serv.cmdCrc <<" "<<
                 packetDeviceData.serv.reserved0 <<" "<<
                 packetDeviceData.serv.nCmd <<" "<<
                 packetDeviceData.serv.reply <<" "<<
                 packetDeviceData.serv.rsDeepness <<" "<<
                 packetDeviceData.serv.reserved1 <<" "<<
                 packetDeviceData.serv.crc16 << "  " << packetDeviceData.serv.status<<endl;

        packetDeviceData.data.status = 0;
        QString bl255 = "";
        for(int position = 0; position < data.length();position+=510 ){
            bl255 = data.mid(position,510);
            byteArray = QByteArray::fromHex(bl255.toLocal8Bit());
            for(int i = 0; i < 255;i++){
                if(i >= byteArray.length())
                    array[i] = 0;
                else
                    array[i] = static_cast<unsigned char>(byteArray.data()[i]);
            }
            packetDeviceData.data.status |= cod.decode_rs_nasa(array);
            packetDeviceData.data.data += bl255.mid(64);
        }
        this->deviceData->push_back(packetDeviceData);

    }
    /*for(auto dev = deviceData->begin();dev < deviceData->end();dev++){
        qDebug()<< dev->serv.length <<" "<<
                 dev->serv.segmentNum <<" "<<
                 dev->serv.segmentCurr <<" "<<
                 dev->serv.counter <<" "<<
                 dev->serv.numModules <<" "<<
                 dev->serv.sysTime <<" "<<
                 dev->serv.report <<" "<<
                 dev->serv.tlmSpeed <<" "<<
                 dev->serv.cmdCrc <<" "<<
                 dev->serv.reserved0 <<" "<<
                 dev->serv.nCmd <<" "<<
                 dev->serv.reply <<" "<<
                 dev->serv.rsDeepness <<" "<<
                 dev->serv.reserved1 <<" "<<
                 dev->serv.crc16 << endl;
    }*/
}


ParserDeviceDataTlm::ParserDeviceDataTlm(QList<BlockTlm> *tlmBlocks){
    this->tlmDeviceData = new QList<TlmPack>;
    this->deviceData = new QList<PacketDeviceData>;

    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPucket.dev_type == "ADSP" && pack->dataPucket.inf_type == "GETDATA")
                this->tlmDeviceData->push_back(*pack);

    findServiseFFFE();
}
