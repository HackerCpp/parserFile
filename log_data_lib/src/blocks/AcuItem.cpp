#include "acuItem.h"
#include <QDebug>
#include <QList>

AcuItem::AcuItem(){
    m_multicolor = new QList<MulticolorItem>;
    m_type = ACU;
}

AcuItem::~AcuItem(){

}

void AcuItem::setColor(QString bruchColor, QString transparentColor){
    m_brushColor = bruchColor;
    m_transparentColor = transparentColor;
}

void AcuItem::setMulticolor(MulticolorItem multicolor){
    m_multicolor->push_back(multicolor);
}

void AcuItem::setShowMode(unsigned int showMode){
    m_showMode = showMode;
}

void AcuItem::setLevelCount(int levelCount){
    m_levelCount = levelCount;
}



int AcuItem::levelCount(){
    return m_levelCount;
}

QString AcuItem::bruchColor(){
    return m_brushColor;
}

QString AcuItem::transparentColor(){
    return m_transparentColor;
}

QList<MulticolorItem> *AcuItem::multiColor(){
    return m_multicolor;
}

unsigned int AcuItem::showMode(){
    return m_showMode;
}
