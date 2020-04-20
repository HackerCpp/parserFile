#ifndef AITEM_H
#define AITEM_H
#include <QVariant>
#include "astyleitem.h"
#include <QDebug>

//enum PaintMode{CURVE_MODE,NUMBERS_MODE};
enum TypeItem{LINE,ACU,MARK};


class AItem{
public:
    enum VisibleView{VIEW_NUM,BOARD_GRAPH_VIEW,BOARD_LEGEND_VIEW,
                    BOARD_WAVE_VIEW,DIGITAL_DATA_VIEW,DIGITAL_LEGEND_VIEW,
                    BOARD_TOOL_TIP_VIEW,MAXIMIM};

protected:
    TypeItem m_type;
    QString m_name;

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

    uint8_t m_visible[VisibleView::MAXIMIM];
public:
    AItem();
    virtual ~AItem();

    virtual QString name(){return m_name;}
    virtual QString visible();
    virtual bool visible(VisibleView what){return m_visible[what];}

    virtual bool isBeginValue(){return m_begin.is_beginValue;}
    virtual qreal beginValue(){return m_begin.beginValue;}
    virtual qreal zeroOffset(){return m_begin.zeroOffset;}

    virtual bool isEndValue(){return m_end.is_endValue;}
    virtual qreal endValue(){return m_end.endValue;}
    virtual qreal scale(){return m_end.scale;}

    virtual bool isMultiScale(){return m_multiScale.is_multiscale;}
    virtual qreal glemCount(){return m_multiScale.gleamCount;}
    virtual qreal glemScale(){return m_multiScale.gleamScale;}


    virtual TypeItem Type(){return m_type;}


    virtual void setBegin(bool isBegin, qreal begin, qreal zeroOffset);
    virtual void setEnd(bool isEnd,qreal end,qreal scale);
    virtual void setMultiScale(bool isMultiScale,qreal gleamCount,qreal gleamScale);
    virtual void setName(QString name, QString visible);
    virtual void setTypeItem(TypeItem type){m_type = type;}
};






#endif // AITEM_H
