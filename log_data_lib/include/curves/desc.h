#ifndef DESC_H
#define DESC_H
#include <QHash>
#include <QDebug>

class Desc{
    QHash<QString,QString> *m_parameters;
    QHash<QString,QString> *m_calibration;
public:
    Desc(QByteArray desc);
    QByteArray forSave();
    QString param(QString index);
    QString calib(QString index);
};

#endif // DESC_H
