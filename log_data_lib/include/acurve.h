#ifndef ACURVE_H
#define ACURVE_H

#include "icurve.h"


template<typename T>
class ACurve : public ICurve{
public:
    ACurve();
    virtual ~ACurve();

    virtual uint setData(T data);
    virtual uint setData(T data,uint index);
    virtual uint setData(const T &dataPtr,uint size);
};

#endif // ACURVE_H
