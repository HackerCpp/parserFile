#include "inc/curveint16.h"

CurveInt16::CurveInt16():m_data(nullptr){
    m_sizeOfType = 2;
}
void CurveInt16::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<int16_t>(dataSize);
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();
}
void CurveInt16::run(){
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

qreal CurveInt16::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index]);
    return 0;
}
qreal CurveInt16::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] - m_positiveOffset);
}

uint CurveInt16::getSize(){
    return m_data->size();
}
QByteArray CurveInt16::getDataByte(){
    if(m_data)
        return QByteArray((const char*)m_data->data(),static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}
CurveInt16::~CurveInt16(){
    if(m_data)
        delete m_data;
}
