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
    uint m_sizeOffsetInByte;
    uint m_sizeOfType;
    QString m_mnemonic;
    QString m_dataType;
    qreal m_recordPoint;
    qreal m_positiveOffset;
    uint m_offset;

public:
    static const qreal M_NOVALID;

    ACurve();
    virtual ~ACurve()override;

    virtual qreal data(uint index)override{return 0;}
    virtual QByteArray data()override{return 0;}
    virtual void setData(qreal data)override{}
    virtual void setData(qreal data,uint index)override{}
    virtual void setData(const char *dataPtr,uint numberOfVectors)override{}



    virtual ICurve *time()override;
    virtual ICurve *depth()override;
    virtual ICurve *userBaseValue()override;

    virtual bool setTime(ICurve *time)override;
    virtual bool setDepth(ICurve *depth)override;
    virtual bool setUserBaseValue(ICurve *userBaseValue)override;


    virtual uint size()override;
    virtual uint sizeOffset()override{return 0;}
    virtual uint sizeOffsetInBytes(){return m_sizeOffsetInByte;}
    virtual qreal maximum()override;
    virtual qreal minimum()override;
    virtual qreal recordPoint()override{return m_recordPoint;}



    virtual Desc *desc()override;
    virtual ShortCut shortCut()override;
    virtual QString mnemonic()override;

    virtual void setShortCut(ShortCut shortCut)override;
    virtual void setOffset(uint offset);
    virtual void setSizeOffset(uint sizeOffset);
    virtual void setMnemonic(QString mnemonic)override;
    virtual void setDataType(QString dataType);
    virtual void setRecordPoint(qreal recordPoint)override{m_recordPoint = recordPoint;}
    virtual void setDesc(Desc *desc)override;

    virtual QString dataType();

    virtual uint offset();




};

#endif // ACURVE_H
