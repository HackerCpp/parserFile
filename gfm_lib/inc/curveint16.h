#ifndef CURVEINT16_H
#define CURVEINT16_H
#include "inc/curve.h"

class CurveInt16 : public Curve{
    QVector<int16_t> *m_data;
public:
    CurveInt16();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveInt16()override;
};

#endif // CURVEINT16_H
