#include "inc/parsers/parserDeviceDataTlm.h"

ParserDeviceDataTlm::ParserDeviceDataTlm(QList<BlockTlm> *tlmBlocks){
    this->tlmDeviceData = new QList<TlmPack>;
    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPucket.dev_type == "ADSP" && pack->dataPucket.inf_type == "GETDATA")
                this->tlmDeviceData->push_back(*pack);

    for (auto pack = this->tlmDeviceData->begin();pack < tlmDeviceData->end();pack++){
        QString serv = pack->dataPucket.data.mid(0,60);
        QByteArray byteArray = QByteArray::fromHex(serv.toLocal8Bit());
        unsigned char* array = new unsigned char[255];
        for(int i = 0; i < 255;i++){
            if(i+2 >= byteArray.length())
                array[i] = 0;
            else
                array[i] = byteArray.data()[i+2];
        }
        int code = cod.decode_rs_short(array);
        for(int i = 0; i < byteArray.length();i++){
             byteArray.data()[i] = array[i];
        }

        serv = byteArray.toHex();
        qDebug() << code <<"  " <<serv<< endl;
    }
}
