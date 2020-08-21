#include "acuItem.h"
#include <QDebug>
#include <QList>

AcuItem::AcuItem(){
    m_multicolor = new QList<MulticolorItem>;
    m_type = ACU;
}

AcuItem::AcuItem(const AcuItem &other)
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


AcuItem::~AcuItem(){

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
