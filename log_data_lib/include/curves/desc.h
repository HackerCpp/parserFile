#ifndef DESC_H
#define DESC_H
#include <QHash>
#include <QDebug>

class Desc{
    QHash<QString,QString> *m_parameters;
    QHash<QString,QString> *m_calibration;
public:
    Desc(QByteArray desc);
    Desc();
    QByteArray forSave();

    void setParam(QString index,QString value);
    void setCalib(QString index,QString value);

    QString param(QString index);
    QString calib(QString index);
};

#endif // DESC_H
