#include "boardfortrack.h"
#include <QScreen>
#include <QApplication>

BoardForTrack::BoardForTrack(){
    QList<QScreen *> f_screens = QApplication::screens();
    m_pixelPerMm = f_screens.at(0)->physicalDotsPerInch()/2.54/10;
    m_scalePixelPerMm = 1;
    m_pictureHeight = 16000;
    m_offsetUp = 7000;
    m_top = -10;
    m_length = 10000;
    m_scaleForDepth = m_scaleForTime = 1.f/10.f;
    m_isDrawTime = false;
    m_positionHeader = 100;
    m_formatImg = QImage::Format_ARGB32;
}

qreal BoardForTrack::scale(){
    return (m_isDrawTime ? m_scaleForTime : m_scaleForDepth) * pixelPerMm();
}

void BoardForTrack::setPictureHeightMM(int heightMM){
    m_pictureHeight = heightMM;
    m_offsetUp = m_pictureHeight / 2;
}
