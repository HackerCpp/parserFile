#ifndef CURVE_H
#define CURVE_H

#include "acurve.h"

template<typename T>
class Curve : public ACurve{
     QVector<T> *m_data;

public:
     Curve(){
         m_sizeOfType = sizeof(T);
         m_minimum = m_maximum = m_positiveOffset = 0;
     }
    ~Curve()override{}

     qreal data(uint index)override;
     QByteArray data() override;
     uint setData(const char *dataPtr,uint numberOfVectors)override;
     uint setData(qreal data,uint index)override;

     uint size()override;
};

template<typename T> qreal Curve<T>::data(uint index){
    if(index>m_data->size())
    {
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


template<typename T> uint Curve<T>::setData(qreal data,uint index){
    if(index>m_data->size())
    {
        qDebug()<<"Индекс вышел за пределы массива, вернули 0";
        return 0;
    }
    m_data->data()[index] = data;
    return m_size;
}

template<typename T> uint Curve<T>::setData(const char *dataPtr,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_size/m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_size;
    m_data = new QVector<T>(dataSize);
    memcpy(m_data->data(),dataPtr,dataSizeInBytes);
    m_minimum = static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));
    m_maximum = static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));
    m_positiveOffset = m_minimum < 0?m_minimum:0;
    return dataSizeInBytes;
}

template<typename T> uint Curve<T>::size(){
    if(m_data)
        return m_data->size();
    return 0;
}

#endif // CURVE_H
