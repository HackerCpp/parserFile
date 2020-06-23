#ifndef CURVE_H
#define CURVE_H

#include "acurve.h"

template<typename T>
class Curve : public ACurve{
     QVector<T> *m_data;
     void updateDataType();
public:
     Curve(){
         updateDataType();
         m_sizeOfType = sizeof(T);
         m_minimum = m_maximum = m_positiveOffset = 0;
     }
     Curve(int size,int offset);
    ~Curve()override{}

     qreal data(uint index)override;
     QByteArray data() override;
     void setData(const char *dataPtr,uint numberOfVectors)override;
     void setData(qreal data,uint index)override;

     uint size()override;
     uint sizeOffset()override;
};

template<typename T> void Curve<T>::updateDataType(){
    if(std::is_same<T, uint8_t>::value)
        m_dataType = "UINT8";
    else if(std::is_same<T, int8_t>::value)
        m_dataType = "INT8";
    else if(std::is_same<T, uint32_t>::value)
        m_dataType = "UINT32";
    else if(std::is_same<T, int32_t>::value)
        m_dataType = "INT32";
    else if(std::is_same<T, uint16_t>::value)
        m_dataType = "UINT16";
    else if(std::is_same<T, int16_t>::value)
        m_dataType = "INT16";
    else if(std::is_same<T, float_t>::value)
        m_dataType = "FLOAT32";
    else if(std::is_same<T, double>::value)
        m_dataType = "DOUBLE64";
    else if(std::is_same<T, uint64_t>::value)
        m_dataType = "UINT64";
    else if(std::is_same<T, int64_t>::value)
        m_dataType = "INT64";
}

template<typename T> Curve<T>::Curve(int size,int offset){  
    updateDataType();
    int f_size = size * offset;
    m_data = new QVector<T>(f_size);
    m_sizeOfType = sizeof(T);
    m_sizeOffsetInByte = offset * m_sizeOfType;
    m_minimum = m_maximum = m_positiveOffset = 0;
    m_offset = offset;
}

template<typename T> qreal Curve<T>::data(uint index){
    if(index > m_data->size()){
        qDebug()<<"Индекс вышел за пределы массива, вернули 0";
        return 0;
    }
    return m_data->data()[index];
}

template<typename T> QByteArray Curve<T>::data(){
    if(m_data)
        return QByteArray((const char*)m_data->data(),static_cast<int>(m_sizeOfType)*m_data->size());
    return QByteArray();
}


template<typename T> void Curve<T>::setData(qreal data,uint index){
    if(index>m_data->size()){
        qDebug()<<"Индекс вышел за пределы массива, вернули 0";
        return;
    }
    m_data->data()[index] = data;
}

template<typename T> void Curve<T>::setData(const char *dataPtr,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_sizeOffsetInByte/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_sizeOffsetInByte;
    m_data = new QVector<T>(dataSize);
    memcpy(m_data->data(),dataPtr,dataSizeInBytes);
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
}

template<typename T> uint Curve<T>::size(){
    if(m_data)
        return m_data->size();
    return 0;
}

template<typename T> uint Curve<T>::sizeOffset(){
    return m_sizeOffsetInByte/m_sizeOfType;
}

#endif // CURVE_H
