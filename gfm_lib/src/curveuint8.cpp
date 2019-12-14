#include "inc/curveuint8.h"

CurveUint8::CurveUint8():m_data(nullptr){
    m_sizeOfType = 1;
}

void CurveUint8::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<uint8_t>(static_cast<int>(dataSize));
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();
}
void CurveUint8::run(){
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

qreal CurveUint8::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index]);
    return 0;
}
qreal CurveUint8::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] - m_positiveOffset);
}

uint CurveUint8::getSize(){
    return static_cast<uint>(m_data->size());
}

QByteArray CurveUint8::getDataByte(){
    if(m_data)
        return QByteArray::fromRawData( reinterpret_cast<const char*>(m_data->constData()), static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}

CurveUint8::~CurveUint8(){
    if(m_data)
        delete m_data;
}
