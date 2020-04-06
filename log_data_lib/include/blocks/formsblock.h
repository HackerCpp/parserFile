#ifndef FORMSBLOCK_H
#define FORMSBLOCK_H

#include "ablock.h"
#include "aboard.h"
#include <QList>

class FormsBlock : public ABlock{
    QList<ABoard*> *m_boards;
    QString m_activeName;
public:
    FormsBlock();
    ~FormsBlock();

    void setActiveName(QString activeName);
    void addBoard(ABoard* block);
    QList<ABoard*> *boards();
    QString activeName();

};

#endif // FORMSBLOCK_H
