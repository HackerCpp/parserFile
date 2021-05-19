#ifndef ACURVE_H
#define ACURVE_H

#include "icurve.h"
#include "shortcut.h"

/*! \addtogroup  curve Описание кривой
 * @{
 */
/*!
*  \authors Пряников Алексей Владимирович
*
*   \brief Абстрактный класс кривой.
*   Содержит общие поля для всех типов данных.
*/

class ACurve : public ICurve{

protected:
    ICurve *m_time,*m_depth,*m_userValue;
    Desc *m_desc;
    ShortCut m_shortCut;

    uint m_sizeOffsetInByte;
    uint m_sizeOfType;
    QString m_mnemonic;
    QString m_dataType;
    qreal m_recordPoint;
    qreal m_scale,m_offset; // data * m_scale + m_offset
    QString m_uid;
    qreal (ACurve::*dataCountingFunction)(qreal data);
    virtual qreal minData(){return 0;}
    virtual qreal maxData(){return 0;}
public:

    ACurve();
    virtual ~ACurve()override{}

    virtual inline qreal data(uint index)override{Q_UNUSED(index) return 0;}
    virtual inline qreal rawData(qreal data){Q_UNUSED(data) return 0;}
    virtual inline qreal recalculatedData(qreal data){Q_UNUSED(data) return 0;}
    virtual QByteArray data()override{return 0;}
    virtual void setData(qreal data)override{Q_UNUSED(data)}
    virtual void setData(qreal data,uint index)override{Q_UNUSED(data)Q_UNUSED(index)}
    virtual void setData(const char *dataPtr,uint numberOfVectors)override{Q_UNUSED(dataPtr)Q_UNUSED(numberOfVectors)}



    virtual ICurve *time()override;
    virtual ICurve *depth()override;
    virtual ICurve *userBaseValue()override;

    virtual bool setTime(ICurve *time)override;
    virtual bool setDepth(ICurve *depth)override;
    virtual bool setUserBaseValue(ICurve *userBaseValue)override;


    virtual uint size()override;
    virtual uint sizeOffset()override{return 0;}
    virtual uint sizeOffsetInBytes()override{return m_sizeOffsetInByte;}
    virtual qreal maximum()override;
    virtual qreal minimum()override;
    virtual qreal recordPoint()override{return m_recordPoint;}

    virtual Desc *desc()override;
    virtual ShortCut shortCut()override;
    void checkingTheDataFunction();
    void setOffset(qreal offset)override;
    void setScale(qreal scale)override;
    virtual QString mnemonic()override;
    QString dataType() override{return m_dataType;};
    virtual QString uniqID()override{return m_uid;}

    virtual void setShortCut(ShortCut shortCut)override;
    virtual void setSizeOffset(uint sizeOffset);
    virtual void setMnemonic(QString mnemonic)override;
    virtual void setDataType(QString dataType);
    virtual void setRecordPoint(qreal recordPoint)override{m_recordPoint = recordPoint;}
    virtual void setDesc(Desc *desc)override;

    virtual void load()override{}
    virtual void unload()override{}

};
/*! @} */
#endif // ACURVE_H
