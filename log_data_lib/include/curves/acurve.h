#ifndef ACURVE_H
#define ACURVE_H

#include "icurve.h"
#include "shortcut.h"


class ACurve : public ICurve{
    ICurve *m_time,*m_depth,*m_userValue;
protected:
    Desc *m_desc;
    ShortCut m_shortCut;

    qreal m_resolution;
    qreal m_maximum,m_minimum;
    uint m_size;
    uint m_sizeOfType;
    QString m_mnemonic;
    QString m_dataType;
    QString m_recordPoint;
    qreal m_positiveOffset;
    uint m_offset;

public:
    ACurve();
    virtual ~ACurve()override;

    virtual qreal data(uint index)override{return 0;}
    virtual QByteArray data()override{return 0;}
    virtual uint setData(qreal data)override;
    virtual uint setData(qreal data,uint index)override;
    virtual uint setData(const char *dataPtr,uint numberOfVectors)override;


    virtual ICurve *time()override;
    virtual ICurve *depth()override;
    virtual ICurve *userBaseValue()override;

    virtual bool setTime(ICurve *time)override;
    virtual bool setDepth(ICurve *depth)override;
    virtual bool setUserBaseValue(ICurve *userBaseValue)override;
    virtual QString recordPoint();

    virtual uint size()override;
    virtual qreal maximum()override;
    virtual qreal minimum()override;



    virtual Desc *desc()override;
    virtual ShortCut shortCut()override;
    virtual QString mnemonic()override;

    virtual void setShortCut(ShortCut shortCut);
    virtual void setOffset(uint offset);
    virtual void setSize(uint size);
    virtual void setMnemonic(QString mnemonic);
    virtual void setDataType(QString dataType);
    virtual void setRecordPoint(QString recordPoint);
    virtual void setDesc(Desc *desc);

    virtual QString dataType();

    virtual uint offset();




};

#endif // ACURVE_H
