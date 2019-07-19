#ifndef PARSERTLM_H
#define PARSERTLM_H

#include "QString"
#include "QList"

struct Pucket{           //***
    uint	time;
    char    dev_type;
    uchar	inf_type;
    QString data;
};
struct TlmPuck{          //**
    uchar state;
    ushort length;
    QString data;
    Pucket dataPucket;
};
struct TlmBlock{         //*
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QString bodyBlock;
    QList<TlmPuck> *tlmPuckList;
};



class ParserTLM{
    QString m_tlmFile;
    QString string;
    QList<TlmBlock> *tlmBlocksList;
public:
    ParserTLM(QString tlmFile);
    QString getHexString();
};

#endif // PARSERTLM_H
