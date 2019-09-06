#include "inc/parsers/parser38k.h"
#include <QTextCodec>
#include <QTime>

void channelGKT(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGKT();
    DataGKT *dS = reinterpret_cast<DataGKT*>(moduleData->dataStruct);
    memcpy(&dS->temperature_internal,data.data(),20);
    dS->type = GKT;
    dS->temperature_external = *reinterpret_cast<uint*>(data.mid(20,3).data());
    dS->sti_1 = *reinterpret_cast<uint*>(data.mid(23,3).data());
    dS->sti_2 = *reinterpret_cast<uint*>(data.mid(26,3).data());
    dS->p_corr = *reinterpret_cast<uint*>(data.mid(29,3).data());
    dS->p_bw = *reinterpret_cast<uint*>(data.mid(32,3).data());
    dS->acceleration_x = *reinterpret_cast<uint*>(data.mid(35,3).data());
    dS->acceleration_y = *reinterpret_cast<uint*>(data.mid(38,3).data());
    dS->acceleration_z = *reinterpret_cast<uint*>(data.mid(41,3).data());
    dS->locator_amp24 = *reinterpret_cast<uint*>(data.mid(44,3).data());
    dS->resistance = *reinterpret_cast<uint*>(data.mid(47,3).data());
    memcpy(&dS->sti_pwm,data.data() + 50,12);
}

void Parser38kModules::channelSHM(PacketModulesData38k * moduleData){
    int size = moduleData->dataBytes.size();
    QByteArray *data = &moduleData->dataBytes;
    if(!moduleData->header.currentPartNo){
        moduleData->dataStruct = new DataSHM0();
        DataSHM0 *dS = reinterpret_cast<DataSHM0*>(moduleData->dataStruct);
        dS->type = SHM;
        memcpy(&dS->periph_status,data->data(),20);
        isWave = dS->work_mode&0x0001;
        if(!isWave){
            dS->Wave_1int = nullptr;
            dS->Wave_1float = new QVector<float>();
            for(int i = 20; i < size - 4;i+=4){
                dS->Wave_1float->push_back(*reinterpret_cast<float*>(data->mid(i,4).data()));
            }
        }
        else{
            dS->Wave_1int = new QVector<short>();
            dS->Wave_1float = nullptr;
            for(int i = 20; i < size - 2;i += 2){
                dS->Wave_1int->push_back(*reinterpret_cast<short*>(data->data()+i));
            }
       }
    }
    else{
        moduleData->dataStruct = new DataSHM1();
        DataSHM1 *dS = reinterpret_cast<DataSHM1*>(moduleData->dataStruct);
        dS->type = SHM;
        if(!isWave){
            dS->Wave_1int = nullptr;
            dS->Wave_1float = new QVector<float>();
            for(int i = 0; i < size - 4;i+=4){
                dS->Wave_1float->push_back(*reinterpret_cast<float*>(data->mid(i,4).data()));
            }
        }
        else{
            dS->Wave_1int = new QVector<short>();
            dS->Wave_1float = nullptr;
            for(int i = 0; i < size - 2;i += 2){
                dS->Wave_1int->push_back(*reinterpret_cast<short*>(data->data()+i));
            }
        }
    }
}

void channelAG(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataAG();
    DataAG *dS = reinterpret_cast<DataAG*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),8);
    dS->type = AG;
}
void channelP(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP();
    DataP *dS = reinterpret_cast<DataP*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),10);
    dS->type = MP;
}

void channelP02(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP02();
    DataP02 *dS = reinterpret_cast<DataP02*>(moduleData->dataStruct);
    memcpy(&dS->rate,data.data(),8);
    dS->type = P02;
}

void channelP04(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataP04();
    DataP04 *dS = reinterpret_cast<DataP04*>(moduleData->dataStruct);
    memcpy(&dS->rate,data.data(),3);
    dS->type = P04;
}

void channel2NNKt(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new Data2NNKT();
    Data2NNKT *dS = reinterpret_cast<Data2NNKT*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),21);
    dS->type = NNKt;
}
void channelGGP(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGGP();
    DataGGP *dS = reinterpret_cast<DataGGP*>(moduleData->dataStruct);
    memcpy(&dS->periph_status,data.data(),15);
    dS->type = GGP;
}
void channelGVK(PacketModulesData38k * moduleData){
    QByteArray &data = moduleData->dataBytes;
    moduleData->dataStruct = new DataGVK();
    DataGVK *dS = reinterpret_cast<DataGVK*>(moduleData->dataStruct);
    memcpy(&dS->temperature_internal,data.data(),48);
    dS->type = GVK;
}
void Parser38kModules::moduleDataParsing(PacketModulesData38k * moduleData){
    moduleData->dataStruct = nullptr;
    QString * data = &moduleData->data;
    if(moduleData->header.data_state & 0x02){
        moduleData->dataStruct = new Flash();
        Flash *dS = reinterpret_cast<Flash*>(moduleData->dataStruct);
        HardFlash *hF = &dS->hardFlash;
        bool moduleAdded = false;
        ushort deviceType = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+2);
        ushort length = *reinterpret_cast<ushort*>(moduleData->dataBytes.data());
        if(listOfFoundModules->size() != 0)
            for(auto value = listOfFoundModules->begin();value < listOfFoundModules->end();value++)
                if(value->moduleAddress == moduleData->header.moduleAddress){
                    moduleAdded = true;
                    break;
                }
        if(!moduleAdded){
            NumberType module = {moduleData->header.moduleAddress,deviceType};
            listOfFoundModules->push_back(module);
        }
        hF->total_length = length;hF->device_tipe = deviceType;
        hF->device_number = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(4,12).data());
        hF->production_day = *reinterpret_cast<uchar*>(moduleData->dataBytes.data()+16);
        hF->production_month = *reinterpret_cast<uchar*>(moduleData->dataBytes.data()+17);
        hF->production_year = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+18);
        hF->device_name = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(20,16).data());
        hF->device_code = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(36,6).data());
        hF->device_decimal = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(42,6).data());
        hF->flash_version = QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+48)) + "." + QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+49));
        hF->firmware_version = QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+50)) + "." + QString::number(*reinterpret_cast<uchar*>(moduleData->dataBytes.data()+51));
        hF->reserved = 0;
        hF->device_tag = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(56,20).data());
        hF->device_length = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+76);
        hF->device_tech_header_size = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+78);
        hF->device_data_size = *reinterpret_cast<uint*>(moduleData->dataBytes.data()+80);
        hF->data_parts_max = *reinterpret_cast<uchar*>(moduleData->dataBytes.data()+84);
        int numberOfChannels = (length-86)/8;
        for(int i = 0; i <  numberOfChannels;i++){
            ChannelInformation channel;
            channel.channel_mnemonics = QTextCodec::codecForMib(106)->toUnicode(moduleData->dataBytes.mid(85+(i*8),4).data());
            channel.channel_write_point = *reinterpret_cast<short*>(moduleData->dataBytes.data()+89+(i*8));
            channel.channel_flags = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+91+(i*8));
            hF->channel.push_back(channel);
        }
        hF->crc16 = *reinterpret_cast<ushort*>(moduleData->dataBytes.mid(85+(numberOfChannels*8),2).data());
        length = *reinterpret_cast<ushort*>(moduleData->dataBytes.data()+87+(numberOfChannels * 8));
        QByteArray paramFlashArray = moduleData->dataBytes.mid(87 +(numberOfChannels * 8),length);
        dS->type = deviceType;
        if(deviceType == GKT){
            dS->paramFlash = new ParamFlashGKT;
            ParamFlashGKT *pF = reinterpret_cast<ParamFlashGKT*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
            pF->total_length = pF->total_length;
        }
        else if(deviceType == SHM){
            dS->paramFlash = new ParamFlashSHM;
            ParamFlashSHM *pF = reinterpret_cast<ParamFlashSHM*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == AG){
            dS->paramFlash = new ParamFlashAG;
            ParamFlashAG *pF = reinterpret_cast<ParamFlashAG*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == MP){
            dS->paramFlash = new ParamFlashP;
            ParamFlashP *pF = reinterpret_cast<ParamFlashP*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == P02 || deviceType == P04){
            dS->paramFlash = new ParamFlashP02P04;
            ParamFlashP02P04 *pF = reinterpret_cast<ParamFlashP02P04*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == GVK){
            dS->paramFlash = new ParamFlashGVK;
            ParamFlashGVK *pF = reinterpret_cast<ParamFlashGVK*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == GVK){
            dS->paramFlash = new ParamFlashNNKt;
            ParamFlashNNKt *pF = reinterpret_cast<ParamFlashNNKt*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }
        else if(deviceType == GVK){
            dS->paramFlash = new ParamFlashGGP;
            ParamFlashGGP *pF = reinterpret_cast<ParamFlashGGP*>(dS->paramFlash);
            memcpy(&pF->total_length,paramFlashArray.data(),sizeof(*pF));
        }

        dS->calibFlash = moduleData->dataBytes.mid(87 +(numberOfChannels * 8) + (length));
    }
    else if(!(moduleData->header.data_state & 0x01) & !moduleData->dataBytes.isEmpty()){
        uint type = 124;
        if(listOfFoundModules->size() != 0)
            for(auto value = listOfFoundModules->begin();value < listOfFoundModules->end();value++)
                if(value->moduleAddress == moduleData->header.moduleAddress){
                    type = value->type;
                    break;
                }
        if(type == GKT)
           channelGKT(moduleData);
        else if(type == SHM)
           channelSHM(moduleData);
        else if(type == AG)
           channelAG(moduleData);
        else if(type == MP)
           channelP(moduleData);
        else if(type == P04)
           channelP04(moduleData);
        else if(type == P02)
           channelP02(moduleData);
        else if(type == GVK)
           channelGVK(moduleData);
        else if(type == NNKt)
           channel2NNKt(moduleData);
        else if(type == GGP)
           channelGGP(moduleData);
    }
}
Parser38kModules::Parser38kModules(QList<PacketModulesData38k> *modulesData){
    this->modulesData = modulesData;
    this->listOfFoundModules = new QList<NumberType>;
    enabled = true;
    connect(this, SIGNAL(finished(void)), this, SLOT(del()));
}
void Parser38kModules::run(){
    QTime time =  QTime::currentTime();
    for(auto value = modulesData->begin();value < modulesData->end(); value++)
        if(enabled)
            moduleDataParsing(&*value);
        else
           return;
    qDebug() <<   time.msecsTo(QTime::currentTime());
}
void Parser38kModules::stop(){
    enabled = false;
}
void Parser38kModules::del(){
    this->~Parser38kModules();
}
Parser38kModules::~Parser38kModules(){
    if(this->listOfFoundModules)
        delete this->listOfFoundModules;
    this->listOfFoundModules = nullptr;
}


void Parser38k::findModulesDataBytes(PacketDeviceData38k pack){
    QByteArray moduleDataByteArray;
    int position = 0;
        dataBytes += pack.data.dataByte.mid(0);
        int size = dataBytes.size();
        while(position < size){
            PacketModulesData38k moduleData;
            moduleData.header.moduleAddress = *reinterpret_cast<unsigned char*>(dataBytes.data()+position);
            moduleData.header.data_state = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+1);
            moduleData.header.totalSize = *reinterpret_cast<unsigned short*>((dataBytes.data()+position+2));
            if(moduleData.header.totalSize > size - position || moduleData.header.totalSize < 12)
                break;
            moduleDataByteArray = dataBytes.mid(position,moduleData.header.totalSize);
            moduleData.status =  crc.crcFast(reinterpret_cast<uchar*>(moduleDataByteArray.data()),moduleData.header.totalSize)?0x80:0;
            int posLastComSt = 0;
            if(moduleData.header.data_state & 0x80){
                moduleData.header.totalDataSize = moduleData.header.totalSize - 14;
                moduleData.header.totalParts = 1;
                moduleData.header.currentPartNo = 0;
                moduleData.dataBytes = moduleDataByteArray.mid(12,moduleData.header.totalSize - 14);
            }
            else{
                moduleData.header.totalDataSize = *reinterpret_cast<unsigned short*>((dataBytes.data()+position+4));
                moduleData.header.totalParts = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+6);
                moduleData.header.currentPartNo = *reinterpret_cast<unsigned char*>(dataBytes.data()+position+7);
                posLastComSt = 4;
                moduleData.dataBytes = moduleDataByteArray.mid(16,moduleData.header.totalSize - 14);
            }
            int pos = position + posLastComSt + 4;
            moduleData.header.lastCommandState = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos);
            moduleData.header.commandCounter = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+1);
            moduleData.header.lastCommandCrc = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+2);
            moduleData.header.lastCommandCode = *reinterpret_cast<unsigned char*>(dataBytes.data()+pos+3);
            moduleData.header.requestTime = *reinterpret_cast<uint*>(dataBytes.data()+pos+4);

            //moduleDataParsing(&moduleData);
            moduleData.dataStruct = nullptr;
            emit  getModData38k(moduleData);
            position += moduleDataByteArray.size();
        }
        dataBytes = dataBytes.mid(position);
        position = 0;
        if(dataBytes.toHex() == "00")
            dataBytes.resize(0);
}
void Parser38k::findServiseFFFEBytes(TlmPack pack){
    unsigned char array[255];
        QByteArray data = pack.dataPacketBytes.data.mid(2);
        QByteArray bl255;
        QByteArray byteArray;
        PacketDeviceData38k packetDeviceData;
        packetDeviceData.data.status = 0;
        for(int position = 0; position < data.length();position+=255 ){
           // memset(array,0,255);
            bl255 = data.mid(position,255);
            //memcpy(array,bl255.data(),bl255.size());
            //int decod = cod.decode_rs_nasa(array);
            //this->numberOfChecks++;
            //this->numberOfError += decod?1:0;
            //packetDeviceData.data.status |= decod;
            packetDeviceData.data.dataByte += bl255.mid(33);
        }

        QByteArray serv = packetDeviceData.data.dataByte.mid(0,12);
        memset(array,0,255);
        memcpy(array,serv.data(),12);
        this->numberOfChecks++;
        int crcF = crc.crcFast(array,12);
        if(crcF)
            this->numberOfError++;
        if((packetDeviceData.data.status == 2 && crcF) || serv.size() == 0){
            return;
        }
        packetDeviceData.data.dataByte = packetDeviceData.data.dataByte.mid(12);
        packetDeviceData.serv.systemTime = *reinterpret_cast<uint*>(serv.data());
        packetDeviceData.serv.transmissionCounter = *reinterpret_cast<unsigned short*>(serv.data()+4);
        packetDeviceData.serv.totalModules = *reinterpret_cast<unsigned char*>(serv.data()+6);
        packetDeviceData.serv.speedTelemetry = (*reinterpret_cast<unsigned char*>(serv.data()+7) << 4) & 0x0f;
        packetDeviceData.serv.bitDepthTelemetry = *reinterpret_cast<unsigned char*>(serv.data()+7) >> 4;
        packetDeviceData.serv.commandCounter = *reinterpret_cast<unsigned char*>(serv.data()+8);
        packetDeviceData.serv.reserved = *reinterpret_cast<unsigned char*>(serv.data()+9);
        packetDeviceData.serv.crc16 = *reinterpret_cast<unsigned short*>(serv.data()+10);
        findModulesDataBytes(packetDeviceData);
}
Parser38k::Parser38k(FileReader *file){
    this->tlmDeviceData = new QList<TlmPack>;
    this->byteArrayData = file->getByteArray();
    delete file;
    file = nullptr;
    connect(this, SIGNAL(finished()), this, SLOT(destroy()));
}

void Parser38k::run(){
    numberOfChecks = 0;
    numberOfError = 0;
    QTime time = QTime::currentTime();
    ParserTLM *parserTlm = new ParserTLM(this->byteArrayData);
    QList<BlockTlm> *tlmBlocks = parserTlm->getBlocks();
    for(auto block = tlmBlocks->begin();block < tlmBlocks->end();block++)
        for(auto pack = block->TlmPackList.begin();pack < block->TlmPackList.end();pack++)
            if(pack->dataPacketBytes.dev_type == "ADSP" && pack->dataPacketBytes.inf_type == "GETDATA"){
                findServiseFFFEBytes(*pack);
            }

    delete parserTlm;
    parserTlm = nullptr;
    double sr;
    if(numberOfError != 0 & numberOfChecks != 0)
        sr = numberOfError/(numberOfChecks/100);
    else
        sr = 100;

    this->probabilityOfError = sr;
}

void Parser38k::destroy(){
   this->~Parser38k();
}

Parser38k::~Parser38k(){
    delete this->tlmDeviceData;
    this->tlmDeviceData = nullptr;
    this->quit();
}
