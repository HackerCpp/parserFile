#include "inc/curveint32.h"

CurveInt32::CurveInt32():m_data(nullptr){
    m_sizeOfType = 4;

}
void CurveInt32::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<int32_t>(dataSize);
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();
}
void CurveInt32::run(){
    bool ok;
    if(m_parameterMnemonics.indexOf("TIME(MSEC)") != -1){
        qreal f_resolutoin = m_desc->getParam("resolution").replace(',','.').toDouble(&ok);
        if(ok){
            for(auto value = m_data->begin(); value < m_data->end();value++){
                *value *= f_resolutoin;
            }
        }
        else{
           qDebug() << "resolution не переведён в число. int32 depth"<< m_parameterMnemonics <<"; resolution: "<< m_desc->getParam("resolution");
        }
     }
     else if(m_parameterMnemonics.indexOf("DEPTH(COUNTS)") != -1){
        qreal f_resolutoin = m_desc->getParam("resolution").replace(',','.').toDouble(&ok);
        if(ok){
            qreal f_length = m_desc->getCalib("length").replace(',','.').toDouble(&ok);
            if(ok){
                qreal f_counts = m_desc->getCalib("length").replace(',','.').toDouble(&ok);
                if(ok){
                    foreach(auto value,*m_data){
                        value *= static_cast<int>(f_length / f_counts * f_resolutoin);
                    }
                }
                else{
                   qDebug() << "count не переведён в число.int32 depth";
                }
            }
            else{
                qDebug() << "length не переведён в число.int32 depth"<< m_parameterMnemonics;
            }
        }
        else{
            qDebug() << "resolution не переведён в число. int32 depth"<< m_parameterMnemonics <<"; resolution: "<< m_desc->getParam("resolution");
        }
    }

    foreach(auto value,*m_data){
        m_minimum = qMin(m_minimum,static_cast<qreal>(value));
        m_maximum = qMax(m_maximum,static_cast<qreal>(value));
    }
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

qreal CurveInt32::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index]);
    return 0;
}
qreal CurveInt32::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] - m_positiveOffset);
}

uint CurveInt32::getSize(){
    return m_data->size();
}
QByteArray CurveInt32::getDataByte(){
    if(m_data)
        return QByteArray::fromRawData( reinterpret_cast<const char*>(m_data->constData()), static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}
CurveInt32::~CurveInt32(){
    if(m_data)
        delete m_data;
}
