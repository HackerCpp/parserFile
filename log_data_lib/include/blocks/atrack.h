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
        int logarithmBase;
        int decadeCount;
        int decadeStart;
        int decadeEnd;
    }m_logarithm;

public:
    ATrack();
    ~ATrack(){}


    void setIsGreed(bool isGreed);
    void setName(QString name);
    void setType(QString type);
    void setType(Type type);
    void setLogarothm(int log_base,int dec_count, int dec_start,int dec_end);
    void setBegin(float begin,QString unit);
    void setWidth(float width);

    bool isGreed(){return m_IsGreed;}
    Type type(){return m_type;}
    QString name(){return m_name;}

};

#endif // ATRACK_H
