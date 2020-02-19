#ifndef ABSTRACTBLOCKGFM_H
#define ABSTRACTBLOCKGFM_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QDebug>
#include <QTextCodec>


class AbstractBlockGFM{
    QByteArray *m_block;
protected:

    QString m_name;
    QTextCodec *m_codec;

public:
    AbstractBlockGFM();
    void setName(QString name);
    QString getName()const;
    virtual void parser(QByteArray *bodyBlock);
    virtual QByteArray getForSave();
    virtual ~AbstractBlockGFM();
};

#endif // ABSTRACTBLOCKGFM_H
