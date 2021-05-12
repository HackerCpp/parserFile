#include "boardfortrack.h"
#include <QScreen>
#include <QApplication>


BoardForTrack::BoardForTrack(DrawSettings *drawSettings)
    : m_drawSettings(drawSettings){
    m_top = -10;
    m_length = 10000;
    m_positionHeader = 100;
}
