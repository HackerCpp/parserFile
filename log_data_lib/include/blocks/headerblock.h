#ifndef HEADERBLOCK_H
#define HEADERBLOCK_H
#include <QVariant>

#include "ablock.h"
#include "aboard.h"

struct HearedInfo{
    QString name;
    QString body;
};


class HearedBlock: public ABlock{
    QList<HearedInfo> *m_info;
public:
    HearedBlock();
    ~HearedBlock();

    void setHeaderInfo(HearedInfo info);
    QList<HearedInfo> *infoHeader();


};

#endif // HEADERBLOCK_H
