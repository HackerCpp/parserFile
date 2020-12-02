#ifndef BASECONVERTER_H
#define BASECONVERTER_H
#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include "gtkthread.h"

class BaseConverter : public QWidget
{
protected:
    QButtonGroup *m_btnGroup;
    QVBoxLayout *m_vLayout;
    QString m_fileName;
    GtkThread m_gtkThread;
public:
    BaseConverter();
    virtual ~BaseConverter();

    virtual void convert(){}

    void setFileName(QString fileName);
    void fillWithButtons();
};

#endif // BASECONVERTER_H
