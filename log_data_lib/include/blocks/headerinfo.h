#ifndef HEADERINFO_H
#define HEADERINFO_H

#include <QObject>

class HeaderInfo : public QObject{
    QString m_name;
    QString m_body;
    QString m_comment;
public:
    HeaderInfo(){}
    HeaderInfo(QString name,QString body,QString comment = ""):m_name(name),m_body(body),m_comment(comment){}
    ~HeaderInfo(){}
    void setName(QString name){m_name = name;}
    void setBody(QString body){m_body = body;}
    void setComment(QString mark){m_comment = mark;}
    QString name(){return m_name;}
    QString body(){return m_body;}
    QString comment(){return m_comment;}
};

#endif // HEADERINFO_H
