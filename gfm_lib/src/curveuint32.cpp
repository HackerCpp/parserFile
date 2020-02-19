#include "inc/curveuint32.h"
#include "QFile"

CurveUint32::CurveUint32():m_data(nullptr){
    m_sizeOfType = 4;
}
void CurveUint32::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<uint32_t>(dataSize);
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();

}
void CurveUint32::run(){
    bool ok;
    m_resolution = m_desc->getParam("resolution").replace(',','.').toDouble(&ok);
    if(!ok)
        m_resolution = 1;
    foreach(auto value,*m_data){
        m_minimum = qMin(m_minimum,static_cast<qreal>(value));
        m_maximum = qMax(m_maximum,static_cast<qreal>(value));
    }
    m_positiveOffset = m_minimum < 0?m_minimum:0;

}

qreal CurveUint32::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index] * m_resolution);
    return 0;
}

qreal CurveUint32::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] * m_resolution - m_positiveOffset);
}

uint CurveUint32::getSize(){
    return m_data->size();
}

QByteArray CurveUint32::getDataByte(){
    if(m_data){
        return QByteArray((const char*)m_data->data(),static_cast<int>(m_sizeOfType) * m_data->size());
    }
    return QByteArray();
}
CurveUint32::~CurveUint32(){
    if(m_data)
        delete m_data;
}
