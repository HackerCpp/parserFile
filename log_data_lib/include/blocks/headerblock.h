#ifndef HEADERBLOCK_H
#define HEADERBLOCK_H
#include <QVariant>

#include "ablock.h"
#include "aboard.h"

class HeaderInfo : public QObject{
    QString m_name;
    QString m_body;
public:
    HeaderInfo(){}
    HeaderInfo(QString name,QString body):m_name(name),m_body(body){}
    ~HeaderInfo(){}
    void setName(QString name){m_name = name;}
    void setBody(QString body){m_body = body;}
    QString name(){return m_name;}
    QString body(){return m_body;}
};


class HearedBlock: public ABlock{
    QList<QSharedPointer<HeaderInfo>> *m_info;
public:
    HearedBlock();
    ~HearedBlock();

    void setHeaderInfo(QSharedPointer<HeaderInfo> info);
    QList<QSharedPointer<HeaderInfo>> *infoHeader();


};

#endif // HEADERBLOCK_H
