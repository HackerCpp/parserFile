#ifndef CURVEUINT16_H
#define CURVEUINT16_H
#include "inc/curve.h"

class CurveUint16 : public Curve{
    QVector<uint16_t> *m_data;
public:
    CurveUint16();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveUint16();
};

#endif // CURVEUINT16_H
