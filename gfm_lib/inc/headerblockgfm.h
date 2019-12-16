#ifndef HEADERBLOCKGFM_H
#define HEADERBLOCKGFM_H
#include "inc/abstractblockgfm.h"

class HeaderBlockGFM : public AbstractBlockGFM{
    struct Subunit{
        QString m_name;
        QString m_data;
    };
    QList <Subunit*> *m_blocks;
public:
    HeaderBlockGFM();
    void parser(QByteArray *bodyBlock);
    virtual QByteArray getForSave();
    ~HeaderBlockGFM();
};

#endif // HEADERBLOCKGFM_H
