#include "boardfortrack.h"
#include <QScreen>
#include <QApplication>

BoardForTrack::BoardForTrack(){
    QList<QScreen *> f_screens = QApplication::screens();
    m_pixelPerMm = f_screens.at(0)->physicalDotsPerInch()/2.54/10;
    m_pictureHeight = 10000;
    m_offsetUp = 4000;
    m_top = -10;
    m_length = 10000;
    m_scaleForDepth = m_scaleForTime = 1.f/10.f;
    m_isDrawTime = false;
    setFormatTime(FormatTime::SEC_SM_1);
}

qreal BoardForTrack::scale(){
    return m_isDrawTime ? m_scaleForTime : m_scaleForDepth;
}
