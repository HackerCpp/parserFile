#ifndef INTERFACECURVE_H
#define INTERFACECURVE_H
#include <QtCore>

template<typename T>
class InterfaceCurve{
public:
    InterfaceCurve();
    virtual ~InterfaceCurve();

    virtual qreal data(uint index);
    virtual uint setData(T data);
    virtual uint setData(T data,uint index);
    virtual uint setData(const T &dataPtr,uint size);

    virtual InterfaceCurve *time();
    virtual InterfaceCurve *depth();
    virtual InterfaceCurve *userBaseValue();
    virtual bool setTime(const InterfaceCurve &time);
    virtual bool setDepth(const InterfaceCurve &depth);
    virtual bool setUserBaseValue(const InterfaceCurve &userBaseValue);

    virtual qreal maximum();
    virtual qreal minimum();


};

#endif // INTERFACECURVE_H
