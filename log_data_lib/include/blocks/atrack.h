#ifndef ATRACK_H
#define ATRACK_H

#include <QString>
#include <QList>
#include <aitem.h>

enum Types{LINEAR};

class ATrack{

    QList <AItem*> *m_items;
    Types m_type;
    QString m_name;

    bool m_IsGreed;
    qreal m_begin,m_width;
    struct Logarithm{
        qreal logarithmBase;
        qreal decadeCount;
        qreal decadeStart;
        qreal decadeEnd;
    }m_logarithm;

public:
    ATrack();
    ~ATrack(){}


    void setIsGreed(bool isGreed);
    void setName(QString name);
    void setType(Types type);
    void setLogarithm(qreal log_base,qreal dec_count, qreal dec_start,qreal dec_end);
    void setBegin(qreal begin);
    void setWidth(qreal width);
    void setItem(AItem *item);

    bool IsGreed();
    QString Name();
    Types Type();
    qreal Begin();
    qreal Width();
    qreal Logarithm();
    qreal LogarithmBase();
    qreal DecadeCount();
    qreal DecadeStart();
    qreal DecadeEnd();
    QList <AItem*> Items();

};

#endif // ATRACK_H
