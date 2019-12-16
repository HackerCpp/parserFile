#include "inc/curveuint16.h"

CurveUint16::CurveUint16():m_data(nullptr){
    m_sizeOfType = 2;
}
void CurveUint16::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<uint16_t>(dataSize);
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();
}
void CurveUint16::run(){
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

qreal CurveUint16::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index]);
    return 0;
}
qreal CurveUint16::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] - m_positiveOffset);
}

uint CurveUint16::getSize(){
    return m_data->size();
}
QByteArray CurveUint16::getDataByte(){
    if(m_data)
        return QByteArray::fromRawData( reinterpret_cast<const char*>(m_data->constData()), static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}
CurveUint16::~CurveUint16(){
    if(m_data)
        delete m_data;
}
