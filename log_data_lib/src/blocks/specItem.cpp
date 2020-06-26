#include "specItem.h"
#include <QDebug>
#include <QList>


SpecItem::SpecItem(){
    m_multicolor = new QList<MulticolorItem>;
    m_type = SPEC;
}

SpecItem::SpecItem(const SpecItem &other)
    :AItem(other){
    m_multicolor = new QList<MulticolorItem>;
    QList<MulticolorItem> *f_multicolor = other.m_multicolor;
    foreach(auto value,*f_multicolor){
        m_multicolor->push_back(value);
    }
    m_brushColor = other.m_brushColor;
    m_transparentColor = other.m_transparentColor;
    m_showMode = other.m_showMode;
    m_levelCount = other.m_levelCount;
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
