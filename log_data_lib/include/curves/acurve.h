#ifndef ACURVE_H
#define ACURVE_H

#include "icurve.h"
#include "shortcut.h"
#include "desc.h"

class ACurve : public ICurve{
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
    virtual ~ACurve();

    virtual uint setData(qreal data);
    virtual uint setData(qreal data,uint index);
    virtual uint setData(const char *dataPtr,uint numberOfVectors);

    virtual void setShortCut(ShortCut shortCut);
    virtual void setOffset(uint offset);
    virtual void setSize(uint size);
    virtual void setMnemonic(QString mnemonic);
    virtual void setDataType(QString dataType);
    virtual void setRecordPoint(QString recordPoint);
    virtual void setDesc(Desc *desc);

    virtual uint offset();

};

#endif // ACURVE_H
