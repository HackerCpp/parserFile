#ifndef ATRACK_H
#define ATRACK_H

#include <QString>
#include <QList>
#include <aitem.h>
class ATrack{

    QList <AItem*> *m_items;



    enum Type{LINEAR};

    Type m_type;
    QString m_name;
    QString m_widthString;
    bool m_IsGreed;
    float m_begin,m_width;
    struct Logarithm{
        float logarithmBase;
        float decadeCount;
        float decadeStart;
        float decadeEnd;
    }m_logarithm;

public:
    ATrack();
    ~ATrack(){}


    void setIsGreed(bool isGreed);
    void setName(QString name);
    void setType(QString type);
    void setType(Type type);
    void setLogarithm(float log_base,float dec_count, float dec_start,float dec_end);
    void setBegin(QString begin,QString unit);
    void setWidth(QString width,QString unit);
    void setWidthString(QString valueString);
    QString getWidthString(){return m_widthString;}
    void setItem(AItem *item);
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

};

#endif // ATRACK_H
