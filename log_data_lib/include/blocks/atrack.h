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
<<<<<<< HEAD
    int getIsGreed(){return m_IsGreed;}
    QString getName(){return m_name;}
    QString getType();
    float getBegin(){return m_begin;}
    float getWidth(){return m_width;}
    float getLogarithm();
    float getLogarithmBase(){return m_logarithm.logarithmBase;}
    float getDecadeCount(){return m_logarithm.decadeCount;}
    float getDecadeStart(){return m_logarithm.decadeStart;}
    float getDecadeEnd(){return m_logarithm.decadeEnd;}

    Type type(){return m_type;}

    QList <AItem*> getItems();
=======


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
>>>>>>> b501db74b2187d2cd07b61e4d974a67aebca7876

};

#endif // ATRACK_H
