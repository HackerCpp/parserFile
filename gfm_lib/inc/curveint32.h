#ifndef CURVEINT32_H
#define CURVEINT32_H
#include "inc/curve.h"

class CurveInt32 : public Curve{
    QVector<int32_t> *m_data;
public:
    CurveInt32();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;
    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveInt32()override;
};

#endif // CURVEINT32_H
