#ifndef DESC_H
#define DESC_H
#include <QHash>
#include <QDebug>

class Paraminfo : public QObject{
    Q_OBJECT
    QString m_index;
    QString m_value;

public:
    Paraminfo(QString index,QString value);
    ~Paraminfo(){}
    QString index(){return m_index;}
    QString value(){return m_value;}
};
/*****************************************************************/
class Parameters : public QObject{
public:
    enum Type{PARAM,CALIB};
private:
    QMap<QString,QString> *m_mapParameters;
    QVector<Paraminfo *> *m_vectorParameters;
    Type m_type;
    void init();
public:


    Parameters(QByteArray parameters,Type type);
    Parameters(Type type);
    ~Parameters();

    void insert(QString index,QString value);
    QString value(QString index){return m_mapParameters->value(index);}
    QVector<Paraminfo *> *vectorParameters(){return m_vectorParameters;}
    Type type(){return m_type;}

};

/****************************************************************************************/
class Desc : public QObject{
    Q_OBJECT
    Parameters *m_parameters;
    Parameters *m_calibration;
    //QHash<QString,QString> *m_parameters;
    //QHash<QString,QString> *m_calibration;
public:
    Desc(QByteArray desc);
    Desc();
    ~Desc();

    void setParam(QString index,QString value);
    void setCalib(QString index,QString value);

    QString param(QString index);
    QString calib(QString index);

    Parameters *parameters(){return m_parameters;}
    Parameters *calibrations(){return m_calibration;}

};

#endif // DESC_H
