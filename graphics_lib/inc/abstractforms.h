#ifndef ABSTRACTFORMS_H
#define ABSTRACTFORMS_H

#include "abstractboard.h"
#include <QTableWidget>
#include "gfm.h"


class AbstractForms : public QTabWidget{
protected:
    virtual bool gzipCompress(QByteArray input, QByteArray &output, int level);
    virtual bool gzipDecompress(QByteArray input, QByteArray &output);
public:
    AbstractForms(QByteArray zipForms,QMap<QString,Curve*> *curves);
    virtual QByteArray zipForms();
    virtual void setZipForms();
    virtual ~AbstractForms();
};

#endif // ABSTRACTFORMS_H
