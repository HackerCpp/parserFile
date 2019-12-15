#ifndef BOARD_H
#define BOARD_H
#include <QByteArray>
#include <QList>
#include "track.h"
#include <QDebug>
#include <QDomNode>

class Board{
    QList<Track*> *m_tracks;
    QDomNode *m_xmlBoard;
public:
    Board(QDomNode *xmlBoard);
    QString name();
    QList<Track*> *tracks();
    ~Board();
};

#endif // BOARD_H
