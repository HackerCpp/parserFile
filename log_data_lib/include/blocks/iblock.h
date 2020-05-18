#ifndef IBLOCK_H
#define IBLOCK_H

#include <stdint.h>
#include <QString>
#include <QList>
#include <QObject>



class IBlock : public QObject{

public:
    enum TypeBlock {NO_BLOCK,DATA_BLOCK, FORMS_BLOCK,
                    TOOLINFO_BLOCK, HEADER_BLOCK};
public:
    IBlock();
    virtual ~IBlock();

    virtual TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);
};

#endif // IBLOCK_H
