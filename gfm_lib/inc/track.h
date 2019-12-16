#ifndef TRACK_H
#define TRACK_H
#include <QByteArray>
#include <QString>
#include <QDebug>

class Track{
    QString m_name,m_type;
    bool m_isShowGrid;
    int m_leftPosition;
    int m_width;
public:
    Track();
    void parser(QByteArray *byteArray);
    ~Track();
};

#endif // TRACK_H
