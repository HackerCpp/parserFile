#ifndef AITEM_H
#define AITEM_H
#include <QVariant>
#include "astyleitem.h"

enum PaintMode{CURVE_MODE,NUMBERS_MODE};
enum TypeItem{LINE,ACU};
struct MulticolorItem{
    qreal bound;
    QString value;
};
class AItem{ 
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

    virtual bool isBeginValue();
    virtual qreal beginValue();
    virtual qreal zeroOffset();

    virtual bool isEndValue();
    virtual qreal endValue();
    virtual qreal scale();

    virtual bool isMultiScale();
    virtual unsigned int glemCount();
    virtual qreal glemScale();

    virtual void color();
    virtual void widthLine();



    virtual void setBegin(bool isBegin,qreal begin,qreal zeroOffset);
    virtual void setEnd(bool isEnd,qreal end,qreal scale);
    virtual void setMultiScale(bool isMultiScale,qreal gleamCount,qreal gleamScale);


};


class LineItem : public AItem{
    QString m_color;
    unsigned int m_widthLine;
    bool m_isDashes;

    PaintMode m_paintMode;
public:

    LineItem();
    ~LineItem();
};

class AcuItem : public AItem{
    QString m_brushColor;
    QString m_transparentColor;
    QList<MulticolorItem> *m_multicolor;

    unsigned int  m_showMode;
public:

    AcuItem();
    ~AcuItem();
};

class MarkItem : public AItem{
    QString m_color;
    unsigned int m_widthLine;
    bool m_isDashes;

public:

    MarkItem();
    ~MarkItem();
};
#endif // AITEM_H
