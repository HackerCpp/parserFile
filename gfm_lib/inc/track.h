#ifndef TRACK_H
#define TRACK_H
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDomNode>
#include "iteminfo.h"

class Track{
    QDomNode *m_xmlTracks;
    QList<ItemInfo*>* m_items;
public:
    Track(QDomNode *xmlTracks);
    int left();
    int width();
    void parser(QByteArray *byteArray);
    QList<ItemInfo*>* items();
    ~Track();
};

#endif // TRACK_H
