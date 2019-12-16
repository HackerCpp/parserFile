#ifndef CURVEUINT8_H
#define CURVEUINT8_H
#include "inc/curve.h"


class CurveUint8 : public Curve{
    QVector<uint8_t> *m_data;
public:
    CurveUint8();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveUint8()override;
};

#endif // CURVEUINT8_H
