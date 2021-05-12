#ifndef HEADERBLOCK_H
#define HEADERBLOCK_H
#include <QVariant>

#include "ablock.h"

class HeaderInfo;

class HeaderBlock: public ABlock{
    QList<QSharedPointer<HeaderInfo>> *m_info;
public:

    HeaderBlock();
    ~HeaderBlock();

    void setHeaderInfo(QSharedPointer<HeaderInfo> info);
    QList<QSharedPointer<HeaderInfo>> *infoHeader();


};

#endif // HEADERBLOCK_H
