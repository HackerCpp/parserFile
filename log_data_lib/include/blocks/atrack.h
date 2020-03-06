#ifndef ATRACK_H
#define ATRACK_H

#include <QString>

class ATrack{
    enum Type{LINEAR};

    Type m_type;
    QString m_name;
    bool m_IsGreed;
    int m_begin,m_width;
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
    void setBegin(float begin,QString unit);
    void setWidth(float width,QString unit);

    bool isGreed(){return m_IsGreed;}
    Type type(){return m_type;}
    QString name(){return m_name;}

};

#endif // ATRACK_H
