#ifndef CURVE_H
#define CURVE_H

#include "acurve.h"

template<typename T>
class Curve : public ACurve{
     QVector<T> *m_data;
     void updateDataType();
public:
     Curve():ACurve(){
         updateDataType();
         m_data = new QVector<T>();
         m_sizeOfType = sizeof(T);
         m_time = m_depth = nullptr;
         m_sizeOffsetInByte = 1 * m_sizeOfType;
     }
     Curve(int size,int offset);
     Curve(const Curve<T> &curve);
    ~Curve()override{QFile(QDir().currentPath() + "/temporary/" + m_uid + ".bin").remove();}

     inline qreal rawData(qreal data);
     inline qreal recalculatedData(qreal data);
     inline qreal data(uint index)override;
     QByteArray data() override;
     void setData(qreal data)override;
     void setData(const char *dataPtr,uint numberOfVectors)override;
     void setData(qreal data,uint index)override;

     uint size()override;
     uint sizeOffset()override;

     qreal minData(){return static_cast<qreal>(*std::min_element(m_data->begin(),m_data->end()));}
     qreal maxData(){return static_cast<qreal>(*std::max_element(m_data->begin(),m_data->end()));}

     void load()override;
     void unload()override;
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
        m_dataType = "FLOAT64";
    else if(std::is_same<T, uint64_t>::value)
        m_dataType = "UINT64";
    else if(std::is_same<T, int64_t>::value)
        m_dataType = "INT64";
}

template<typename T> Curve<T>::Curve(int size,int offset):ACurve(){
    updateDataType();
    int f_size = size * offset;
    m_data = new QVector<T>(f_size);
    m_sizeOfType = sizeof(T);
    m_sizeOffsetInByte = offset * m_sizeOfType;
}

template<typename T> Curve<T>::Curve(const Curve<T> &curve){
    m_data = new QVector<T>;
    m_sizeOfType = sizeof(T);
    m_sizeOffsetInByte = curve.m_sizeOffsetInByte;
    m_uid = QUuid().createUuid().toString();
    m_time = curve.m_time;
    m_depth = curve.m_depth;
    m_userValue = curve.m_userValue;
    m_desc = curve.m_desc;
    m_shortCut = curve.m_shortCut;

    m_resolution = curve.m_resolution;
    m_mnemonic = curve.m_mnemonic;
    m_dataType = curve.m_dataType;
    m_recordPoint = curve.m_recordPoint;
    const_cast<Curve<T>*>(&curve)->load();
    foreach(auto value,*curve.m_data){
        m_data->push_back(value);
    }
    const_cast<Curve<T>*>(&curve)->unload();
    unload();

}

template<typename T> qreal Curve<T>::rawData(qreal data){
    return data;
}

template<typename T> qreal Curve<T>::recalculatedData(qreal data){
    return data * m_scale + m_offset;
}

template<typename T> QByteArray Curve<T>::data(){
    if(m_data)
        return QByteArray((const char*)m_data->data(),static_cast<int>(m_sizeOfType)*m_data->size());
    return QByteArray();
}

template<typename T> qreal Curve<T>::data(uint index){
    if(index >= static_cast<uint>(m_data->size())){
        return qQNaN();
    }
    return (this->*dataCountingFunction)(m_data->at(index));
}

template<typename T> void Curve<T>::setData(qreal data){
    m_data->push_back(data);
}

template<typename T> void Curve<T>::setData(qreal data,uint index){
    if(static_cast<int>(index) > m_data->size()){
        qDebug()<<"Индекс вышел за пределы массива, вернули 0";
        return;
    }
    m_data->data()[index] = data;
}

template<typename T> void Curve<T>::setData(const char *dataPtr,uint numberOfVectors){
    uint dataSize = numberOfVectors * (m_sizeOffsetInByte / m_sizeOfType);
    uint dataSizeInBytes = numberOfVectors * m_sizeOffsetInByte;
    m_data = new QVector<T>(dataSize);
    memcpy(m_data->data(),dataPtr,dataSizeInBytes);
    unload();
}

template<typename T> uint Curve<T>::size(){
    if(m_data)
        return m_data->size();
    return 0;
}

template<typename T> uint Curve<T>::sizeOffset(){
    return m_sizeOffsetInByte/m_sizeOfType;
}

template<typename T> void Curve<T>::load(){
    /*if(!m_data)
        return;
    if(m_desc->param("draw_type") == "TIME" || m_desc->param("draw_type") == "DEPTH")
        return;
    if(!m_numberOfUsers){
        QFile f_file(QDir().currentPath() + "/temporary/" + m_uid + ".bin");
        if(f_file.open(QIODevice::ReadOnly)){
            QDataStream read(&f_file);
            read.setVersion(QDataStream::Qt_5_15);
            read >> *m_data;
            m_data->squeeze();
            f_file.close();
        }
        else{
            qDebug() << "Не получается загрузить данные файл " << QDir().currentPath() + "/temporary/" + m_uid + ".bin" << "не может быть открыт";
        }
    }
    ++m_numberOfUsers;*/
}

template<typename T> void Curve<T>::unload(){
    /*if(!m_data)
        return;
    if(m_desc->param("draw_type") == "TIME" || m_desc->param("draw_type") == "DEPTH")
        return;
    m_numberOfUsers = m_numberOfUsers > 0 ? --m_numberOfUsers : 0;
    if(m_numberOfUsers > 0)
        return;
    QFile f_file(QDir().currentPath() + "/temporary/" + m_uid + ".bin");
    if(f_file.open(QIODevice::WriteOnly)){
        QDataStream write(&f_file);
        write.setVersion(QDataStream::Qt_5_15);
        write << *m_data;
        f_file.close();
        QVector<T>().swap(*m_data);
        Q_ASSERT(m_data->capacity() == 0);
    }*/
}

#endif // CURVE_H
