#ifndef ATRACK_H
#define ATRACK_H

#include <QString>
#include <QList>
#include <aitem.h>

enum Types{LINEAR};

class ATrack{


    Types m_type;
    QString m_name;
    int m_number;
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

    void setNumber(int number){m_number = number;}


    bool isGreed(){return m_isGreed;}
    QString name(){return m_name;}
    Types type(){return m_type;}
    qreal begin(){return m_begin;}
    qreal width(){return m_width;}
    qreal logarithmBase();
    qreal decadeCount();
    qreal decadeStart();
    qreal decadeEnd();

    int number(){return m_number;}

};

#endif // ATRACK_H
