#include "curvefloat32.h"
#include <QTime>

CurveFloat32::CurveFloat32() : m_data(nullptr){
    m_sizeOfType = 4;
}

void CurveFloat32::setData(const char * dataPointer,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<float>(static_cast<int>(dataSize));
    memcpy(m_data->data(),dataPointer,dataSizeInBytes);
    start();
}

void CurveFloat32::run(){
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
    /*m_zipArray = new QByteArray();
    QTime time = QTime::currentTime();
    gzipCompress(QByteArray((const char *)m_data->data(),m_data->size() * 4),*m_zipArray,-1);
    qDebug() << (m_data->size() * 4) << "::" << (m_data->size() * 4)/m_zipArray->size() << "Time: "<< time.msecsTo( QTime::currentTime() );*/
}


qreal CurveFloat32::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index]);
    return 0;
}
qreal CurveFloat32::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] - m_positiveOffset);
}

uint CurveFloat32::getSize(){
    return static_cast<uint>(m_data->size());
}
QByteArray CurveFloat32::getDataByte(){
    if(m_data)
        return QByteArray::fromRawData( reinterpret_cast<const char*>(m_data->constData()), static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}
CurveFloat32::~CurveFloat32(){
    if(m_data)
        delete m_data;
}
