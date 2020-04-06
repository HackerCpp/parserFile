#ifndef IBLOCK_H
#define IBLOCK_H

#include <stdint.h>
#include <QString>
#include <QList>



class IBlock{

QString m_name;
public:
    enum TypeBlock {NO_BLOCK,DATA_BLOCK, FORMS_BLOCK,
                    TOOLINFO_BLOCK, HEADER_BLOCK};
public:
    IBlock();
    virtual ~IBlock();

    virtual TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);
    virtual void setName(QString name);
    virtual QString names();


};

#endif // IBLOCK_H
