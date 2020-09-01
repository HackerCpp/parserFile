#include "calibserialization.h"
#include "QDebug"
#include <QTextCodec>

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

void CalibrSerialization::WriteVers(QByteArray& CalibrData, ushort v){
    /*CalibrData.SetSize(6);
    CalibrData[0] = LOBYTE(v);
    CalibrData[1] = HIBYTE(v);
    CalibrData[2] = 2;
    CalibrData[3] = 0;
    CalibrData[4] = 0;
    CalibrData[5] = 0;*/
}

void CalibrSerialization::WriteSize(QByteArray &CalibrData){
    /*int n = CalibrData.GetSize();
    memcpy(CalibrData.GetData()+2, &n, sizeof(n));*/
}

void CalibrSerialization::WriteString(QByteArray &CalibrData, const QString &str){
    /*int n = CalibrData.GetSize();
    int l = str.GetLength();
    CalibrData.SetSize(n + sizeof(l) + l*sizeof(wchar_t));
    memcpy(CalibrData.GetData()+n, &l, sizeof(l));
    if(l > 0)
        memcpy(CalibrData.GetData()+n+sizeof(l), (LPCWSTR)str, l*sizeof(wchar_t));*/
}

template<typename T>
void CalibrSerialization::WriteArray(QByteArray& CalibrData, const QVector<T>& ar){
    /*int n = CalibrData.GetSize();
    int l = ar.GetSize();
    CalibrData.SetSize(n + sizeof(l) + l*sizeof(T));
    memcpy(CalibrData.GetData()+n, &l, sizeof(l));
    if(l > 0)
        memcpy(CalibrData.GetData()+n+sizeof(l), &ar[0], l*sizeof(T));*/
}

template<typename T>
void CalibrSerialization::Write(QByteArray& CalibrData, T v){
    /*int n = CalibrData.GetSize();
    CalibrData.SetSize(n + sizeof(v));
    memcpy(CalibrData.GetData()+n, &v, sizeof(v));*/
}

void CalibrSerialization::readAll(QByteArray &CalibrData){
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

    //m_Tunes.resize(MAX_TUNES + 1);
    ReadArray(CalibrData, n, m_dataCalib.tunes);

    Read(CalibrData, n, m_dataCalib.status);

    bool f_bZonds, f_bWave;
    f_bZonds = f_bWave;
    /*int f_quantitysamples = 0;
    switch(m_dataCalib.calibType){
        case NOTYPE:
        case ACCELER: // акселерометры
        case STANDART: // стандарт
            f_quantitysamples = m_dataCalib.quantitySamplesCnt2;
            break;
        case PARAMDEP: // с параметрической зависимостью
            f_quantitysamples = m_dataCalib.quantitySamplesCnt * m_dataCalib.quantitySamplesCnt2;
            break;
        case MULTIZOND: // многозондовая
            f_quantitysamples = m_dataCalib.quantitySamplesCnt;
            f_bZonds = true;
            break;
        case WAVE:
            f_quantitysamples = 1;
            break;
    }


    switch(m_dataCalib.calibType){
        case NOTYPE:	// по умолчанию считаем стандартную
        case ACCELER:	// акселерометры
        case STANDART:  	// стандартная калибровка
            m_dataCalib.controlPoint.resize(f_quantitysamples * 3);
            m_dataCalib.measuredValue.resize(f_quantitysamples * 3);
            m_dataCalib.approximatedValues.resize(f_quantitysamples * 3);
            m_dataCalib.calibTolerance.resize(f_quantitysamples * 8);
            m_dataCalib.calcTolerance.resize(8);
            m_dataCalib.reserve1.resize(f_quantitysamples);
            m_dataCalib.reserve2.resize(f_quantitysamples);
            m_dataCalib.setTolerance.resize(8);
            break;
        case PARAMDEP:	// калибровка с параметрической зависимостью
            m_dataCalib.controlPoint.resize(f_quantitysamples * 3);
            m_dataCalib.measuredValue.resize(f_quantitysamples * 3);
            m_dataCalib.approximatedValues.resize(f_quantitysamples * 3);
            m_dataCalib.calibTolerance.resize(f_quantitysamples * 8);
            m_dataCalib.calcTolerance.resize(8);
            m_dataCalib.reserve1.resize(f_quantitysamples);
            m_dataCalib.reserve2.resize(f_quantitysamples);
            m_dataCalib.setTolerance.resize(8);
            break;
        case MULTIZOND: // многозондовая калибровка
            m_dataCalib.controlPoint.resize(f_quantitysamples * 3);
            m_dataCalib.measuredValue.resize(f_quantitysamples * m_dataCalib.quantituZonds);
            m_dataCalib.approximatedValues.resize(f_quantitysamples * m_dataCalib.quantituZonds);
            m_dataCalib.calibTolerance.resize(f_quantitysamples * m_dataCalib.quantituZonds * 8);
            m_dataCalib.calcTolerance.resize(m_dataCalib.quantituZonds * 4 + 4);
            m_dataCalib.reserve1.resize(f_quantitysamples * m_dataCalib.quantituZonds);
            m_dataCalib.reserve2.resize(f_quantitysamples * m_dataCalib.quantituZonds);
            m_dataCalib.setTolerance.resize(m_dataCalib.quantituZonds * 2);
            break;
        case WAVE: // калибровка волны/спектра
            if(f_bWave){
                m_dataCalib.controlPoint.resize(m_dataCalib.waveSize);
                m_dataCalib.measuredValue.resize(m_dataCalib.waveSize);
            }
            else{
                m_dataCalib.controlPoint.resize(3);
                m_dataCalib.measuredValue.resize(3);
            }
            m_dataCalib.calibTolerance.resize(8);
            m_dataCalib.setTolerance.resize(4);
            m_dataCalib.calcTolerance.resize(4);
            m_dataCalib.reserve1.resize(3);
            m_dataCalib.reserve2.resize(3);
            break;
        }
    m_dataCalib.koeff.resize(fmax(m_dataCalib.quantityCoeffCalib,9));*/

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
        qDebug() << m_dataCalib.nameKoeff[index];
    }






}





