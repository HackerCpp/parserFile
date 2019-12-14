#ifndef CURVEINT8_H
#define CURVEINT8_H
#include "inc/curve.h"

class CurveInt8 : public Curve{
    QVector<int8_t> *m_data;
public:
    CurveInt8();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveInt8()override;
};

#endif // CURVEINT8_H
