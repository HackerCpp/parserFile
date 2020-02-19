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
    m_resolution = m_desc->getParam("resolution").replace(',','.').toDouble(&ok);
     /*else if(m_parameterMnemonics.indexOf("DEPTH(COUNTS)") != -1){


     qreal f_length = m_desc->getCalib("length").replace(',','.').toDouble(&ok);

                qreal f_counts = m_desc->getCalib("length").replace(',','.').toDouble(&ok);

                    foreach(auto value,*m_data){
                        value *= static_cast<int>((f_length / f_counts) * f_resolutoin);
*/
    foreach(auto value,*m_data){
        m_minimum = qMin(m_minimum,static_cast<qreal>(value));
        m_maximum = qMax(m_maximum,static_cast<qreal>(value));
    }
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

qreal CurveInt32::data(uint index){
    if(index < static_cast<uint>(m_data->size()))
        return static_cast<qreal>(m_data->data()[index] * m_resolution);
    return 0;
}

qreal CurveInt32::operator[](int index){
    return static_cast<qreal>(m_data->data()[index] * m_resolution - m_positiveOffset);
}

uint CurveInt32::getSize(){
    return m_data->size();
}

QByteArray CurveInt32::getDataByte(){
    if(m_data)
        return QByteArray((const char*)m_data->data(),static_cast<int>(m_sizeOfType) * m_data->size());
    return QByteArray();
}

CurveInt32::~CurveInt32(){
    if(m_data)
        delete m_data;
}
