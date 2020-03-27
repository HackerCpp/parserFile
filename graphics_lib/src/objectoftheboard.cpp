#include "objectoftheboard.h"
#include <QApplication>
#include <QScreen>

qreal ObjectOfTheBoard::m_pixelPerMm = 1;

ObjectOfTheBoard::ObjectOfTheBoard(){
    QList<QScreen *> f_screens = QApplication::screens();
    m_pixelPerMm = f_screens.at(0)->physicalDotsPerInch()/2.54/10;
}

void ObjectOfTheBoard::changingTheVisibilityZone(QRect newVisibilityZone){
    m_visibilitySquare = newVisibilityZone;
}
