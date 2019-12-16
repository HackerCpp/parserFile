#ifndef BOARD_H
#define BOARD_H
#include <QByteArray>
#include <QList>
#include "track.h"
#include <QDebug>

class Board{
    QString m_name;
    QList<Track*> *m_tracks;
public:
    Board();
    void parser(QByteArray *byteArray);
    ~Board();
};

#endif // BOARD_H
