#include "boardfortrack.h"
#include <QScreen>
#include <QApplication>

BoardForTrack::BoardForTrack(){
    QList<QScreen *> f_screens = QApplication::screens();
    m_pixelPerMm = f_screens.at(0)->physicalDotsPerInch()/2.54/10;
    m_pictureHeight = 6000;
    m_offsetUp = 1000;
    m_top = -10;
    m_length = 2000;
}
