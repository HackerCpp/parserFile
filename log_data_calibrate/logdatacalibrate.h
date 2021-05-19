#ifndef LOGDATACALIBRATE_H
#define LOGDATACALIBRATE_H

#include "LogDataCalibrate_global.h"
#include <QMainWindow>
#include <memory>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QPushButton>
#include <QTabWidget>
#include <QScrollArea>


class ILogData;

class LOGDATACALIBRATE_EXPORT LogDataCalibrate :public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<ILogData> m_logData;
    QComboBox *m_comboDevices,*m_comboCurves;
    QPushButton *m_btnCalibrate;
    QTabWidget *m_calibTabs;
    QHBoxLayout *m_menuHorLayout;
    QVBoxLayout *m_mainVLayout;
    QWidget *m_centralWidget;
    QWidget *m_menuWidget;
public:
    explicit LogDataCalibrate(std::shared_ptr<ILogData> logData,QWidget *parent = nullptr);
    ~LogDataCalibrate(){}
public slots:
    void changeDevice();
};

#endif // LOGDATACALIBRATE_H
