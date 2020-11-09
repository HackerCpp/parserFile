#ifndef UNPACKER_H
#define UNPACKER_H
#include <QString>

class Unpacker{
    Unpacker(){}
public:
    static bool unpack(QString file,QString where,bool isDeleted);
};

#endif // UNPACKER_H
