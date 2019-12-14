#ifndef TRACK_H
#define TRACK_H
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDomNode>

class Track{
    QString m_name,m_type;
    bool m_isShowGrid;
    int m_leftPosition;
    int m_width;
    QDomNode *m_xmlTracks;
public:
    Track(QDomNode *xmlTracks);
    int left();
    int width();
    void parser(QByteArray *byteArray);
    ~Track();
};

#endif // TRACK_H
