#include "iteminfo.h"
#include <QDebug>

ItemInfo::ItemInfo(QDomNode *xmlItemInfo){
    m_xmlItemInfo = xmlItemInfo;
    QDomNode item = m_xmlItemInfo->firstChild();
    while (false == item.isNull()){
        QString tag = item.nodeName();
        if(tag == "style"){
            m_style = new QDomNode(item);
        }
        item = item.nextSibling();
    }
}

QString ItemInfo::name(){
    m_xmlItemInfo->attributes().namedItem("name").nodeValue();
}

int ItemInfo::widthLine(){
    QDomNode styleTeg = m_style->firstChild();
    while (false == styleTeg.isNull()){
        QString tag = styleTeg.nodeName();
        if(tag == "width")
            return styleTeg.attributes().namedItem("value").nodeValue().toInt();
        styleTeg = styleTeg.nextSibling();
    }
    return 1;
}

QColor ItemInfo::color(){
    return QColor(m_style->attributes().namedItem("color").nodeValue());
}
