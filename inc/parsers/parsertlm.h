#ifndef PARSERTLM_H
#define PARSERTLM_H

#include "QString"
#include "QList"
#include "inc/parsers/findblocks.h"

struct Packet{           //***
    uint	time;
    QString dev_type;
    QString	inf_type;
    QString data;
};
struct TlmPack{          //**
    uchar state;
    ushort length;
    Packet dataPucket;
};
struct BlockTlm{
    QString boom;
    QString name;
    QList<TlmPack> TlmPackList;
};


/*!
 * \brief Класс ищет пакеты данных тлм
 *
 * Каждый пакет информации данных тлм файла находится по структуре прим(TlmPack),
 * 1.Статус 1 байт,если старший бит равен единице,то это служебная информация и
 * времени в пакете не будет, сразу нужно считывать dev_type.Если старший бит 0,
 * значит после длины читаем время 4 байта,а потом dev_type.
 * 2.Длина данных 2 байта
 * 3.Время 4 байта, если старший бит статуса = 0
 * 4.Тип прибора откуда пришли данные
 * 5.Тип данных
 * 6.Данные
 * \author Пряников Алексей Владимирович
 */

class ParserTLM{
    QString devTypeArray[10] //!< Названия приборов откуда(куда) могут приходить данные
                    = {"UPS1","UPS2","UPS3","UPS4","CPU","PLOT","SU","MTK","Reserve","ADSP"};
    QString infTypeArray[14] //!< Тип данных
    = {"GETVERSION","GETBLOCKINF","ERROR","STARTMON","WRITEDATA","STARTPROG",
                            "WRITEPARAM","GETPARAM","CMD","GETDATA","WRITEBLOCKINF","CLEARSECTOR","GETCLEARSTATUS","UIPCOMMAND"};
    QList<BlockTlm> *tlmBlocks;

    void findPackFFFE(QString TlmPackString,TlmPack *TlmPack);
    void findTlmPackFFFE(QString blockTlmString,BlockTlm* blockTlm);
public:
    /*!
    * \brief Конструктор принимает HEX строку .tlm файла и разбивает её на пакеты данных
    * \param [in] hexTextTlmFile строка символов
    */
    ParserTLM(QString hexTextTlmFile);
    QList<BlockTlm> *getBlocks();
    ~ParserTLM();
};

#endif // PARSERTLM_H
