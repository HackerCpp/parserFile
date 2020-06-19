#ifndef IBLOCK_H
#define IBLOCK_H

#include <stdint.h>
#include <QString>
#include <QList>
#include <QObject>


class IBlock : public QObject{
    Q_OBJECT

public:
    enum TypeBlock {NO_BLOCK,DATA_BLOCK, FORMS_BLOCK,
                    TOOLINFO_BLOCK, HEADER_BLOCK};

public:
    IBlock();
    IBlock(const IBlock &block){Q_UNUSED(block)}
    virtual ~IBlock();

    virtual TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);

    static IBlock * blockCreater(IBlock::TypeBlock type);
    static IBlock * blockCreater(const IBlock &block);

signals:
    void dataUpdate();
};

#endif // IBLOCK_H
