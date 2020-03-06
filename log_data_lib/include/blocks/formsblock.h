#ifndef FORMSBLOCK_H
#define FORMSBLOCK_H

#include "ablock.h"
#include "iboard.h"
#include <QList>

class FormsBlock : public ABlock{
    QList<IBoard*> *m_boards;
    QString m_activeName;
public:
    FormsBlock();
    ~FormsBlock();

    void setActiveName(QString activeName);
    void addBoard(IBoard* block);

    QString activeName();
};

#endif // FORMSBLOCK_H
