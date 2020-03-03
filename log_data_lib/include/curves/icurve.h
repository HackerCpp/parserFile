#ifndef INTERFACECURVE_H
#define INTERFACECURVE_H
#include <QtCore>


class ICurve{
public:
    ICurve();
    virtual ~ICurve();

    virtual qreal data(uint index);
    virtual uint setData(qreal data);
    virtual uint setData(qreal data,uint index);
    virtual uint setData(const char *dataPtr,uint numberOfVectors);

    virtual ICurve *time();
    virtual ICurve *depth();
    virtual ICurve *userBaseValue();
    virtual bool setTime(const ICurve &time);
    virtual bool setDepth(const ICurve &depth);
    virtual bool setUserBaseValue(const ICurve &userBaseValue);

    virtual qreal maximum();
    virtual qreal minimum();
};

#endif // INTERFACECURVE_H
