#ifndef INTERFACECURVE_H
#define INTERFACECURVE_H
#include <QtCore>

#include "desc.h"
#include "shortcut.h"

/*! \defgroup curve Описание кривой
 * @{
 */
 /*!
 *  \authors Пряников Алексей Владимирович
 *
 *   \brief Интерфейс кривой, любая кривая с данными
 *      наследуется от данного интерфейса.
*/

class ICurve : public QObject{
    Q_OBJECT

public:
    ICurve(){}
    virtual ~ICurve(){}

    virtual inline qreal data(uint index){Q_UNUSED(index)return 0;}
    virtual QByteArray data(){return QByteArray();}
    virtual void setData(qreal data);
    virtual void setData(qreal data,uint index);
    virtual void setData(const char *dataPtr,uint numberOfVectors);
    virtual void setOffset(qreal offset){Q_UNUSED(offset)}
    virtual void setScale(qreal scale){Q_UNUSED(scale)}
    virtual void setDesc(Desc *desc){Q_UNUSED(desc)}
    virtual void setShortCut(ShortCut shortCut){Q_UNUSED(shortCut)}
    virtual void setMnemonic(QString mnemonic){Q_UNUSED(mnemonic)}
    virtual void setRecordPoint(qreal recordPoint){Q_UNUSED(recordPoint)}
    virtual void setSizeOffsetInBytes(uint sizeOffset){Q_UNUSED(sizeOffset)}

    virtual ICurve *time();
    virtual ICurve *depth();
    virtual ICurve *userBaseValue();

    virtual bool setTime(ICurve *time);
    virtual bool setDepth(ICurve *depth);
    virtual bool setUserBaseValue(ICurve *userBaseValue);

    virtual uint size();
    virtual uint sizeOffset(){return 0;}
    virtual uint sizeOffsetInBytes(){return 0;}
    virtual qreal maximum();
    virtual qreal minimum();
    virtual Desc *desc();
    virtual ShortCut shortCut();
    virtual QString mnemonic()const{return nullptr;}
    virtual QString dataType()const{return "";}
    virtual QString uniqID()const{return "";}
    virtual qreal recordPoint()const{return 0;}

    virtual void load(){}
    virtual void unload(){}

    static ICurve * curveCreater(const ICurve &curve);
    static ICurve * curveCreater(const QString dataType);
};
/*! @} */
#endif // INTERFACECURVE_H
