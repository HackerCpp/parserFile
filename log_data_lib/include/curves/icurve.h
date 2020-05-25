#ifndef INTERFACECURVE_H
#define INTERFACECURVE_H
#include <QtCore>

#include "desc.h"
#include "shortcut.h"

class ICurve : public QObject{
    Q_OBJECT
public:
    ICurve();
    virtual ~ICurve();

    virtual qreal data(uint index);
    virtual QByteArray data();
    virtual void setData(qreal data);
    virtual void setData(qreal data,uint index);
    virtual void setData(const char *dataPtr,uint numberOfVectors);

    virtual ICurve *time();
    virtual ICurve *depth();
    virtual ICurve *userBaseValue();

    virtual bool setTime(ICurve *time);
    virtual bool setDepth(ICurve *depth);
    virtual bool setUserBaseValue(ICurve *userBaseValue);

    virtual uint size();
    virtual uint sizeOffset(){return 0;}
    virtual qreal maximum();
    virtual qreal minimum();
    virtual Desc *desc();
    virtual ShortCut shortCut();
    virtual QString mnemonic();
};

#endif // INTERFACECURVE_H
