#ifndef AITEM_H
#define AITEM_H
#include <QVariant>
#include "astyleitem.h"






//enum PaintMode{CURVE_MODE,NUMBERS_MODE};
enum TypeItem{LINE,ACU,MARK};


class AItem {
    TypeItem m_type;
    QString m_name;
    QString m_visible;
    struct Begin{
        bool is_beginValue;
        qreal beginValue;
        qreal zeroOffset;
    }m_begin;

    struct End{
        bool is_endValue;
        qreal endValue;
        qreal scale;
    }m_end;

    struct MultiScale{
        bool is_multiscale;
        qreal gleamCount;
        qreal gleamScale;
    }m_multiScale;
public:
    AItem();
    virtual ~AItem();

    virtual QString name();
    virtual QString visible();

    virtual bool isBeginValue();
    virtual qreal beginValue();
    virtual qreal zeroOffset();

    virtual bool isEndValue();
    virtual qreal endValue();
    virtual qreal scale();

    virtual bool isMultiScale();
    virtual qreal glemCount();
    virtual qreal glemScale();


    virtual TypeItem Type();


    virtual void setBegin(bool isBegin, qreal begin, qreal zeroOffset);
    virtual void setEnd(bool isEnd,qreal end,qreal scale);
    virtual void setMultiScale(bool isMultiScale,qreal gleamCount,qreal gleamScale);
    virtual void setName(QString name, QString visible);
    virtual void setTypeItem(TypeItem type);


};






#endif // AITEM_H
