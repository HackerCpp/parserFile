#include "specItem.h"
#include <QDebug>
#include <QList>


SpecItem::SpecItem(){
    m_multicolor = new QList<MulticolorItem>;
    m_type = SPEC;
}

SpecItem::~SpecItem(){

}

void SpecItem::setColor(QString bruchColor, QString transparentColor){
    m_brushColor = bruchColor;
    m_transparentColor = transparentColor;
}

void SpecItem::setMulticolor(MulticolorItem multicolor){
    m_multicolor->push_back(multicolor);
}

void SpecItem::setShowMode(unsigned int showMode){
    m_showMode = showMode;
}

void SpecItem::setLevelCount(int levelCount){
    m_levelCount = levelCount;
}



int SpecItem::levelCount(){
    return m_levelCount;
}

QString SpecItem::bruchColor(){
    return m_brushColor;
}

QString SpecItem::transparentColor(){
    return m_transparentColor;
}

QList<MulticolorItem> *SpecItem::multiColor(){
    return m_multicolor;
}

unsigned int SpecItem::showMode(){
    return m_showMode;
}
