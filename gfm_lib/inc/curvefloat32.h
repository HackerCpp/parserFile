#ifndef CURVEFLOAT32_H
#define CURVEFLOAT32_H
#include "inc/curve.h"

class CurveFloat32 : public Curve{
    QVector<float> *m_data;
public:
    CurveFloat32();
    void setData(const char * dataPointer,uint numberOfVectors)override;
    void run()override;
    qreal data(uint index)override;
    qreal operator[](int index)override;

    uint getSize()override;
    QByteArray getDataByte()override;
    ~CurveFloat32()override;
};

#endif // CURVEFLOAT32_H
