#ifndef CALIBRATENOISE_H
#define CALIBRATENOISE_H

#include <QWidget>
#include <QDateTime>
#include <QVBoxLayout>
#include <QScrollArea>

class ILogData;

/*!
*  \date 28.05.2021
*
*  \authors Пряников Алексей Владимирович
*
*   \brief Виджет для калибровки шумомера.
*
*/

class CalibrateNoise : public QScrollArea
{
    QDateTime m_dateTimeCalib;
    QVBoxLayout *m_mainVBoxLayout;
    QWidget *m_mainWidget;
public:
    CalibrateNoise(std::shared_ptr<ILogData> logData,QString device);
    CalibrateNoise(){}


};

#endif // CALIBRATENOISE_H
