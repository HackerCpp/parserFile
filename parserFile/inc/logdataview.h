#ifndef LOGDATAVIEW_H
#define LOGDATAVIEW_H

#include <QWidget>
#include <ilogdata.h>

class LogDataView : public QWidget
{
    Q_OBJECT
public:
    explicit LogDataView(QWidget *parent = nullptr);
    ~LogDataView(){}

signals:

};

#endif // LOGDATAVIEW_H
