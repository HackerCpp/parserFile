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
/*!
*  \date 28.05.2021
*
*  \authors Пряников Алексей Владимирович
*
*   \brief Класс, калибровка каротажных данных.
* Предлагает выбрать один из приборов найденных в данных(LogData).
* При нажатии кнопки "калибровать", создаёт виджет калибровки.
* Виджет калибровки для каждого прибора нужно делать свой.
*
*/
class LOGDATACALIBRATE_EXPORT LogDataCalibrate :public QMainWindow
{
    Q_OBJECT
    std::shared_ptr<ILogData> m_logData;
    QComboBox *m_comboDevices;
    QPushButton *m_btnCalibrate;
    QPushButton *m_btnOpenProtocol;
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
    void openProtocol();
};

#endif // LOGDATACALIBRATE_H
