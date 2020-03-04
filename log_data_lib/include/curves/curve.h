#ifndef CURVE_H
#define CURVE_H

#include "acurve.h"
#include "desc.h"

template<typename T>
class Curve : public ACurve{
     QVector<T> *m_data;

public:
     Curve(){
         m_sizeOfType = sizeof(T);
         m_minimum = m_maximum = m_positiveOffset = 0;
     }
    ~Curve()override{}

     uint setData(const char *dataPtr,uint numberOfVectors)override;
};

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

#endif // CURVE_H
