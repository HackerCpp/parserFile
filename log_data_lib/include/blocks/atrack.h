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

    bool m_isGreed;
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


    void setIsGreed(bool isGreed){m_isGreed = isGreed;}
    void setName(QString name){m_name = name;}
    void setType(Types type){m_type = type;}
    void setLogarithm(qreal log_base,qreal dec_count, qreal dec_start,qreal dec_end);
    void setBegin(qreal begin){m_begin = begin;}
    void setWidth(qreal width){m_width = width;}
    void setItem(AItem *item);

    bool isGreed(){return m_isGreed;}
    QString name(){return m_name;}
    int number(){return m_name.remove("Track").toInt();}
    Types type(){return m_type;}
    qreal begin(){return m_begin;}
    qreal width(){return m_width;}
    qreal logarithmBase();
    qreal decadeCount();
    qreal decadeStart();
    qreal decadeEnd();
    QList<AItem*> *items(){return m_items;}

};

#endif // ATRACK_H
