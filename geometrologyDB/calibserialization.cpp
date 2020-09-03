#include "calibserialization.h"
#include "QDebug"
#include <QTextCodec>
#include <QFile>

ushort CalibrSerialization::ReadVers(QByteArray &CalibrData, int &n){
    n = 2;
    if(CalibrData.size() >= 2)
        return *reinterpret_cast<ushort *>(CalibrData.mid(0,2).data());
    return 0;
}

void CalibrSerialization::ReadString(QByteArray &CalibrData, int &n, QString &str){
    str = "";
    int f_length = 0;
    if(n + sizeof(f_length) > CalibrData.size())
        return;
    f_length = *reinterpret_cast<int *>(CalibrData.data() + n);
    n += sizeof(f_length);
    if(f_length < 0)
        return;
    str = QTextCodec::codecForName("UTF-16")->toUnicode(CalibrData.mid(n,f_length * 2));
    n += f_length * 2;
}

template<typename T>
void CalibrSerialization::ReadArray(QByteArray &CalibrData, int &n, QVector<T>& ar){
    int l = 0;
    if(n + (int)sizeof(l) > CalibrData.size())
        return;
    memcpy(&l, CalibrData.data() + n, sizeof(l));
    if(l < 0)
        return;
    n += sizeof(l);
    if(n + (int)(l*sizeof(T)) <= CalibrData.size() && l != 0){
        ar.resize(l);
        memcpy(ar.data(), CalibrData.data() + n, l * sizeof(T));
    }
    n += l * sizeof(T);
}

template<typename T>
void CalibrSerialization::Read(QByteArray &CalibrData, int &n, T &v){
    v = 0;
    if(n + (int)sizeof(v) <= CalibrData.size())
        memcpy(&v, CalibrData.data() + n, sizeof(v));
    n += sizeof(v);
}
void CalibrSerialization::dataClear(){
    m_dataCalib.version;
    m_dataCalib.size;
    m_dataCalib.calibType;
    m_dataCalib.flags;
    m_dataCalib.info.resize(0);
    m_dataCalib.methodSelectedID;
    m_dataCalib.channel.resize(0);
    m_dataCalib.ValidTime;
    m_dataCalib.unit;
    m_dataCalib.tolerance;
    m_dataCalib.toleranceType;

    m_dataCalib.setTolerance.resize(0);
    m_dataCalib.tolerancePriv;

    m_dataCalib.formulaChan;

    m_dataCalib.quantityCoeffCalib;
    m_dataCalib.quantitySamplesCnt;
    m_dataCalib.quantitySamplesCnt2;
    m_dataCalib.quantituZonds;
    m_dataCalib.waveSize;
    m_dataCalib.tunes.resize(0);
    m_dataCalib.status;
    m_dataCalib.controlPoint.resize(0);
    m_dataCalib.measuredValue.resize(0);
    m_dataCalib.approximatedValues.resize(0);
    m_dataCalib.calibTolerance.resize(0);
    m_dataCalib.calcTolerance.resize(0);

    m_dataCalib.saveTime;
    m_dataCalib.koeff.resize(0);
    m_dataCalib.nameKoeff.resize(0);
    m_dataCalib.methodParam.resize(0);
    m_dataCalib.ch1;
    m_dataCalib.ch2;
    m_dataCalib.ch3;
    m_dataCalib.quantitySpecialPoints;
    m_dataCalib.nameSpecialPoints.resize(0);
    m_dataCalib.reserve1.resize(0);
    m_dataCalib.reserve2.resize(0);
    m_dataCalib.resNameCoeff.resize(0);
    m_dataCalib.quantityStorage;
    m_dataCalib.reserveStorage.resize(0);
    m_dataCalib.quantityStorage1;
    m_dataCalib.reserveStroage1.resize(0);
}

QString CalibrSerialization::setTolerance(){
    QString f_string;
    foreach(auto value,m_dataCalib.setTolerance){
        f_string += QString::number(value) + " , ";
    }
    return f_string;
}

QString CalibrSerialization::tunes(){
    QString f_string;
    foreach(auto value,m_dataCalib.tunes){
        f_string += QString::number(value) + " , ";
    }
    return f_string;
}

QString CalibrSerialization::status(){
    switch(m_dataCalib.status){
    case 0 :
        return tr("no good");
    case 1 :
        return tr("good");
    case 2 :
        return tr("not completed");
    default:
        return "no info";
    }
}

template<typename T>
QString  CalibrSerialization::numVector(QVector<T>&vector){
    QString f_string;
    foreach(auto value,vector){
        f_string += QString::number(value) + " , ";
    }
    return f_string;
}
QString CalibrSerialization::strVector(QVector<QString>&vector){
    QString f_string;
    foreach(auto value,vector){
        f_string += value + " , ";
    }
    return f_string;
}


void CalibrSerialization::setData(QByteArray &CalibrData){
    dataClear();
    int n = 0;
    m_dataCalib.version = ReadVers(CalibrData, n);
    Read(CalibrData, n,m_dataCalib.size);
    Read(CalibrData, n,m_dataCalib.calibType);
    m_dataCalib.calibType = m_dataCalib.calibType & 0xFF;
    Read(CalibrData, n, m_dataCalib.flags);
    QString f_string;
    for(int index = 0;index <= CALIB_INFO;++index){
        ReadString(CalibrData, n,f_string);
        m_dataCalib.info.push_back(f_string);
    }

    if(m_dataCalib.version >= 105){
        ReadString(CalibrData, n,f_string);
        m_dataCalib.info.push_back(f_string);
        ReadString(CalibrData, n,f_string);
        m_dataCalib.info.push_back(f_string);
    }

    if(m_dataCalib.version  >= 106){
        Read(CalibrData, n, m_dataCalib.methodSelectedID);
    }

    if(m_dataCalib.version >= 107){
        for(int index = 0; index < CHANNEL_MAX; ++index){
            ReadString(CalibrData, n, f_string);
            m_dataCalib.channel.push_back(f_string);
        }
    }

    Read(CalibrData, n, m_dataCalib.ValidTime);
    ReadString(CalibrData, n, m_dataCalib.unit);
    Read(CalibrData, n, m_dataCalib.tolerance);
    Read(CalibrData, n, m_dataCalib.toleranceType);
    ReadArray(CalibrData, n, m_dataCalib.setTolerance);
    Read(CalibrData, n, m_dataCalib.tolerancePriv);
    Read(CalibrData, n, m_dataCalib.formulaChan);
    Read(CalibrData, n, m_dataCalib.quantityCoeffCalib);
    Read(CalibrData, n, m_dataCalib.quantitySamplesCnt);
    Read(CalibrData, n, m_dataCalib.quantitySamplesCnt2);
    Read(CalibrData, n, m_dataCalib.quantituZonds);
    Read(CalibrData, n, m_dataCalib.waveSize);
    ReadArray(CalibrData, n, m_dataCalib.tunes);
    Read(CalibrData, n, m_dataCalib.status);
    ReadArray(CalibrData, n, m_dataCalib.controlPoint);
    ReadArray(CalibrData, n, m_dataCalib.measuredValue);
    ReadArray(CalibrData, n, m_dataCalib.approximatedValues);
    ReadArray(CalibrData, n, m_dataCalib.calibTolerance);
    ReadArray(CalibrData, n, m_dataCalib.calcTolerance);
    Read(CalibrData, n, m_dataCalib.saveTime);
    ReadArray(CalibrData, n, m_dataCalib.koeff);
    for(int index = 0; index < 16; ++index){
        ReadString(CalibrData, n, f_string);
        m_dataCalib.nameKoeff.push_back(f_string);
    }
    for(int index = 0; index < 4; ++index){
        ReadString(CalibrData, n, f_string);
        m_dataCalib.methodParam.push_back(f_string);
    }
    Read(CalibrData, n, m_dataCalib.ch1);
    Read(CalibrData, n, m_dataCalib.ch2);
    Read(CalibrData, n, m_dataCalib.ch3);
    Read(CalibrData, n, m_dataCalib.quantitySpecialPoints);
    for(int k = 0; k < 16; k++){
        ReadString(CalibrData, n, f_string);
        m_dataCalib.nameSpecialPoints.push_back(f_string);
    }
    ReadArray(CalibrData, n, m_dataCalib.reserve1);
    ReadArray(CalibrData, n, m_dataCalib.reserve1);

    if(m_dataCalib.version >= 107){
        for(int k = 0; k < 16; k++){
            ReadString(CalibrData, n, f_string);
            m_dataCalib.resNameCoeff.push_back(f_string);
        }
        Read(CalibrData, n, m_dataCalib.quantityStorage);
        for(int k = 0; k < 32; k++){
            ReadString(CalibrData, n, f_string);
            m_dataCalib.reserveStorage.push_back(f_string);
        }
        Read(CalibrData, n, m_dataCalib.quantityStorage);
        double f_stor;
        for(int k = 0; k < 32; k++){
            Read(CalibrData, n, f_stor);
            m_dataCalib.reserveStroage1.push_back(f_stor);
        }
     }
}

QString CalibrSerialization::calibInfoHtml(){
    QFile file(":/templateCalib.html");
    QByteArray data;

    if (!file.open(QIODevice::ReadOnly))
        return QString();
    data = file.readAll();
    QString f_stringHtml = QString(data).arg(tr("Calibration information"),
                                             tr("Name: "),tr("Value: "),
    tr("Version"),QString::number(m_dataCalib.version),
     tr("Type"),QString::number(m_dataCalib.calibType),
    tr("Flags"),QString::number(m_dataCalib.flags),
     tr("Device name"),m_dataCalib.info[DEV_NAME],
    tr("Device number"),m_dataCalib.info[DEV_NUM],
     //tr("Device manufacturer"),m_dataCalib.info[DEV_MADE],
     tr("Driver"),m_dataCalib.info[FILE_NAME],
    tr("Parameter name"),m_dataCalib.info[PARAM_NAME],
     /*tr("Tool name"),m_dataCalib.info[TOOL_NAME],
     tr("Tool manufacturer"),m_dataCalib.info[TOOL_MADE],
    tr("Tool model"),m_dataCalib.info[TOOL_MODEL],
     tr("Tool range"),m_dataCalib.info[TOOL_RANGE],
     tr("Tool resolution"),m_dataCalib.info[TOOL_RESOL],
    tr("Tool accuracy"),m_dataCalib.info[TOOL_ACC],
     tr("Tool additionally info"),m_dataCalib.info[TOOL_ADD],
     tr("Installation name"),m_dataCalib.info[C_DEV_NAME],
     tr("Installation manufacturer"),m_dataCalib.info[C_DEV_MADE],
     tr("Installation model"),m_dataCalib.info[C_DEV_MODEL],
     tr("Installation range"),m_dataCalib.info[C_DEV_RANGE],
     tr("Installation resolution"),m_dataCalib.info[C_DEV_RESOL],
     tr("Installation accuracy"),m_dataCalib.info[C_DEV_ACC],
     tr("Installation additionally info"),m_dataCalib.info[C_DEV_ADD],*/
     tr("Calibration info"),m_dataCalib.info[CALIB_INFO],
     tr("Method"),m_dataCalib.info[METOD_NAME],
     tr("Calibration additionally info"),m_dataCalib.info[EXT_CALIB_INFO],
     tr("MethodID"),QString::number(m_dataCalib.methodSelectedID),
     tr("ch in1"),m_dataCalib.channel.size() > 0 ? m_dataCalib.channel[0] : "no",
     tr("ch in2"),m_dataCalib.channel.size() > 1 ? m_dataCalib.channel[1] : "no",
     tr("ch in3"),m_dataCalib.channel.size() > 2 ? m_dataCalib.channel[2] : "no",
     tr("ch out1"),m_dataCalib.channel.size() > 3 ? m_dataCalib.channel[3] : "no",
     tr("ch out2"),m_dataCalib.channel.size() > 4 ? m_dataCalib.channel[4] : "no",
     tr("ch out3"),m_dataCalib.channel.size() > 5 ? m_dataCalib.channel[5] : "no",
     tr("Valid time"),QString::number(m_dataCalib.ValidTime),
     tr("unit"),m_dataCalib.unit,
     tr("Tolerance: "),QString::number(m_dataCalib.tolerance),
     tr("Tolerance type: "),QString::number(m_dataCalib.toleranceType),
     tr("Set tolerance : "),setTolerance(),
     tr("Tolerance priv: "),QString::number(m_dataCalib.tolerancePriv),
     tr("Channel input: "),QString::number(m_dataCalib.formulaChan),
     tr("Quantity coeffs"),QString::number(m_dataCalib.quantityCoeffCalib),
     tr("Quantity points"),QString::number(m_dataCalib.quantitySamplesCnt),
    tr("Quantity points dop"),QString::number(m_dataCalib.quantitySamplesCnt2),
    tr("Quantity zonds"),QString::number(m_dataCalib.quantituZonds),
    tr("Wave size"),QString::number(m_dataCalib.waveSize),
     tr("Tunes"),tunes(),
     tr("Status"),status(),
     tr("Control points"),numVector(m_dataCalib.controlPoint),
     tr("Measured values"),numVector(m_dataCalib.measuredValue),
     tr("Approximated values"),numVector(m_dataCalib.approximatedValues),
     tr("Tolerance values"),numVector(m_dataCalib.calibTolerance),
     tr("Calc tolerance values"),numVector(m_dataCalib.calcTolerance),
     tr("Accumulation time"),QString::number(m_dataCalib.saveTime),
     tr("Calculated coefficients values"),numVector(m_dataCalib.koeff),
      tr("Calculated coefficients name"),strVector(m_dataCalib.nameKoeff),
     tr("Method"),m_dataCalib.methodParam[0],
    tr("Name ch1"),m_dataCalib.methodParam[1],
    tr("Name ch2"),m_dataCalib.methodParam[2],
    tr("Name ch3"),m_dataCalib.methodParam[3],
    tr("Number ch1"),QString::number(m_dataCalib.ch1),
    tr("Number ch2"),QString::number(m_dataCalib.ch2),
    tr("Number ch3"),QString::number(m_dataCalib.ch3),
     tr("Quantity special control points"),QString::number(m_dataCalib.quantitySpecialPoints),
     tr("Name special control points"),strVector(m_dataCalib.nameSpecialPoints),
    tr("Reserve1"),numVector(m_dataCalib.reserve1),
    tr("Reserve2"),numVector(m_dataCalib.reserve2),
     tr("Res name coeff"),strVector(m_dataCalib.resNameCoeff),
            tr("Quantity storage"),QString::number(m_dataCalib.quantityStorage),
            tr("Reserve storage"),strVector(m_dataCalib.reserveStorage),
            tr("Quantity storage1"),QString::number(m_dataCalib.quantityStorage1),
            tr("Reserve storage1"),numVector(m_dataCalib.reserveStroage1));

    return f_stringHtml;
}

void CalibrSerialization::InsertDataInInterpreter(IInterpreterLogData *interpreter){
    if(m_dataCalib.nameKoeff.size() < m_dataCalib.quantityCoeffCalib  ||
       m_dataCalib.koeff.size() < m_dataCalib.quantityCoeffCalib)
        return;
    for(int i = 0; i < m_dataCalib.quantityCoeffCalib; i++){
        interpreter->addVariable(m_dataCalib.nameKoeff.at(i),m_dataCalib.koeff.at(i));
    }
}




