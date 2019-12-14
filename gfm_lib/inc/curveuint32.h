#ifndef CURVEUINT32_H
#define CURVEUINT32_H
#include "inc/curve.h"

class CurveUint32 : public Curve{
    QVector<uint32_t> *m_data;
public:
    CurveUint32();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveUint32()override;
};

#endif // CURVEUINT32_H
